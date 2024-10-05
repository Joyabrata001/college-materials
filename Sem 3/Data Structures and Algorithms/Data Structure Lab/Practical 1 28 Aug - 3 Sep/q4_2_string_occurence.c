#include <stdio.h>

void main()
{
  printf("Enter the 1st string: ");
  char line1[10];
  scanf("%s",line1);

  printf("Enter the 2st string: ");
  char line2[10];
  scanf("%s",line2);

  char maxCountLetter = '\0';
  int maxCount = 0;

  for( int i=0; line2[i] != '\0' ; i++)
  {
    char countLetter = line2[i];
    int count =0;

    for( int j=0; line1[j] != '\0' ; j++ )
    {
      if(line1[j] == countLetter )
        count++;
    }

    if(count > maxCount)
    {
      maxCountLetter = countLetter;
      maxCount = count;
    }
  }

  printf("\'%c\' of \"%s\" is occuring %d times in \'%s\'\n",maxCountLetter,line2,maxCount,line1);
}
