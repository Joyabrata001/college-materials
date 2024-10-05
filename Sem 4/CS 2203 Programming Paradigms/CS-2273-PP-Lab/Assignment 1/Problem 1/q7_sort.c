#include <stdio.h>

//sort arr in incresing order
// n is the number of elements in arr
void sort_recur(int *arr, int n)
{
    if (n == 0)
        return;

    int min = 10000;
    int pos = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] < min)
        {
            pos = i;
            min = arr[i];
        }

    arr[pos] = arr[0];
    arr[0] = min;

    sort_recur(++arr, n - 1);
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

    sort_recur(arr, n);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}