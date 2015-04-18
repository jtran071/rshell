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
		
		cout << getlogin() << "@" << hostname << " $ ";
		getline(cin, input_cmd);	
	}
	

	return 0;
}
