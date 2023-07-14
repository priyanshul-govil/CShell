#include "others.h"

extern char systemname[host_max], username[user_max], home[path_max], path[path_max];

/*
 *The function for PINFO details regarding implementation
 * has been explained in README.md
 */
int PINFO(char **args)
{

    char status[10000] = "/proc/", buff[1000] = "";
    char *final[1000] = {NULL};
    int stat_len = strlen(status);

    if(args[1] == NULL)
    {
        args[1] = malloc(10 * sizeof(char));
        sprintf(args[1], "%d", getpid());
    }

    char a[1000] = "/proc/", b[10] = "/status", c[10] = "/exe";

    int index = 6, flag;
    for (int i = 0; args[1][i] != '\0'; i++) a[index++] = args[1][i];
    for (int i = 0; c[i] != '\0'; i++) a[index++] = c[i];

    for (int i = 0; args[1][i] != '\0'; i++) status[stat_len++] = args[1][i];
    for (int i = 0; b[i] != '\0'; i++) status[stat_len++] = b[i];

    if (readlink(a, buff, sizeof(buff)) == -1) 
    {
        printf("error in readlink: %s", a);
        fflush(stdout);
        return 0;
    }

    int buff_size = 10000 * sizeof(char);
    char *test = malloc(buff_size);

    //printf("%s\n", status);
    int fp = open(status, O_RDONLY);
    if(fp == -1) 
    {
        perror("error in opening file");
        return 0;
    }
    if (read(fp, test, buff_size) == -1) perror("error in read");

    
    char *foo = strtok(test, " \t\n");

    index = 0;
    while (foo != NULL)
        final[index++] = foo, foo = strtok(NULL, " \t\n");

    for(int i = 0; i< index; i++)
    {
        if(strcmp(final[i], "State:") == 0)
            printf("Process Status --- %s\n", final[i + 1]);
        else if(strcmp(final[i], "Pid:") == 0)
            printf("Pid --- %s\n", final[i + 1]);
        else if(strcmp(final[i], "VmSize:") == 0)
            printf("Memory --- %s\n", final[i + 1]);
    }

    free(foo);

    free(test);
    printf("Executable Path --- %s\n", buff);
    fflush(stdout);

    return 0;
}
