#include "Timer.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
using namespace std;

int main(int argc, char **argv)
{
	//check # arguments
	if(argc<3 || argc > 4)
	{
 		cout<<"try: cp src dst (flag)" <<endl;
 		return 1;
	}

int index_input = 1;
int index_output = 2;


int index_flag = 0;

char * find_flag;

//look for flag and get files positions
for(int i=1; i<argc; i++)
{
	if(memcmp(argv[i],"-",1)==0)
	{
		find_flag = strchr(argv[i],'a');

		if(find_flag !=NULL)
		{
			index_flag = i;			
			if(index_flag == 1)
			{
				index_input=2;
				index_output=3;
			}
			if(index_flag == 2)
			{
				index_input=1;
				index_output=3;
			}
			if(index_flag == 3)
			{
				index_input=1;
				index_output=2;
			}
		}
	}
}

//creating a stat

struct stat fileStat;

if(stat(argv[index_input], &fileStat) == -1)
{
	perror("Stat error");
	exit(1);
}

//check if argument is a directory
if(S_ISDIR(fileStat.st_mode) == -1)
{
	cout<<"erro: parameter is a directory"<<endl;
	return 1;
}

DIR *dirp; //creating pointer to directory
if(!(dirp = opendir(".")))
{
	perror("Opendir erro");
	return 1;
}

dirent *direntp;

//reads all files in the directory to check if it already exists

while((direntp = readdir(dirp))) //reads entire directory until finished
{
	if(errno!=0)
	{
		perror("Readdir erro");
		return 1;
	}			
		
	if(strcmp(direntp->d_name,argv[index_output])==0) //reads entire directory checking for if argument passed already exists
	{		
		cout<<"FILE EXIST"<<endl;
		return 1;
	}
}

closedir(dirp);

int flag = 2;
Timer t1,t2,t3;
double eTime,sTime,wTime;
  
ofstream outfile(argv[index_output]);
ifstream is(argv[index_input]);

if(index_flag!=0) flag = 1;
 
switch (flag)
{

	case 1:	
//---------------Method 1 Begins

	t1.start();
	while(is.good())
	{
		char out = is.get(); //reads input stream into char out
		if(is.good())
		{
			outfile.put(out); //writes to output stream
		}
	}

is.close();

t1.elapsedUserTime(eTime);
t1.elapsedSystemTime(sTime);
t1.elapsedWallclockTime(wTime);

cout <<"Method 1"<<endl;
cout <<"UserTime: "<< eTime << endl;
cout <<"SystemTime: "<< sTime << endl;
cout <<"WallclockTime: "<< wTime << endl<<endl;
flag = 2;

//-------------Method 1 Done

//-------------Method 2 Begins

t2.start();
int input2; //input descriptor
int output2; //out descriptor

ssize_t ret_in2;
ssize_t ret_out2;

char buffer2[1];

input2 = open(argv[index_input], O_RDONLY);
if(input2 == -1)
{
	perror("open");
	return 2;
}

output2 = open(argv[index_output], O_WRONLY | O_CREAT);
if(output2 == -1)
{
	perror("open");
	return 3;
}

while((ret_in2 = read (input2, &buffer2, 1))>0)
{
	ret_out2 = write(output2, &buffer2, (ssize_t) ret_in2);
	if(ret_out2 != ret_in2)
	{
		perror("write");
		return 4;
	}
}

close(input2);
close(output2);

t2.elapsedUserTime(eTime);
t2.elapsedSystemTime(sTime);
t2.elapsedWallclockTime(wTime);

cout <<"Method 2"<<endl;
cout <<"UserTime: "<< eTime << endl;
cout <<"SystemTime: "<< sTime << endl;
cout <<"WallclockTime: "<< wTime << endl<<endl;

//--------Method 2 Done

//--------Method 3 Begins

t3.start();
int input3; //input descriptor
int output3; //output descriptor

ssize_t ret_in3;
ssize_t ret_out3;

char buffer3[BUFSIZ]; //reads from bigger data
input3 = open(argv[index_input], O_RDONLY);

if(input3 == -1)
{
	perror("open");
	return 1;
}

output3 = open(argv[index_output], O_WRONLY | O_CREAT);

if(output3 == -1)
{
	perror("open");
	return 1;
}

while((ret_in3 = read (input3, &buffer3, BUFSIZ))>0)
{
	ret_out3 = write(output3, &buffer3, (ssize_t) ret_in3);
	if(ret_out3 != ret_in3)
	{
		perror("write");
		return 1;
	}
}

close(input3);
close(output3);

t3.elapsedUserTime(eTime);
t3.elapsedSystemTime(sTime);
t3.elapsedWallclockTime(wTime);

cout <<"Method 3"<<endl;
cout <<"UserTime: "<< eTime << endl;
cout <<"SystemTime: "<< sTime << endl;
cout <<"WallclockTime: "<< wTime << endl<<endl;

break;
//--------------- Method 3 Done
	case 2:
//-------------- no flag-run fastest
t3.start();
int input; //input descriptor
int output; //output descriptor

ssize_t ret_in;
ssize_t ret_out;

char buffer[BUFSIZ];
input = open(argv[index_input], O_RDONLY);
if(input == -1)
{
	perror("open");
	return 2;
}

output = open(argv[index_output], O_WRONLY | O_CREAT);
if(output == -1)
{
	perror("open");
	return 3;
}

while((ret_in = read (input, &buffer, BUFSIZ))>0)
{
	ret_out = write(output, &buffer, (ssize_t) ret_in);
	if(ret_out != ret_in)
	{
		perror("write");
		return 1;
	}
}

close(input);
close(output);

t3.elapsedUserTime(eTime);
t3.elapsedSystemTime(sTime);
t3.elapsedWallclockTime(wTime);

cout <<"Method 3"<<endl;
cout <<"UserTime: "<< eTime << endl;
cout <<"SystemTime: "<< sTime << endl;
cout <<"WallclockTime: "<< wTime << endl<<endl;

break;
}
}
