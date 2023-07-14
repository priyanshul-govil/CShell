#include "others.h"

/*
 *This file deals with functions related to running foreground
 * and background processes BGPRO() for background
 * and sends the process/command into foreground or background respectively
 */


int BGPRO(char **args)
{
    int status, pid;
    char *arr[1000] = {NULL};

    arr[0] = malloc(100 * sizeof(char));
    strcpy(arr[0], args[0]);

    for (int i = 1; args[i] != NULL && strcmp(args[i], "&") != 0; i++)
    {
        arr[i] = strdup(args[i]);
    }


    if ((pid = fork()) < 0)
    {
        perror("error in fork");
        return 0;
    }

    if (pid)
    {
        return 0;
    }
    else
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        
        if (setpgid(0, 0) == -1)
        {
            perror("error in orphaning child");
            return 0;
        }

        if (execvp(arr[0], arr) == -1)
        {
            perror("error in command");
            return 0;
        }
        _exit(0);
    }

    return 0;
}
