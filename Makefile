CFLAGS = -Wall -Werror -pedantic -std=c++11

all: rshell ls cp

rshell: bin
	g++ $(CFLAGS) src/rshell.cpp -o bin/rshell

cp: bin
	g++ $(CFLAGS) src/cp.cpp -o bin/cp
 
ls: bin
	g++ $(CFLAGS) src/ls.cpp -o bin/ls
 
bin:
	mkdir bin
  
clean:
	rm -rf bin
