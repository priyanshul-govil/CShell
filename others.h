/*
This is the "others.h" file which contains all the header files
required for the entire project (in its current disposition),
along with the function definitions used throughout,
as well as several macros used in the project.
*/

//HEADER FILES
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <limits.h>

//MACROS
#define host_max 100
#define user_max 100
#define path_max 100000

struct Node
{
	pid_t pid;
	char *name;
	int stat;
};

//set and unset environment variables
void SETENV(char **args);
void UNSETENV(char **args);
void GETENV(char **args);

//Parser
void parse(char *line, char **args, char *d);

//Separator for redirection
void tokenize_red(char **args, char **str, int f[]);

//Check Redirection
void check_redirection(char **args);

//Do Stuff I Guess
void DO(char **args);

//Piping
void PIPE(char *line, char **args);

//Function for cd
int CD(char **args);

//Function for pwd
int PWD();

//Function for echo
int ECHO(char **args);

//Function for pinfo
int PINFO(char **args);

//Function for ls [-a]
int LS(char *directory, int A);

//Function for ls -l [-a]
int LSL(char *directory, int A);

int LSMAIN(char **args);

int BGPRO(char **args);

//SIGNAL HANDLING
void FUNC_H(int signum);

//Jobs stuff
void jobs_updated();
void status_update(pid_t pid, int status);
void display_jobs();
void job_overkill();
char* process_name(pid_t pid);
