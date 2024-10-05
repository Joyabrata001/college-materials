#include <stdio.h>
#include <string.h>

//compare strings s1, and s2
//len1 is the length of s1, len2 is the length of s2
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

void main()
{
    char str1[20];
    printf("Enter str1(not more than 20 letters): ");
    fgets(str1, 20, stdin);

    char str2[20];
    printf("Enter str2(not more than 20 letters): ");
    fgets(str2, 20, stdin);

    printf("Output: %d ", string_comp_recur(str1, strlen(str1), str2, strlen(str2)));
    printf("(0 if str1 and str2 is same, 1 if str1>str2, else -1)\n");
}