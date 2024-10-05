// The execve() function does not create a new process rather
// it loads and runs a new program in the context of a current process by
// overwriting the address space of the current process; and
// the new program still has the same pid and enjoys the inherietence of
// all the file descriptors that were open at the time of calling execve

#include <stdio.h>
#include <unistd.h>

int main()
{
    int a = 10;
    char *argv[] = {"a", "b", NULL};

    execve("hello", argv, NULL);

    printf("%d\n", a);
    printf("Oi\n");
    printf("Gimme some treatment too UwU\n");
}