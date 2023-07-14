#include "others.h"

extern char systemname[host_max], username[user_max], home[path_max], path[path_max];
extern char prev_path[path_max];

/*
 * Function for CD
 */
int CD(char **args)
{
    char foo[path_max], curr_path[path_max];
    strcpy(foo, home);

    int l = strlen(home), flag = 1;
    getcwd(curr_path, path_max);
    
    if (args[1] == NULL || strcmp(args[1], "\0") == 0) chdir(home);
    else if(args[1][0] == '-')
    {
        if (chdir(prev_path) != 0) perror("error in cd"), flag = 0;
    }else if (args[1][0] != '~')
    {
        if (chdir(args[1]) != 0) perror("error in cd"), flag = 0;
    } else if (args[1][0] == '~')
    {
        int i = 0;
        for (i = 1; args[1][i] != '\0'; i++)
            foo[i + l - 1] = args[1][i];
        foo[i + l - 1] = '\0';

        if (chdir(foo) != 0) perror("error in cd"), flag = 0;
    } else if (chdir(args[1]) != 0) perror("error in cd"), flag = 0;

    if(flag)
        strcpy(prev_path, curr_path);
    fflush(stdout);
    return 0;
}

/*
 * Function for PWD
 */
int PWD()
{
    char foo[path_max];
    if (getcwd(foo, path_max) == NULL) perror("error in pwd");
    printf("%s\n", foo);

    fflush(stdout);
    return 0;
}

/*
 * Function for ECHO
 */
int ECHO(char **args)
{
    for(int i = 1; args[i] != NULL; i++)
        printf("%s ", args[i]);

    printf("\n");
    fflush(stdout);
    return 0;
}
