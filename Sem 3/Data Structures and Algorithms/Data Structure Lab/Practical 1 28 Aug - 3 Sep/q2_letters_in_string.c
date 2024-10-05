#include <stdio.h>
#include <ctype.h>

void main()
{
  char str[25];

  printf("Enter a string: ");
  scanf("%s",str);

  int count = 0;

  int i=0;

  while(str[i] != '\0')
  {
    if(isalpha(str[i]) != 0)
      count++;

    i++;
  }

  printf("The number of English letters in the string ");
  printf("%c%s%c",'"',str,'"');
  printf(" is %d\n",count);
}
