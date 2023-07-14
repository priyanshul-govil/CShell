#include "others.h"

extern char systemname[host_max], username[user_max], home[path_max], path[path_max];

void DO(char **args)
{

    if (strcmp(args[0], "pwd") == 0)
        PWD();
    else if (strcmp(args[0], "echo") == 0)
        ECHO(args);
    else if (strcmp(args[0], "pinfo") == 0)
        PINFO(args);
    else if (strcmp(args[0], "ls") == 0)
        LSMAIN(args);
    else
    {
        if (execvp(args[0], args) == -1)
        {
            perror("error in command");
            return;
        }
    }

    _exit(0);
}

void check_redirection(char **args)
{
	char *str[100] = {NULL};
	int f_stdin = dup(0), f_stdout = dup(1), index = 0;

	int f_arr[2] = {0, 1};
	tokenize_red(args, str, f_arr);

	int f_in = f_arr[0], f_out = f_arr[1];
	dup2(f_in, 0), dup2(f_out, 1);

	int pid = fork();
	if (pid < 0)
    {
    	perror("error in pid");
    	return;
    }
	else if (pid == 0)
	{
	    DO(str);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
    	signal(SIGTSTP, SIG_DFL);
		
		waitpid(pid, NULL, 0);
	    dup2(f_stdin, 0), dup2(f_stdout, 1);
	}

	fflush(stdout);
	return;
}

void PIPE(char *line, char **args)
{
	char *block[20] = {NULL};
	parse(line, block, "|");

	if (block[1] == NULL)
	{
		check_redirection(args);
	}	
	else
	{
		int f_stdin = dup(0), f_stdout = dup(1);
		int f_in = 0, f_out = -1, i = 0;

		for (i = 0; block[i] != NULL; i++)
		{
			if (block[i + 1] == NULL)
				f_out = 1;

			char *arr[50] = {NULL};
			char *str[100] = {NULL};
			parse(block[i], arr, " \t\n");
			
			int f_arr[2] = {0, 1};
			tokenize_red(arr, str, f_arr);
			
			if (i == 0)
				f_in = f_arr[0];
			else if (f_out == 1 && f_arr[1] == 1)
				f_arr[1] = f_stdout;

			int fd[2], id;
			if (pipe(fd) == -1)
			{
				perror("error in piping");
				return;
			}

			if ((id = fork()) < 0)
			{
				perror("error in pid");
				return;
			}
			else if (id == 0)
			{
				/* Child Process */
				signal(SIGINT, SIG_DFL);
	    		signal(SIGTSTP, SIG_DFL);
				
				close(fd[0]);
				
				if(f_out == -1)
					dup2(fd[1], 1);
				else dup2(f_arr[1], 1);
				
				dup2(f_in, 0);
				DO(str);
			}
			else
			{
				/* Parent Process */
				close(fd[1]);
				while(waitpid(id, NULL, WUNTRACED) > 0)
					break;
				f_in = fd[0];
			}
		}

		dup2(f_stdin, 0), dup2(f_stdout, 1);
	}

	fflush(stdout);
	return;
}
