#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <boost/tokenizer.hpp>
#include <list>

using namespace std;
using namespace boost;






int main()
{
	char hostname[256];
	gethostname(hostname, 256);
	if(gethostname(hostname, 256) == -1)
	{
		perror("hostname()");
	}
	if(getlogin() == NULL)
	{
		perror("getlogin()");
	}
	while(1)
	{
		string input_cmd;
		list<string> parse_list;
		
		//outputs user login and host name along with command prompt
		cout << getlogin() << "@" << hostname << "$ ";

		//takes in commands
		getline(cin, input_cmd);
		
		//parse command input
		char_separator<char> delim(" ;&|");
		tokenizer< char_separator<char> > mytok(input_cmd, delim);
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			parse_list.push_back(*it);
		}
	
		vector<string> cmd_line;
		vector<char*> arg(parse_list.size() + 1);
		
		string exit_flag = parse_list.front();
	
		while(!(parse_list.empty()))
		{
			cmd_line.push_back(parse_list.front());
			parse_list.pop_front();
		}
      
		for(unsigned int i = 0; i != cmd_line.size(); ++i)  
		{
			arg[i] = &cmd_line[i][0];
		}

		//make it so that anything after exit will still exit
		//
		//if exit entered, exit shell
		if(exit_flag == "exit")
		{
			exit(0);
		}	
		

		//TODO: CHECK FOR COMMENTS # 
		//CONNECTORS		
		
		int pid = fork();
		//error with fork
		if(pid < 0)
		{
			perror("fork()");
			exit(1);
		}
		//child process
		else if(pid == 0)
		{
			if(-1 == execvp(arg[0], arg.data()))//insert arg
			{
				perror("execvp()");
				_exit(1);
			}
			_exit(0);
		}
		//parent process
		else if(pid > 0)
		{
			if(-1 == wait(0))
			{
				perror("wait()");
				exit(1);
			}
		
		}
		
		//arg.clear();

	}

	return 0;
}
