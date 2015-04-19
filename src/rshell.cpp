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

	while(1)
	{
		string input_cmd;
		list<string> parse_list;
		
		//FIXME: Doesn't output after fg, error check if host/user dne
		//	
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
		vector<char*> arg;
	
		for(unsigned int i = 0; i < cmd_line.size(); ++i)	
		{
			arg[i] = &cmd_line[i][0];
		}
			
		//TODO: CHECK FOR COMMENTS # 
		//DO FORK AND EXEC
		//CONNECTORS		
		
		int pid = fork();
		//error with fork
		if(pid < 0)
		{
			perror("fork().");
			exit(1);
		}
		//child process
		else if(pid == 0)
		{
			if(-1 == execvp(arg[0], arg.data()))//insert arg
			{
				perror("execvp().");
				_exit(1);
			}
		}
		//parent process
		else if(pid > 0)
		{
			if(-1 == wait(0))
			{
				perror("wait().");
				exit(1);
			}
		
		}
		//if exit entered, exit shell
		if(input_cmd == "exit")
		{
			exit(0);
		}	
	}
	

	return 0;
}
