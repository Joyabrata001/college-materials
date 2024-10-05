#include <stdio.h>
#include <string.h>

void main()
{
  printf("Enter the line: ");
  char line1 [100];
  scanf("%[^\n]",line1);
  int size = strlen(line1);

  printf("Enter the string to be dropped: ");
  char sub[10];
  scanf("%s",sub);


  char line2[10];
  //for(int i=0;i<10;i++)
    //line2[i] = ' ';
  int pos =0;

  int len = strlen(sub);

  for(int i=0; i<size; i++)
  {
    if(line1[i] == sub[0])
    {
      char substring[len];

      for(int j=0;j<len;j++)
        substring[j] = line1[i+j];

      if(strcmp(sub,substring) == 0)
        i = i+len;
    }

    if(line1[i]!= '\0')
      {
        line2[pos] = line1[i];
        pos++;
      }

  }

  line2[pos] = '\0';

  printf("%s\n",line2);
}
