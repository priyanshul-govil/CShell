#include "others.h"

extern struct Node process[100];
extern int n_jobs;

void SETENV(char **args)
{
	int flag = 0, count = 0;
	for (int i = 0; args[i] != NULL; i++) 
		count++;

	if(count == 2)
	{
		args[2] = strdup("");
		if(setenv(args[1], args[2], 1) == -1)
		{
			perror("error in setenv");
			return;
		}
	}
	else if (count == 3)
	{
		if(setenv(args[1], args[2], 1) == -1)
		{
			perror("error in setenv");
			return;
		}
	}
	else
	{
		perror("missing/extra parameters");
		return;
	}
}

void UNSETENV(char **args)
{
	int flag = 0, count = 0;
	for (int i = 0; args[i] != NULL; i++) 
		count++;

	if(count == 2)
	{
		if(unsetenv(args[1]) == -1)
		{
			perror("error in unsetenv");
			return;
		}
	}
	else
	{
		perror("missing/extra parameters");
		return;
	}
}

void GETENV(char **args)
{
	int flag = 0, count = 0;
	for (int i = 0; args[i] != NULL; i++) 
		count++;

	if(count == 2)
	{
		if(getenv(args[1]) == NULL)
		{
			perror("error in getenv");
			return;
		}
		printf("%s\n", getenv(args[1]));
	}
	else
	{
		perror("missing/extra parameters");
		return;
	}
}

void jobs_updated()
{
	struct Node dup[100];
	int index = 0;

	for (int i = 0; i < n_jobs; i++)
	{
		if (kill(process[i].pid, 0) == -1) continue;

		dup[index].pid = process[i].pid, dup[index].name = process_name(process[i].pid);
		dup[index].stat = process[i].stat;
		index += 1;
	}
	for (int i = 0; i < index; i += 1)
		process[i].pid = dup[i].pid, process[i].name = dup[i].name, process[i].stat = dup[i].stat;

	n_jobs = index;
}

void status_update(pid_t pid, int status)
{
	for (int i = 0; i < n_jobs; i++)
	{
		if (process[i].pid == pid)
			process[i].stat = status;
	}
}

void display_jobs()
{
	jobs_updated();	

	for (int i = 0; i < n_jobs; i++)
	{
		printf("[%d] ", (i + 1));
		if (WIFEXITED(process[i].stat)) continue;
		else if(WIFSTOPPED(process[i].stat))
			printf("Stopped %s [%d]\n", process[i].name, process[i].pid);
		else
			printf("Running %s [%d]\n", process[i].name, process[i].pid);
	}

	fflush(stdout);
	return;
}

void job_overkill()
{
	for(int i = 0; i < n_jobs; i++)
	{
		pid_t pid = process[i].pid;
		if(kill(pid, SIGKILL) == -1)
		{
			perror("kill:");
			return;
		}
	}
	jobs_updated();
}

char* process_name(pid_t pid)
{
	size_t buffer_size = 100;
	char *proc_stat = (char *)malloc(sizeof(char) * 50);
	sprintf(proc_stat, "/proc/%d/status", pid);
	int fd = open(proc_stat, O_RDONLY);
	if(fd == -1)
		return '\0';

	char *str = (char *) malloc(sizeof(char)*buffer_size);
	int read_value = read(fd, str, buffer_size);
	if (read_value == -1)
	{
		perror("read");
		return '\0';
	}

	char delim[10] = " \t\n";
	char *name = strtok(str, delim);
	name = strtok(NULL, delim);
	close(fd);
	return name;
}