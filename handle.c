#include "others.h"

void FUNC_H(int signum)
{
    int PID = getpid(), status;

    if (signum == SIGINT)
    {
        /*
        * Handle interrupt in particular
        */
        fprintf(stderr, "\nprocess with pid:%d interrupted\n", PID);
        fflush(stderr);
        fflush(stdout);
        exit(1);
    } else if (signum == SIGCHLD)
    {
        jobs_updated();
        /*
         * Child handling in particular with associated status and PID
         */
        while ((PID = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
        {
            if (WIFEXITED(status))
                fprintf(stderr, "\npid: %d exited, status = %d\n", PID, WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                fprintf(stderr, "\npid: %d killed by signal %d\n", PID, WTERMSIG(status));
            else if (WIFSTOPPED(status))
                fprintf(stderr, "\npid: %d stopped by signal %d\n", PID, WSTOPSIG(status));
            else if (WIFCONTINUED(status))
                fprintf(stderr, "\npid: %d continued\n", PID);
            
            status_update(PID, status);
            return;
        }
    }
}