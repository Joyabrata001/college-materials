#include "types.h"
#include "user.h"

int main(int argc, char **argv)
{

    if (fork() == 0)
        printf(1, "child process\n");
    else
    {
        wait();
        printf(1, "parent process\n");
    }

    exit();
}