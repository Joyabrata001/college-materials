#include <stdio.h>
#include <string.h>

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

void main()
{
    char str[20];
    printf("Enter string (not more than 20 characters): ");
    fgets(str, 20, stdin);

    printf("Enter character to be replaced: ");
    char c1;
    scanf("%c", &c1);
    getc(stdin); //getting the \n out of stdin

    printf("Enter new character: ");
    char c2;
    scanf("%c", &c2);

    replace_occurrences_recur(str, strlen(str), c1, c2);

    printf("Output: %s\n", str);
}