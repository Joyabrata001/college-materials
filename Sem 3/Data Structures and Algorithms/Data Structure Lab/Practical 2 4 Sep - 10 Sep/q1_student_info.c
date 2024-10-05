#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
  char fname[20]; // stores the 1st name of thr Student
  char surname[20]; // stores the surname of the Student
  int roll;
};

int comparator(const void *p, const void *q)
{
  int l = ((struct Student*)p) -> roll;
  int r = ((struct Student*)q) -> roll;
  return l-r;
}

void main()
{
  printf("Enter number of students: ");
  int n;
  scanf("%d",&n);

  struct Student ss[n];

  for(int i=0;i<n;i++)
  {
    printf("\nDetails for %d student: \n",i+1);

    char a = getchar(); //remove newline character from the stdin buffer

    printf("First Name: " );
    fgets(ss[i].fname,20,stdin);

    printf("Second Name: ");
    fgets(ss[i].surname,20,stdin);

    printf("Roll number: " );
    scanf("%d",&ss[i].roll);
  }

  int size = sizeof(ss) / sizeof(ss[0]); // variable used only for qsort below

  qsort((void*)ss,size,sizeof(ss[0]),comparator);

  for(int i=0;i<n;i++) // remove trailing \n from all fname and surnames in ss[]
  {
     for(int j=0; j<strlen(ss[i].fname);j++)
        if(ss[i].fname[j] == '\n')
          ss[i].fname[j] = '\0';

      for(int j=0; j<strlen(ss[i].surname);j++)
        if(ss[i].surname[j] == '\n')
          ss[i].surname[j] = '\0';
  }

  printf("NAME                             ROLL\n");

  for(int i=0;i<n;i++)
    printf("%s %s         %d\n",ss[i].fname,ss[i].surname,ss[i].roll);
}
