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


bool do_exec(vector<char*> &arg)
{
	int status;
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
		if(-1 == waitpid(-1, &status, 0))
		{
			perror("waitpid()");
			exit(1);
		}
		if(status != 0)
		{
			return false;
		}
	}
	return true;
}



int main()
{
	char hostname[256];
	char *login_info;
	if(gethostname(hostname, 256) == -1)
	{
		perror("hostname()");
	}

	login_info = getlogin();
	if(login_info == NULL)
	{
		perror("getlogin()");
	}
	while(1)
	{
		string input_cmd;
		list<string> parse_list;
		bool conn_semi_c = false;
		bool conn_and = false;
		bool conn_or = false;
		bool exec_check = false;


		//outputs user login and host name along with command prompt
		cout << login_info << "@" << hostname << "$ ";
		
		//takes in commands
		getline(cin, input_cmd);
		
		//parse command input
		char_separator<char> delim(" \t","#;&|");
		tokenizer< char_separator<char> > mytok(input_cmd, delim);
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			parse_list.push_back(*it);
		}
	
				
		vector<string> cmd_line;
		vector<char*> arg(parse_list.size() + 1);
		list<string> cmd_list;

		string exit_flag = parse_list.front();
		
		//push only the commands, saving connectors in list
		while(!(parse_list.empty()) && parse_list.front() != "#" && 
				parse_list.front() != ";" && parse_list.front() != "&" && 
				parse_list.front() != "|")
		{
			cmd_line.push_back(parse_list.front());
			cmd_list.push_back(parse_list.front());
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
		

		
		while(!(cmd_list.empty()))
		{
			
			if(parse_list.front() == "#")
			{
				cmd_list.clear();
				exec_check = do_exec(arg);
			}
			else if(parse_list.front() == ";")
			{
				conn_semi_c = true;
				parse_list.pop_front();
			}
			else if(parse_list.front() == "&")
			{
				parse_list.pop_front();
				if(parse_list.front() == "&")
				{
					conn_and = true;
					parse_list.pop_front();
				}
				else{
					conn_and = false;
					cout << "Error: Invalid connector." << endl;
					break;
				}
			}
			else if(parse_list.front() == "|")
			{
				parse_list.pop_front();
				if(parse_list.front() == "|")
				{
					conn_or = true;
					parse_list.pop_front();
				}
				else{
					conn_or = false;
					cout << "Error: Invalid connector." << endl;
					break;
				}
			}
			else{
				exec_check = do_exec(arg);
				cmd_list.pop_front();
				break;
			}
			

			if(conn_semi_c == true)
			{
				exec_check = do_exec(arg);
				cmd_list.pop_front();
			}
			if(conn_and == true && exec_check == true)
			{
				exec_check = do_exec(arg);
				cmd_list.pop_front();
			}
			if(conn_or == true && exec_check == false)
			{
				exec_check = do_exec(arg);
				cmd_list.pop_front();
			}	
			
		}		

	}

	return 0;
}
