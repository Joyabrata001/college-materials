#include <stdio.h>
#include <string.h>

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

void main()
{
    char str[20];
    printf("Enter string (not more than 20 characters): ");
    fgets(str, 20, stdin);
    str[strcspn(str,"\n")] = '\0';
    //strcspn() calculates the length of the number of characters before the 1st occurrence of character present in both the string.

    printf("Output: %d (1 means string is palindrome, 0 means not palindrome) \n", check_palindrome_recur(str, strlen(str), 0));
}