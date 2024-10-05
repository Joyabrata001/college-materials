#include <stdio.h>
long long factorial(int n)
{
    if (n == 1)
        return 1;
    if (n == 5)
        printf("n = 5 reached for debugger\n");
    if (n == 3)
        printf("n = 3 reached for debugger\n");
    return (long long)n * factorial(n - 1);
}
int main()
{
    int value = 10;
    printf("factorial of %d is %lld\n", value, factorial(value));
    return 0;
}