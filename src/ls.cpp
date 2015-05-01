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
					cout << "yes flag a" << endl;
				}
				else if(argv[i][j] == 'l')
				{
					flag_l = true;
					cout << "yes flag l" << endl;
				}
				else if(argv[i][j] == 'R')
				{
					flag_R = true;
					cout << "yes flag R" << endl;
				}
			}
		}
		else
		{
			q_dirs.push(argv[i]);
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
		
		parse_flags(argc, argv, flag_a, flag_l, flag_R, q_dirs);
	
		//lets ls check cwd without having to pass .	
		if(q_dirs.empty()) q_dirs.push(".");


		while(!q_dirs.empty())
		{
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
				cout << files->d_name << " ";
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
