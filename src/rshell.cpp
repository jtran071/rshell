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
		

		//if exit entered, exit shell
		if(input_cmd == "exit")
		{
			break;
		}	
	}
	

	return 0;
}
