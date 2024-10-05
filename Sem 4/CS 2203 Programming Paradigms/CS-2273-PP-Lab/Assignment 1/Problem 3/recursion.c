#include <stdio.h>

//compare strings s1, and s2
//len1 is the length of s1, len2 is the length of s2
//return 0 if s1 and s2 is same, return 1 if s1>s2, else -1
int string_comp_recur(char *s1, int len1, char *s2, int len2)
{

    if (len1 == 0 && len2 == 0)
        return 0;
    else if (len1 == 0 && len2 > 0)
        return -1;
    else if (len1 > 0 && len2 == 0)
        return 1;

    if (*s1 == *s2)
        return string_comp_recur(++s1, len1 - 1, ++s2, len2 - 1);
    else
    {
        int diff = *s1 - *s2;
        if (diff < 0)
            return -1;
        else
            return 1;
    }
}

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

//searchs num in L
//as bool is not there in C, 1 means true, 0 means false
//n is the number of elements in L
//returns 0 
int num_search_recur(int *L, int n, int num)
{
    if (n == 0)
        return 0;

    if (*L == num)
        return 1;
    else
        return num_search_recur(++L, n - 1, num);
}

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

//checks if s in palindrome or not
//as bool is not there in C, 1 means true, 0 means false
//len is string length, give pos as 0
int check_palindrome_recur(char *s, int len, int pos)
{
    if (2 * pos > len)
        return 1;

    if (s[pos] == s[len - 1 - pos])
        return check_palindrome_recur(s, len, pos + 1);
    else
        return 0;
}

//replaces all occurrences of c1 by c2
//len is the string length
void replace_occurrences_recur(char *s, int len, char c1, char c2)
{
    if (len == 0)
        return;

    if (*s == c1)
        *s = c2;

    replace_occurrences_recur(++s, len - 1, c1, c2);
}

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