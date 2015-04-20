# rshell

This is an basic implementation of the bash shell. It is able to take in 
commands through the command line and execute them.

##How to Install

n`$ git clone https://github.com/jtran071/rshell.git`
n`$ cd rshell`
n`$ make`
n`$ bin/rshell`

##Usage
The command format is: `[command] [flag]`
Type in `exit` to exit the shell. As long as `exit` is the first word in
the command line, it will be able to exit the shell.

Anything after `#` is commented out in the command line.

The tab character `\t` is treated as whitespace.

##Bugs, Limitations and Issues

Although this implementation is able to use many bash commands such as 
`ls`, `echo`, `cat`, and `touch`, it is unable to use the `cd` command.

The `&&`, `||`, `;` connectors are currently not working. Anything after
`&`, `|`, `;` is treated as a comment.

Using `echo` with `&`, `|`, `;` will output a whitespace. 

This implementation is also not set up for the inclusion of parenthesis
used in the command line.

Able to run instances of rshell within itself.
