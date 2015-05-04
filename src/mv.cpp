#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>


using namespace std;

int main (int argc, char * argv[])
{
	if (argc < 3)
	{
		perror ("not enough arguments");
		exit(1);
	}
	else if (argc > 3)
	{
		perror ("too many arguments");
		exit(1);
	}

	struct stat s;
	if (stat (argv[1], &s) ==-1)
	{
		perror ("file 1 does not exist");
		exit(1);
	}

	if ( stat (argv[2], &s) == -1)
	{
		// file 2 does not exist
		if  ( link (argv[1], argv[2]) ==-1 )
		{
			perror ("link fail");
		}
		else
		{
			unlink (argv[1]);
		}
	}
	else
	{
		// file 2 exist
		// check dir
		if (S_ISDIR(s.st_mode))
		{
			//cout << "he;;p" << endl;
			string a = argv[2];
			string b = argv[1];

			string new_path = a + '/' + b;
			
			//int file2 = open ( (char*)new_path.c_str(), O_WRONLY | O_CREAT);
			//if (file2 == -1)
			//{
			//	perror ("open fail");	
			//}
			// if file 2 is directory, move over
			if ( link( argv[1] ,new_path.c_str()) == -1)
			{
				perror ("link fail");
			}
			else
			{
				unlink (argv[1]);
			}
		}
		else
		{
			perror ("file 2 not a directory");
			// not directory, 
		}

	}	
	//else
	//{
		
		// file 2 does not exit, create and rename file 1
//	}
	return 0;
}
