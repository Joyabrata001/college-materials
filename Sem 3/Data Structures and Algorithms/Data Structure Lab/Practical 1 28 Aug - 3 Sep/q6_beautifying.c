#include <stdio.h>
#include <string.h>

void main()
{
  printf("Enter the line: ");
  char line1[100];
  scanf("%[^\n]", line1);

  printf("Length of the output line: ");
  int l;
  scanf("%d", &l);

  int i = 0;

  int rem = l;
  while (line1[i] != '\0' && i < 100)
  {

    char word[20];
    for (int k = 0; k < 20; k++)
      word[k] = '\0';
    int j = 0;

    while (line1[i] != ' ' && j < 20)
    {
      word[j] = line1[i];
      j++;
      i++;
    }

    i++;

    if (strlen(word) > l)
    {
      printf("error : line length to small\n");
      break;
    }
    else if (strlen(word) > rem)
    {
      printf("\n");
      rem = l;
    }

    printf("%s ", word);
    rem = rem - strlen(word) - 1;
  }

  printf("\n");
}
