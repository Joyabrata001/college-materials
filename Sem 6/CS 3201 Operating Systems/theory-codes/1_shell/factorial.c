#include <stdio.h>
#include <stdlib.h>

long long factorial(int n)
{
    long long res = 1;

    for (int i = 2; i <= n; i++)
        res *= i;

    return res;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Error: Provide a number(s)\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
        printf("%lld ", factorial(atoll(argv[i])));

    printf("\n");
}