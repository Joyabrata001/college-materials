#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
    char fname[20];
    char surname[20];
    int roll;
    struct student *next;
}student;

struct student *addSNode(struct student *start, struct student s)
{
    student* temp;

    temp = (student*) malloc(sizeof(student));

    strcpy(temp->fname,s.fname);
    strcpy(temp->surname, s.surname);
    temp->roll = s.roll;
    temp->next = NULL;
   
    if(start == NULL)
        start = temp;
    else
    {
        student* temp2 = start;

        while(temp2->next != NULL)
            temp2 = temp2->next;

        temp2->next = temp;
    }

    return start;
}

void printLL(struct student *start)
{
    printf("Name \t\t Roll\n");
    do
    {
        printf("%s %s \t %d\n",start->fname,start->surname,start->roll);
        student *temp = start;
        start = start->next;
        free(temp);
    }while(start != NULL);
}

void main()
{
    student *start = NULL;
    
    student s;

    FILE* fin = fopen("data.txt","r");

    while(!feof(fin))
    {
        fscanf(fin,"%s %s %d\n",s.fname,s.surname,&s.roll);
        start = addSNode(start,s);

    }

    printLL(start);

    fclose(fin);
}