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

There are also connectors that are functional.
`&&` will run the following command if the previous command succeeded.
`||` will run the following command if the previous command failed.
`;` runs the following command regardless of whether the previous
failed or succeeded.

rshell now includes functional redirection operators: `<`, `>`, `>>`
The input redirection, `<`, takes in an input from a file.
The output redirection, `>`, takes the output, erases the contents of the file,
and saves the output to the file. While, `>>`, takes the output and appends it the end of the file.
To output to stderr use `2>` to to clear then write to the file or `2>>` to append.
Same goes for stdout except use `1>` or `1>>`.

The `cd` command has been included in rshell.

To use it, enter the command `cd [directory]`, which will change your current
working directory to the directory you specified.

`cd` by itself will change the current working directory to your home directory.

`cd -` will change to the previous directory you were in.

rshell is now able to take the `^C` signal and the `^Z` signal.
`^C` will kill the current foreground job, returning to rshell.
`^Z` will suspend the current foreground job, sending it to the background then returning to rshell.
With the inclusion of `^Z`, `fg` and `bg` are also implemented.
`fg` will bring the suspended job to the foreground.
`bg` will send the suspended job to the background.

##Bugs, Limitations and Issues

Although this implementation is able to use many bash commands such as 
`ls`, `echo`, `cat`, and `touch`, it is unable to use the `cd` command.

Using `echo` with `&`, `|`, `;` will output a whitespace. 

Unable to use connectors with redirection operators.

Redirection does not wait for file input if none is specified at
the command line. For example: `cat <` will seg fault.

When using `1>`, `1>>`, `2>`, and `2>>` you cannot use `1` or `2` anywhere
in the file name. rshell currently treats 1 and 2, when using the mentioned
redirection commands, as string delimiters. There is also a seg fault
issue if you try to use a file with `1` or `2` as the first
character of the file name. However, it is fine to use `1` or `2` when using
the redirection commands without specifying the file descriptors. 

Piping command `|` is not currently implemented.
Redirect command `<<<` not implemented.

This implementation is also not set up for the inclusion of parenthesis
used in the command line.

The `cd` command to home does not work with connectors if it precedes a connector.
`fg` and `bg` will not work with connectors if it precedes a connector and will output and error
if used after a connector.
Using `fg` twice in succession will cause an error, killing the second process without bringing it to
the foreground. If there are any other process suspended, it may be left running.

Using `^C` after executing another command will cause `kill` to output an error saying that no process is running.

`^Z` may display error messages after using `fg` and `bg`
`fg` and `bg` are still very buggy. It messes up stdin, stderr, and stdout.

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
You can simply run `ls` by entering the command `bin/ls`. 

To use the flags, you can enter pass the arguments to `bin/ls`.

For example, you can enter`bin/ls -a` to display the hidden files in the directory. 
You can also enter more than one flag by doing `bin/ls -al` or `bin/ls -a -l`, either one works.
Furthermore, you can pass in directory names to see what 
files are in there by doing `bin/ls directory` or if you want to pass
in flags you can do: `bin/ls -a directory`.

The directories are colored in blue, while the executables are colored
in green.
Hidden files have a gray highlighting. 
The display is sorted by alphabetical order ignoring case sensitivity
with `.` files displayed first.


##Known Issues and Bugs with `ls`
When using the `-R` flag, there may be some permission denied errors.
Use of `-R` and `-a` together displays repeats of directories.

The display may not output as neat as it should if long file names or large numbers are displayed. 
When taking flags, it does not output an error when a flag does not exist,
it will simply do regular ls. 
Also if a working flag is in any part of `-`, it will work.
