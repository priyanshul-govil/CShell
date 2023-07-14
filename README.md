# CShell

- Made by Priyanshul Govil. 
- Help/suggestions taken from codereview@SE and stackoverflow@SE.
- Completed the basic functionality in a duration of 2 days (i.e., work done till 10/09/21).
- Updates to follow.

## Prompt

A Basic Shell implemented in C. The `prompt` displays the USERNAME and HOSTNAME along with the relative path of the 
directory you are in, wrt the location of the executable.

## Features

1. `pwd`: Displays the name of the working directory. Implemented as `PWD()` in `spec2.c`.

2. `ls [-l -a] [directory]`: List all files and folders in a specified directory in alphabetical order. Implemented 
in `ls.c`.

3. `cd [directory]`: Changes directory to the directory specified, throws an error if the directory does not exist. 
Implemented as `CD()` in `spec2.c`.

4. `echo [arguments]`: Displays whatever is specified in `[arguments]`.
    
A very basic implementation of ECHO has been performed ignoring the vitalities and possibilities of the actual 
ECHO command. Environment variables, for example, can't be echoed, i.e., `echo $USER` doesn't work. Implemented 
as `ECHO()` in `spec2.c`.

5. `exit`: Exits the shell. Implemented in `shell.c`.

6. `pinfo [pid]`: Returns details of the task mentioned as PID. If PID is not mentioned then it operates on `a.out`, 
i.e., the specified shell program executable.
    
This has been implemented by scrapping `/proc/[PID]/exec` and `/proc/[PID]/status`. Absolute Executable Path has 
also been printed for the user's benefit. Implemented in `pinfo.c`.

**N.B:** Unnecessary spaces, tabs etc. have been accounted for in LS, CD, PWD and ECHO. Regarding LS, position 
of `[directory]` and `[flags]` are invariant wrt the result. 

## Foreground and Background Processes
1. All other commands are treated as system commands like emacs, vim, clear etc.
2. To run a process in the background, follow the command with a '&' symbol. Eg. emacs &. Implemented by orphaning 
the child process.

Implemented in `syscmd.c`. Used FORK and EXECVP commands to get the work done.

## Signal Handling
1. When the background process terminates it's PID and EXIT STATUS are shown.
2. INTERRUPT and TERMINATE signals have also been well inplemented.
3. [UPDATED] Handled ^C and ^Z in order to let them work as intended on foreground process without letting 
them affect the shell as a whole from exitting/stopping the shell from being executed.

**N.B:** Why name of the process is not returned upon termination of the background process?
Reason: It is highly unsafe to use malloc() inside the respective `signal_handler()` functions. `fprintf` is 
relatively stable and thus has been used only to directly print the PID associated. Printing the name of the 
process has been ignored.

Implemented in `handle.c` under the function `FUNC_H()`.

## Piping and Redirection

1. Implemented I/O redirection in the file `pipe_red.c`.
2. Implemented muti-piping facility for the shell. This can be used along with I/O redirection now. Look in 
`pipe_red.c` for details of implementation.

## User-Defined Commands

Several user-defined commands have also been implemented. They include setenv, unsetenv, jobs, kjob, overkill,
quit/exit and many more. 


## Issues
1. Extreme stress testing to be performed to look for SIGSEGV.
3. Look into signal handling security issues.
