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

using namespace std;
using namespace boost;


int main()
{
	char hostname[256];
	gethostname(hostname, 256);

	while(1)
	{
		string input_cmd;
		
		//FIXME: Doesn't output after fg
		//	
		//outputs user login and host name along with command prompt
		cout << getlogin() << "@" << hostname << "$ ";

		//takes in commands
		getline(cin, input_cmd);

		

		//if exit entered, exit shell
		if(input_cmd == "exit")
		{
			break;
		}	
	}
	

	return 0;
}
