#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

vector<string> get_files (char* arg[], size_t num, bool& r)
{
	vector<string> files;
	for (unsigned int i = 0; i < num; i++)
	{
		if ( arg[i][0] == '-' )
		{
			if ( arg[i][1] == 'r')
			{
				//cout << "here"<< endl;
				r = true;
			}
		}
		else
		{
			files.push_back( string(arg[i]) );
		}
	}

	return files;
}

void remove (string a, bool& rr, string current, bool first)
{

	struct stat s;

	string path = current + '/' + a;

	stat (path.c_str(), &s) != 0;


	vector <string> innerfiles;
	
	ifstream fileopen;
	fileopen.open ((char*)a.c_str());
	
	//if (!fileopen.is_open() && !S_ISDIR(s.st_mode))
	//{
	//	perror ("file does not exist");
	//	exit(1);
	//}

	//fileopen.close();
	if (S_ISDIR(s.st_mode))
	{
		//cout << "rr: " << rr<< endl;
		//file is directory
		if (rr)
		{
			if (a == "." || a == "..")
			{
			}
			
			else
			{
				DIR * open = opendir ( (char*) path.c_str());
				if(open == NULL)
				{
					perror ("open");
					exit(1);
				}

				dirent *b;
				while (( b = readdir(open)))
				{
					string c = b->d_name;
					innerfiles.push_back(c);
				}
			
				if (closedir(open) == -1)
				{
					perror ("close directory fail.");
				}

				for (unsigned u=0; u<innerfiles.size(); u++)
				{
					remove (innerfiles.at(u), rr, path, 0);
				}

			}
		}
		else
		{
			perror ("warning : deleting a directory");
			exit(1);
		}

		rmdir((char*)path.c_str());
	}
	else
	{
		if (first)
		{
			if (fileopen.is_open())
			{
				unlink ((char*) path.c_str() );
			}

			else
			{
				perror ("file does not exist");
				exit(1);
			}
		}
		else
		{
			unlink ( (char*) path.c_str());
		}
		fileopen.close();
	}

}
int main (int argc, char *argv[])
{
	bool r = false;

	vector<string> files = get_files (argv, argc,r);

	//cout << "r: " << r<< endl;
	for (unsigned int i =1; i < files.size(); i++)
	{
		remove(files.at(i), r, ".", 1);
	}

	return 0;
}


