#include <stdio.h>

//print L in reverse
//n is the no. of elements in L
void print_reverse_recur(int *L, int n)
{
    if (n == 0)
        return;

    int print = *L;
    print_reverse_recur(++L, n - 1);
    printf("%d ", print);
}

void main()
{
    printf("Enter number of elements: ");
    int n;
    scanf("%d", &n);

    int arr[n];
    printf("Enter Array: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Reverse Array: ");
    print_reverse_recur(arr, n);
    printf("\n");
}