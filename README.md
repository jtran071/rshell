# rshell

This is an basic implementation of the bash shell. It is able to take in 
commands through the command line and execute them.

##How to Install

1. `$ git clone https://github.com/jtran071/rshell.git`
2. `$ cd rshell`
3. `$ make`
4. `$ bin/rshell`

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

# Implementation of ls

rshell now has its own implementation of ls. The flags it currently supports
are `-a`, `-l`, and `-R`.

To call this implementation of `ls`, however, you must run `bin/ls` (will go
more in detail in the next section), otherwise you will run the bash version
of `ls`.


## How to Install `ls`

1. `git clone https://github.com/jtran071/rshell.git`
2. `cd rshell`
3. `make`
4. `bin/ls`

##Usage
You can simply run `ls` by entering the command `bin/ls`. To use the flags,
you can enter pass the arguments to `bin/ls`. For example, you can enter
`bin/ls -a` to display the hidden files in the directory. You can also 
enter more than one flag by doing `bin/ls -al` or `bin/ls -a -l`, either
one works. Furthermore, you can pass in directory names to see what 
files are in there by doing `bin/ls directory` or if you want to pass
in flags you can do: `bin/ls -a directory`.

The directories are colored in blue, while the executables are colored
in green. Hidden files have a gray highlighting. The display is sorted
by alphabetical order ignoring case sensitivity with `.` files displayed
first.


##Known Issues and Bugs with `ls`
Currently, the `-R` flag is not functioning properly. When you run it,
you will get error saying that the file or directory does not exist. It
may also have a segmentation fault.
The display may not output as neat as it should if long file names or
large numbers are displayed. When taking flags, it does not output an error
when a flag does not exist, it will simply do regular ls. Also if a working 
flag is in any part of `-`, it will work.
