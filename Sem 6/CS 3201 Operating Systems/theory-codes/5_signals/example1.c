#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int sig)
{
    printf(" Hello \n");
    exit(0);
}
int main()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("error:signal");
    pause(); // wait for the handler to catch the signal
    return 0;
}