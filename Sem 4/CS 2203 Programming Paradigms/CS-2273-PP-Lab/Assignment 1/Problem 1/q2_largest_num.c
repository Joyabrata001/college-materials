#include <stdio.h>

//return largest number in arr
//n is the no. of elements in arr, give max as -inf
int largest_num_recur(int *arr, int n, int max)
{
    if (n == 0)
        return max;

    if (*arr > max)
        max = *arr;

    return largest_num_recur(++arr, n - 1, max);
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

    printf("Max Number: %d\n", largest_num_recur(arr, n, -1000));
}