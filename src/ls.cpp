#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

void parse_flags(const int argc, char* argv[], bool& flag_a,
	bool& flag_l, bool& flag_R, queue<string> &q_dirs)
{
	unsigned count = argc;
	for(int i = count - 1; i != 0; --i)
	{
		if(argv[i][0] == '-')
		{
			if(argv[i][1] == '\0')
			{
				cout << "Error: invalid flag" << endl;
				exit(1);
			}
			for(int j = 1; argv[i][j] != '\0'; ++j)
			{
				if (argv[i][j] == 'a')
				{
					flag_a = true;
				}
				else if(argv[i][j] == 'l')
				{
					flag_l = true;
				}
				else if(argv[i][j] == 'R')
				{
					flag_R = true;
				}
			}
		}
		else
		{
			q_dirs.push(argv[i]);
		}
	}
}

void get_perm(struct stat &info, string& perm)
{
	if(S_ISREG(info.st_mode)) perm[0] = '-';
	else if(S_ISDIR(info.st_mode)) perm[0] = 'd';
	else if(S_ISBLK(info.st_mode)) perm[0] = 'b';
	else if(S_ISCHR(info.st_mode)) perm[0] = 'c';
	else if(S_ISLNK(info.st_mode)) perm[0] = 'l';

	if(S_IRUSR & info.st_mode) perm[1] = 'r';
	if(S_IWUSR & info.st_mode) perm[2] = 'w';
	if(S_IXUSR & info.st_mode) perm[3] = 'x';
	if(S_IRGRP & info.st_mode) perm[4] = 'r';
	if(S_IWGRP & info.st_mode) perm[5] = 'w';
	if(S_IXGRP & info.st_mode) perm[6] = 'x';
	if(S_IROTH & info.st_mode) perm[7] = 'r';
	if(S_IWOTH & info.st_mode) perm[8] = 'w';
	if(S_IXOTH & info.st_mode) perm[9] = 'x';
}

void get_usrgrp(struct stat &info, string& usr, string& grp)
{
	struct passwd *user;
	if(!(user = getpwuid(info.st_uid)))
	{
		perror("getpwuid()");
	}
	struct group *gp;
	if(!(gp = getgrgid(info.st_gid)))
	{
		perror("getgrgid()");
	}

	usr = user->pw_name;
	grp = gp->gr_name;
}

int calc_total_block(vector<string>& v_files, string& path_curr)
{	
	int total = 0;
	for(int i = 0; i < v_files.size(); ++i)
	{
		struct stat info;
		if(-1 == stat((path_curr + "/" + (v_files[i])).c_str(), &info))
		{
			perror("stat()");
		}
		total += info.st_blocks;
	}
	return total/2;
}

void print_long(vector<string>& v_files, string& path_curr)
{
	int total = calc_total_block(v_files, path_curr);
	cout << "total " << total << endl;

	for(int i = 0; i < v_files.size(); ++i)
	{
		struct stat info;
		if(-1 == stat((path_curr + "/" + (v_files[i])).c_str(), &info))
		{
			perror("stat()");
			exit(1);
		}
	
		string perm = "----------";
		string usr;
		string grp;

		get_perm(info,perm);
		get_usrgrp(info,usr,grp);
		
		string time = ctime(&info.st_mtime);
		time = time.substr(4,time.length() - 13);

		cout << right;
		cout << perm << " ";
		cout << right;
		cout << setw(2) << info.st_nlink << " ";
		cout << left;
		cout << setw(3) << usr << " ";
		cout << left;
		cout << setw(3) <<  grp << " ";
		cout << right;
		cout << setw(4) << info.st_size << " ";
		cout << right;
		cout << setw(6) <<  time << " ";
		cout << left;
		cout << setw(3) << v_files[i] << endl;
	}

}

bool ignore_case(const string &x, const string &y)
{
	if(tolower(x[0]) < tolower(y[0])) return true;
	else if (tolower(x[0]) > tolower(y[0])) return false;

	return x < y;
}

void do_recursive(queue<string> &q_dirs, vector<string> &v_files, string &path_curr)
{
	if(!v_files.empty())
	{
		for(int i = v_files.size() - 1; i != 0; --i)
		{
			struct stat info;
			if(-1 == stat((path_curr + "/" + (v_files[i])).c_str(), &info))
			{
				perror("stat()");
				exit(1);
			}
		
			if(info.st_mode & S_IFDIR)
			{
				q_dirs.push(path_curr + "/" + v_files[i]);
			}
		}
	}
}


int main(int argc, char* argv[])
{
	if(argc < 1)
	{
		cout << "Error: No arguments passed in." << endl;
		exit(1);
	}
	else
	{
		bool flag_a = false;
		bool flag_l = false;
		bool flag_R = false;

		queue<string> q_dirs;
		vector<string> v_files;

		parse_flags(argc, argv, flag_a, flag_l, flag_R, q_dirs);
	
		//lets ls check cwd without having to pass .	
		if(q_dirs.empty()) q_dirs.push(".");


		while(!q_dirs.empty())
		{
			string path_curr = q_dirs.front();

			DIR *dirp;
			if(NULL == (dirp = opendir(q_dirs.front().c_str())))
			{
				perror("opendir()");
				exit(1);
			}
			struct dirent *files;
			errno = 0;
			while(NULL != (files = readdir(dirp)))
			{
				if(files->d_name[0] == '.' && flag_a == false)
				{
					continue;
				}
				v_files.push_back(files->d_name);
			
			}
			
			//alphabetize
			sort(v_files.begin(), v_files.end(), ignore_case);
			
			if(flag_R)
			{
				cout << path_curr << ":" << endl;
				do_recursive(q_dirs, v_files, path_curr);
			}
			
			if(!flag_l)
			{
				for(vector<string>::iterator it = v_files.begin(); it != v_files.end(); ++it)
				{
					cout << *it << " ";
				}
			}
			

			if(flag_l)
			{
				print_long(v_files, path_curr);
			}

			q_dirs.pop();

			if(errno != 0)
			{
				perror("readdir()");
				exit(1);
			}
			cout << endl;
			if(-1 == closedir(dirp))
			{
				perror("closedir()");
				exit(1);
			}
		}
	}	
	return 0;

}
