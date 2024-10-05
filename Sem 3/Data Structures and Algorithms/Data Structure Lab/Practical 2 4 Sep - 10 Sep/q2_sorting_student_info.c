#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
  char fname[20]; // stores the 1st name of thr Student
  char surname[20]; // stores the surname of the Student
  int roll;
};

int comparator_roll(const void *p, const void *q)
{
  int l = ((struct Student*)p) -> roll;
  int r = ((struct Student*)q) -> roll;
  return l-r;
}

int comparator_fname(const void* p, const void* q)
{
  return strcmp((const char*)(((struct Student*)p) -> fname), (const char*)(((struct Student*)q) -> fname));
}

int comparator_surname(const void* p, const void* q)
{
  return strcmp((const char*)(((struct Student*)p) -> surname), (const char*)(((struct Student*)q) -> surname));
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

  for(int i=0;i<n;i++) // remove trailing \n from all fname and surnames in ss[]
  {
     for(int j=0; j<strlen(ss[i].fname);j++)
        if(ss[i].fname[j] == '\n')
          ss[i].fname[j] = '\0';

      for(int j=0; j<strlen(ss[i].surname);j++)
        if(ss[i].surname[j] == '\n')
          ss[i].surname[j] = '\0';
  }

  printf("\nEnter f to determine the sorting object:\n");
  printf("1) First Name\n");
  printf("2) Surname\n");
  printf("3) Roll\n");
  printf("Ans> ");
  int f;
  scanf("%d",&f);

  int size = sizeof(ss)/sizeof(ss[0]);

  if(f == 1)
    qsort(ss,size,sizeof(ss[0]),comparator_fname);
  else if(f == 2)
    qsort(ss,size,sizeof(ss[0]),comparator_surname);
  else if(f == 3)
    qsort(ss,size,sizeof(ss[0]),comparator_roll);
  else
    printf("Error: invalid f !\n");

  printf("NAME                             ROLL\n");

  for(int i=0;i<n;i++)
    printf("%s %s         %d\n",ss[i].fname,ss[i].surname,ss[i].roll);
}
