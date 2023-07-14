#include "others.h"

/*
 * The MAIN shell function with:
 * 1. UI() for prompt
 * 2. initialise() for getting user and host names
 * 3. main() which binds the entire shell together decides on the argument input by user
 * and runs/performs the required command
 */

char systemname[host_max], username[user_max], home[path_max], path[path_max];
char prev_path[path_max], curr_path[path_max];
struct Node process[100];
int n_jobs;

int initialise()
{
    gethostname(systemname, host_max);
    getlogin_r(username, user_max);
    getcwd(home, path_max);
    strcpy(prev_path, home);
    return 0;
}

int UI()
{
    int flag = 1;
    getcwd(path, path_max);

    for (int i = 0; i < strlen(home); i++)
        if (home[i] != path[i]) flag = 0;


    char foo[path_max];
    if (flag)
    {
        int i, index = 0;

        foo[index++] = '~';
        for (i = strlen(home); i < strlen(path); i++)
            foo[index++] = path[i];
        foo[index++] = '\0';

        strcpy(path, foo);
    }

    printf("\n<%s@%s:%s>", username, systemname, path);
    fflush(stdout);
    return 0;
}

void execute(char *line)
{
    char *block = strdup(line);

    char *args[100] = {NULL};
    char d[10] = " \t\n";
    parse(line, args, d);

    if (strcmp(args[0], "exit") == 0)
        exit(0);
    else if (strcmp(args[0], "cd") == 0)
        CD(args);
    else if (strcmp(args[0], "setenv") == 0)
        SETENV(args);
    else if (strcmp(args[0], "unsetenv") == 0)
        UNSETENV(args);
    else if (strcmp(args[0], "getenv") == 0)
        GETENV(args);
    else if (strcmp(args[0], "jobs") == 0)
        display_jobs();
    else if (strcmp(args[0], "overkill") == 0)
        job_overkill();
    else 
    {
        int bg_flag = 0;
        for (int i = 1; args[i] != NULL; i++)
        {
            if (strcmp(args[i], "&") == 0)
            {
                bg_flag = 1;
                break;
            }
        }
        if (bg_flag) BGPRO(args);
        //else check_redirection(args);
        else PIPE(block, args);
    }
}

int main(int argc, char *argv[])
{
    int f_stdin = dup(0), f_stdout = dup(1);

    printf("HELLO, THERE! Welocome to CShell :P");
    fflush(stdout);

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGCHLD, FUNC_H);

    initialise();

    while (1)
    {
        UI();
        dup2(f_stdin, 0), dup2(f_stdout, 1);

        size_t buff_size = 1000;
        char *line = (char *) malloc(buff_size * sizeof(char));
        int r_value = read(0, line, buff_size * sizeof(char));

        if(r_value == 0) 
            exit(0);

        line = realloc(line, (sizeof(char) * (r_value + 1)));
        line[r_value] = '\0';

        char *block[20] = {NULL};

        parse(line, block, ";\n");

        for(int i = 0; block[i] != NULL; i++)
        {
            execute(block[i]);
        }

        jobs_updated();
        fflush(stdin), fflush(stderr), fflush(stdout);
    }
}
