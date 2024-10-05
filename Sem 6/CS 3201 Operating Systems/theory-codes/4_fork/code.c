#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid;
    int x = 1;
    pid = fork(); /* A wrapper for fork() explained shorly */
    if (pid == 0)
    { /* child */
        printf("Child: x= %d\n", ++x);
        // exit(0);
    }
    /* Parent */
    printf(" Parent: x = %d\n", --x);
    exit(0);
}