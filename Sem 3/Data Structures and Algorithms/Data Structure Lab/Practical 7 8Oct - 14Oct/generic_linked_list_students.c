//Write Function to support generic linked list and use it to make linked list for students

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    char fname[20];
    char surname[20];
    int roll;
    struct student *next;
} student;

typedef struct node //definition of node
{
    void *data;
    struct node *next;

} node;

typedef struct gll //definition of gll
{
    int dsize;
    struct node *list;
    int (*compareFn)(void *a, void *b);
} gll;

typedef struct gll *genericLL;

int student_compare(void *a, void *b) //compare function for int
{

    if (((student *)a)->roll == ((student *)b)->roll)
        return 0;
    else if (((student *)a)->roll < ((student *)b)->roll)
        return -1;
    else
        return 1;
}

genericLL createGLL(int dsize, int (*cfunction)(void *, void *)) //makes and inserts node
{
    genericLL g;
    g = (gll *)malloc(sizeof(gll));

    g->dsize = dsize;
    g->list = NULL;
    g->compareFn = cfunction;

    return g;
}

void addNodeGLL(genericLL g, void *d) //add node in the end
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
        g->list = temp;
    else
    {
        node *temp2 = g->list;

        while (temp2->next != NULL)
            temp2 = temp2->next;

        temp2->next = temp;
    }
}

void addNodeGLLSorted(genericLL g, void *d) //add node to make ascending order
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
    {
        g->list = temp;
    }
    else
    {
        if (g->compareFn(temp->data, g->list->data) == -1)
        {
            temp->next = g->list;
            g->list = temp;
        }
        else
        {
            node *temp2 = g->list;

            while (!(((g->compareFn(temp2->data, temp->data) == -1) || g->compareFn(temp2->data, temp->data) == 0) && g->compareFn(temp2->next->data, temp->data) == 1))
                temp2 = temp2->next;

            temp->next = temp2->next;
            temp2->next = temp;
        }
    }
}

int isPresentGLL(genericLL g, void *d) //checks of value present in node
{
    node *temp = g->list;

    int pos = 1;
    int is_found = 0;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            is_found = 1;
            return pos;
        }

        pos++;
        temp = temp->next;
    }

    if (is_found == 0)
        return 0;
}

int deleteNodeGLL(genericLL g, void *d) //deletes node
{
    node *temp = g->list;
    int pos = 1;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            if (temp == g->list)
                g->list = g->list->next;
            else
            {
                node *temp2 = g->list;
                while (temp2->next != temp)
                    temp2 = temp2->next;

                temp2->next = temp->next;
            }

            free(temp);
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    return 0;
}

int getNodeDataGLL(genericLL g, int i, void *d) //give output of ith node
{
    int pos = 1;
    node *temp = g->list;

    while (temp != NULL && pos != i)
    {
        temp = temp->next;
        pos++;
    }
    if (temp == NULL)
        return 0;

    memcpy(d, temp->data, g->dsize);
    return 1;
}

void main()
{
    genericLL g = createGLL(sizeof(student), student_compare);

    student a;
    strcpy(a.fname, "$$$");
    a.roll = 1;
    strcpy(a.surname, "$$$");
    addNodeGLL(g, (void *)&a);
    printf("list = a\n");

    student b;
    strcpy(b.fname, "Abhiroop");
    b.roll = 3;
    strcpy(b.surname, "Mukherjee");
    addNodeGLL(g, (void *)&b);
    printf("list = a->b\n");

    student c;
    strcpy(c.fname, "Alpha");
    c.roll = 2;
    strcpy(c.surname, "Beta");
    addNodeGLLSorted(g, (void *)&c);
    printf("list = a->c->b\n");

    student d;
    strcpy(d.fname, "Gamma");
    d.roll = 4;
    strcpy(d.surname, "Delta");
    addNodeGLL(g, (void *)&d);
    printf("list = a->c->b->d\n");

    printf("isPresentNode for c: %d\n", isPresentGLL(g, &c));

    printf("deleteNodeGLL() for b : %d\n", deleteNodeGLL(g, &b));
    printf("list = a->c->d\n");

    student *ptr = (student *)malloc(sizeof(student));
    getNodeDataGLL(g, 3, (void *)ptr);
    printf("Doing getNodeDataGLL for pos 3\n");
    printf("ptr->fname: %s\n", ptr->fname);
    printf("ptr->surname: %s\n", ptr->surname);
    printf("ptr->roll: %d\n", ptr->roll);
}