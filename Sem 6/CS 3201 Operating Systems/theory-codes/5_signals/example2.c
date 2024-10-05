#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void signal_handler(int sig)
{
    printf("Handler: Hello\n");
}
int main()
{
    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
        perror("error:signal");
    printf("Main\n");
    raise(SIGUSR1); // send a signal to the calling process
    return 0;
}