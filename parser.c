#include "others.h"

void parse(char *line, char **args, char *d)
{
    int index = 0;
    char *END;
    char *foo = strtok_r(line, d, &END);

    while (foo != NULL)
    {
        args[index] = foo, foo = strtok_r(NULL, d, &END);
        index += 1;
    }
    fflush(stdout);
}

void tokenize_red(char **args, char **str, int f[])
{
	int index = 0;

	for (int i = 0; args[i] != NULL; i++)
	{
		if (args[i][0] == '<')
		{
			f[0] = open(args[i + 1], O_RDONLY);
			if (f[0] == -1)
			{
				perror("error in opening file");
				return;
			}
			i++;
		}
		else if (args[i][0] == '>')
		{
			if (sizeof(args[i]) > (int)(2 * sizeof(char)) && args[i][1] == '>')
			{
				f[1] = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (f[1] == -1)
				{
					perror("error in creating/opening file");
					return;
				}
			}
			else
			{
				f[1] = creat(args[i + 1], 0644); 
				if (f[1] == -1)
				{
					perror("error in creating/opening file");
					return;
				}
			}
			i++;
		}
		else
		{
			str[index++] = strdup(args[i]); 
		}
	}
}