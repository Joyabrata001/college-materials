#include <stdio.h>

//searchs num in L
//as bool is not there in C, 1 means true, 0 means false
//n is the number of elements in L
int num_search_recur(int *L, int n, int num)
{
    if (n == 0)
        return 0;

    if (*L == num)
        return 1;
    else
        return num_search_recur(++L, n - 1, num);
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

    printf("Enter number to be searched: ");
    int num;
    scanf("%d", &num);

    printf("Output: %d (1 means found, 0 means not found)\n", num_search_recur(arr, n, num));
}