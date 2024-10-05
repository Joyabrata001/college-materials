#include <stdio.h>
#include <ctype.h>

void main()
{

  printf("Enter a line: ");

  char std[100];
  scanf("%[^\n]", std);

  int i = 0;
  int count = 0;

  while (std[i] != '\0')
  {
    if (isalpha(std[i]) != 0)
      count++;

    i++;
  }

  printf("Length of the line is %d!\n", count);
}
