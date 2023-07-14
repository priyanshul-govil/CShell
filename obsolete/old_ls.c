#include "others.h"
/*
 * External (global in shell.c) variables
 */
extern char systemname[host_max], username[user_max], home[path_max], path[path_max];

/*
 * Function to implement ls [-a]
 * When A = 1, we detect -a flag
 * When A = 0, we execute only ls
 * Respective perror and printf statements included
 */
int LS(char *directory, int A)
{
    struct dirent **LIST;

    int NUM = scandir(directory, &LIST, 0, alphasort);
    if (NUM < 0)
    {
        perror("error in ls");
        return 0;
    }

    for (int i = 0; i < NUM; i++)
    {
        if (LIST[i]->d_name[0] == '.' && A == 0)
            continue;
        else printf("%s\n", LIST[i]->d_name);
    }

    fflush(stdout);
    return 0;
}

/*
 * Function to implement ls -l
 * with all permissions
 * As in the previous case, if A = 1, -a functionality is implemented
 */
int LSL(char *directory, int A)
{
    struct dirent **LIST;
    struct stat ST;

    int NUM = scandir(directory, &LIST, 0, alphasort);
    if (NUM < 0)
    {
        perror("error in ls");
        return 0;
    }

    for (int i = 0; i < NUM; i++)
    {
        char *str = malloc(100 * sizeof(char));
        strcpy(str, directory);
        strcat(str, "/");
        strcat(str, LIST[i]->d_name);

        if (LIST[i]->d_name[0] == '.' && A == 0)
        {
            continue;
        } else if (stat(str, &ST) == 0)
        {
            printf("%c", (S_ISDIR(ST.st_mode)) ? 'd' : '-');
            printf("%c", (ST.st_mode & S_IRUSR) ? 'r' : '-');
            printf("%c", (ST.st_mode & S_IWUSR) ? 'w' : '-');
            printf("%c", (ST.st_mode & S_IXUSR) ? 'x' : '-');
            printf("%c", (ST.st_mode & S_IRGRP) ? 'r' : '-');
            printf("%c", (ST.st_mode & S_IWGRP) ? 'w' : '-');
            printf("%c", (ST.st_mode & S_IXGRP) ? 'x' : '-');
            printf("%c", (ST.st_mode & S_IROTH) ? 'r' : '-');
            printf("%c", (ST.st_mode & S_IWOTH) ? 'w' : '-');
            printf("%c ", (ST.st_mode & S_IXOTH) ? 'x' : '-');

            printf("%2ld ", (unsigned long) (ST.st_nlink));

            printf("%s ", (getpwuid(ST.st_uid))->pw_name);
            printf("%s ", (getgrgid(ST.st_gid))->gr_name);

            printf("%5lld ", (unsigned long long) ST.st_size);

            char timer[14];
            strftime(timer, 14, "%h %d %H:%M", localtime(&ST.st_mtime));
            printf("%s ", timer);

            printf("%s\n", LIST[i]->d_name);
        } else
        {
            perror("error in ls -l");
        }
        free(str);
        str = NULL;
    }

    fflush(stdout);
    return 0;
}

/*
 * The LS main() function with implementation of figuring out the correct absolute path
 * acceptable to scandir.
 * Some restrictions on file names have been put forward.
 */
int LSMAIN(char **args)
{
    int A = 0, L = 0, count = 0;

    for (int i = 1; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "-l") == 0) L = 1, count--;
        else if (strcmp(args[i], "-a") == 0) A = 1, count--;
        else if (strcmp(args[i], "-la") == 0) A = 1, L = 1, count--;
        else if (strcmp(args[i], "-al") == 0) A = 1, L = 1, count--;
        count++;

        int err = 0;
        /*for (int check = 0; check < strlen(args[i]); check++)
        {
            if (args[i][check] >= 'a' && args[i][check] <= 'z');
            else if (args[i][check] >= 'A' && args[i][check] <= 'Z');
            else if (args[i][check] >= '0' && args[i][check] <= '9');
            else if (args[i][check] == '-' || args[i][check] == '/' || args[i][check] == '\0' || args[i][check] == '_');
            else if (args[i][check] == '#' || args[i][check] == '.' || args[i][check] == '*' || args[i][check] == '~');
            else if (args[i][check] == '?' || args[i][check] == '\'' || args[i][check] == '\"');
            else
            {
                err = 1;
                break;
            }
        }*/
        if (err) count--;
    }

    printf("L:%d A:%d count:%d\n", L, A, count);

    if (count == 0)
    {
        if (L == 1) LSL(".", A);
        else LS(".", A);
        return 0;
    }

    for (int i = 1; args[i] != NULL; i++)
    {
        if (args[i][0] == '-') continue;

        int err = 0;
        /*for (int check = 0; check < strlen(args[i]); check++)
        {
            if (args[i][check] >= 'a' && args[i][check] <= 'z');
            else if (args[i][check] >= 'A' && args[i][check] <= 'Z');
            else if (args[i][check] >= '0' && args[i][check] <= '9');
            else if (args[i][check] == '-' || args[i][check] == '/' || args[i][check] == '\0' || args[i][check] == '_');
            else if (args[i][check] == '#' || args[i][check] == '.' || args[i][check] == '*' || args[i][check] == '~');
            else if (args[i][check] == '?' || args[i][check] == '\'' || args[i][check] == '\"');
            else
            {
                err = 1;
                break;
            }
        }*/
        if (err) continue;

        char *rel_path = malloc(path_max * sizeof(char));
        if (getcwd(rel_path, path_max) == NULL) perror("error in cwd");

        char *resolved_path = malloc(path_max * sizeof(char));

        //printf("%s\n", args[i]);

        if (args[i][0] == '~')
        {
            strcpy(rel_path, home);
            int l = strlen(home);

            int ind = 0;
            for (ind = 1; args[i][ind] != '\0'; ind++)
                rel_path[ind + l - 1] = args[i][ind];
            rel_path[ind + l - 1] = '\0';

        } else if (args[i][0] == '/')
        {
            strcpy(rel_path, args[i]);
            strcat(rel_path, "\0");
        } else
        {
            strcat(rel_path, "/");
            strcat(rel_path, args[i]);
            strcat(rel_path, "\0");
        }

        //printf("%s\n", rel_path);
        if (realpath(rel_path, resolved_path) == NULL)
        {
            perror("error in locating directory");
            return 0;
        }
        printf("%s\n", resolved_path);

        if (L == 1) LSL(resolved_path, A);
        else LS(resolved_path, A);

        free(rel_path);
        free(resolved_path);
    }

    fflush(stdout);
    return 0;
}
