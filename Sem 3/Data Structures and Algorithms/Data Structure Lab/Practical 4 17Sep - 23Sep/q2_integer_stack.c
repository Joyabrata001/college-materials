#include <stdio.h>
#include <stdlib.h>

typedef struct s //typedeffing made structure to match the condition in the question
{
    int size;
    int count;
    int *data;
} stack;

int is_integer_stack_full(stack s) //checking if the stack is full or not
{
    if (s.count < s.size)
        return 0;
    else
        return 1;
}

int is_integer_stack_empty(stack s) //checking if the stack is empty or not
{
    if (s.count == 0)
        return 1;
    else
        return 0;
}

int free_integer_stack(stack *s) //freeing the data inside the structure s
{
    free(s->data);
}

stack create_integer_stack(int stack_size)
{
    stack s; //defining initial values
    s.size = stack_size;
    s.count = 0;
    s.data = (int *)malloc(sizeof(int) * (stack_size + 1)); //allocating data for s.data

    if (s.data != NULL) //checking if malloc worked or not
        return s;
}

int push_integer_stack(stack *s, int d)
{
    if (!is_integer_stack_full(*s)) //checking if stack is full or not
    {
        s->count++;
        s->data++;
        *s->data = d;
        return 1;
    }
    else //otherwise print error
    {
        printf("Error: Size Full\n");
        return 0;
    }
}

int pop_integer_stack(stack *s, int *dp)
{
    if (is_integer_stack_empty(*s)) //checking of stack is empty or not
    {
        printf("Error: Stack already empty");
        return 0;
    }
    else
    {
        *dp = *s->data;
        s->data--;
        s->count--;
        return 1;
    }
}

void main()
{
    stack numb = create_integer_stack(10); //defining and making stack

    //pushing values
    push_integer_stack(&numb, 5);  //stack is {5}
    push_integer_stack(&numb, 10); //stack is {5,10}
    push_integer_stack(&numb, 10); //stack is {5,10,10}

    int a; //value made for printf

    pop_integer_stack(&numb, &a); //stack is {5,10}, with a =10
    printf("%d\n", a);            //output a = 10

    pop_integer_stack(&numb, &a); //stack is {5}, with a =10
    printf("%d\n", a);            //output a = 10

    pop_integer_stack(&numb, &a); //stack is empty, with a =5
    printf("%d\n", a);            //output a = 5
}