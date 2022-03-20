# minishell
A project where you need to implement the work of the `bash` shell
***
In this project, it was necessary to implement:

> 1 - Not interpret unclosed quotes or unspecified special characters like `\` or `;`
> 
> 2 - Not use more than one global variable, think about it and be ready to explain why
you do it
> 
> 3 - Have a working History
> 
> 4 - Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
> 
> 5 - It must implement the builtins:
> > * `echo` with option -n
> > * `cd` with only a relative or absolute path
> > * `pwd` with no options
> > * `export` with no options
> > * `unset` with no options
> > * `env` with no options or arguments
> > * `exit` with no options
>
> 6 - `’` inhibit all interpretation of a sequence of characters
> 
> 7 - `"` inhibit all interpretation of a sequence of characters except for `$`
> 
> 8 - Redirections:
> > * `<` should redirect input
> > * `>` should redirect output
> > * `<<` read input from the current source until a line containing only the delimiter is seen. It doesn’t need to update history!
> > * `>>` should redirect output with append mode
> 
> 9 - Pipes `|` The output of each command in the pipeline is connected via a pipe to the
input of the next command
> 
> 10 - Environment variables (`$` followed by characters) should expand to their values
> 
> 11 - `$?` should expand to the exit status of the most recently executed foreground
pipeline
> 
> 12 - `ctrl-C` `ctrl-D` `ctrl-\` should work like in bash. When interactive:
> > * `ctrl-C` print a new prompt on a newline
> > * `ctrl-D` exit the shell
> > * `ctrl-\` do nothing

In addition, the following has been implemented:
* `$$` - the process ID of the current shell instance
* Ability to add a command if the last element of the given command is a pipe (example: `ls -l | `)

***
Compilation commands:

`make` - compilation

`make re` - recompilation (deleting everything and compiling again)

`make clean` - deleting object files (.o)

`make fclean` - deleting object files (.o) and executable file
***
Program launch: `./minishell`
***
