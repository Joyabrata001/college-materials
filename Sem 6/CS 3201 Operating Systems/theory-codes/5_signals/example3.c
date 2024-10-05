#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sig_handler_parent(int signum)
{
    printf("Parent : Received a response signal from child \n");
}
void sig_handler_child(int signum)
{
    printf("Child : Received a signal from parent \n");
    sleep(1);
    kill(getppid(), SIGUSR1);
}
int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Fork Failed\n");
        exit(1);
    }
    else if (pid == 0)
    {                                       /* Child Process */
        signal(SIGUSR1, sig_handler_child); // Register signal handler
        printf("Child: waiting for signal\n");
        pause();
    }
    else
    {                                        /* Parent Process */
        signal(SIGUSR1, sig_handler_parent); // Register signal handler
        sleep(1);
        printf("Parent: sending signal to Child\n");
        kill(pid, SIGUSR1);
        printf("Parent: waiting for response\n");
        pause();
    }
    return 0;
}