CFLAGS = -Wall -Werror -pedantic -std=c++11

all: rshell

rshell: bin
	g++ $(CFLAGS) src/rshell.cpp -o bin/rshell
  
bin:
	mkdir bin
  
clean:
	rm -rf bin
