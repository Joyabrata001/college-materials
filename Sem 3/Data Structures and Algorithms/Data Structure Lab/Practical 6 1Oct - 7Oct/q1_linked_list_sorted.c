#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
    char fname[20];
    char surname[20];
    int roll;
    struct student *next;
} student;

struct student *addSNodeSorted(struct student *start, struct student s)
{
    student *temp;

    temp = (student *)malloc(sizeof(student));

    strcpy(temp->fname, s.fname);
    strcpy(temp->surname, s.surname);
    temp->roll = s.roll;
    temp->next = NULL;

    if (start == NULL)
        start = temp;
    else if (temp->roll < start->roll)
    {
        temp->next = start;
        start = temp;
    }
    else
    {
        student *temp2 = start;

        while (!((temp2->roll <= temp->roll) && ((temp2->next)->roll >= temp->roll)))
            temp2 = temp2->next;

        temp->next = temp2->next;
        temp2->next = temp;
    }

    return start;
}

void printLL(struct student *start)
{
    printf("Name \t\t Roll\n");
    do
    {
        printf("%s %s \t %d\n", start->fname, start->surname, start->roll);
        student *temp = start;
        start = start->next;
        free(temp);
    } while (start != NULL);
}

int isPresentSNodeSorted(struct student *start, struct student s)
{
    int pos = 1;
    int found = 1;

    student *temp = start;

    do
    {
        if (strcmp(temp->fname, s.fname) == 0 && strcmp(temp->surname, s.surname) == 0 && temp->roll == s.roll)
        {
            found = 0;
            return pos;
        }

        temp = temp->next;
        pos++;
    } while (temp != NULL);

    if (found == 1)
        return 0;
}

struct student *deleteSNodeSorted(struct student *start, struct student s)
{
    student *temp = start;

    do
    {
        if (temp->roll == s.roll)
        {
            if (temp == start)
            {
                start = start->next;
            }
            else
            {
                student *temp2 = start;
                while (temp2->next != temp)
                    temp2 = temp2->next;

                temp2->next = temp->next;
            }

            free(temp);
            return start;
        }

        temp = temp->next;
    } while (temp != NULL);
    return start;
}

void main()
{
    student *start = NULL;

    student s;

    FILE *fin = fopen("data.txt", "r");

    while (!feof(fin))
    {
        fscanf(fin, "%s %s %d\n", s.fname, s.surname, &s.roll);
        start = addSNodeSorted(start, s);
    }

    strcpy(s.fname, "$$$");
    strcpy(s.surname, "$$$");
    s.roll = 10519018;

    start = addSNodeSorted(start, s);

    printLL(start);

    fclose(fin);
}