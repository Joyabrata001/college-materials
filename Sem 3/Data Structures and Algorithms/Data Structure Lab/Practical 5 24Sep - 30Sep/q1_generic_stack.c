#include <stdio.h>
#include <stdlib.h>

typedef struct //typedeffing made structure to match the condition in the question
{
    int size;
    int dsize;
    int count;
    void *data;
} gstack;

int is_gstack_full(gstack s) //checking if the stack is full or not
{
    if (s.count < s.size)
        return 0;
    else
        return 1;
}

int is_gstack_empty(gstack s) //checking if the stack is empty or not
{
    if (s.count == 0)
        return 1;
    else
        return 0;
}

int free_gstack(gstack *s) //freeing the data inside the structure s
{
    free(s->data);
    s->count = 0;
    s->dsize = 0;
    s->size = 0;
}

gstack create_gstack(int stack_size, int data_size)
{
    gstack g; //defining initial values
    g.size = stack_size;
    g.dsize = data_size;
    g.count = 0;
    g.data = (void *)malloc(data_size * (stack_size + 1)); //allocating data for s.data

    if (g.data != NULL) //checking if malloc worked or not
        return g;
}

int push_gstack(gstack *s, void *dp)
{
    if (!is_gstack_full(*s)) //checking if stack is full or not
    {
        s->count++;
        s->data = (char *)s->data + s->dsize;

        if (s->dsize == sizeof(int))      //these if statement check the data type of
            *(int *)s->data = *(int *)dp; //the stack according to dsize
        else if (s->dsize == sizeof(char))
            *(char *)s->data = *(char *)dp;
        else if (s->dsize == sizeof(float))
            *(float *)s->data = *(float *)dp;

        return 1;
    }
    else //otherwise print error
    {
        printf("Error: Size Full\n");
        return 0;
    }
}

int pop_gstack(gstack *s, void *dp)
{
    if (is_gstack_full(*s)) //checking of stack is empty or not
    {
        printf("Error: Stack already empty");
        return 0;
    }
    else
    {

        if (s->dsize == sizeof(int))        //these if statement check the data type of
            *(int *)dp = *(int *)(s->data); //the stack according to dsize
        else if (s->dsize == sizeof(char))
            *(char *)dp = *(char *)(s->data);
        else if (s->dsize == sizeof(float))
            *(float *)dp = *(float *)(s->data);

        s->data = (char *)s->data - s->dsize;
        s->count--;
        return 1;
    }
}

void main()
{
    gstack stk = create_gstack(10, sizeof(char)); //defining and making stack

    //pushing values
    char b = 'a';
    char c = 'b';

    push_gstack(&stk, &b); //stack is {a}
    push_gstack(&stk, &c); //stack is {a,b}
    push_gstack(&stk, &c); //stack is {a,b,b}

    char a; //value made for printf

    pop_gstack(&stk, &a); //stack is {a,b}, with a =b
    printf("%c\n", a);    //output a = b

    pop_gstack(&stk, &a); //stack is {5}, with a = b
    printf("%c\n", a);    //output a = b

    pop_gstack(&stk, &a); //stack is empty, with a = a
    printf("%c\n", a);    //output a = a

    free_gstack(&stk);
}