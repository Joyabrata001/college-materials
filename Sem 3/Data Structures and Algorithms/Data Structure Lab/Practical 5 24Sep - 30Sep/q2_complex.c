#include <stdio.h>
#include <stdlib.h>

typedef struct complex //definition of complex struct
{
    float real;
    float imag;
} complex;

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

        *(complex *)s->data = *(complex *)dp;

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
        *(complex *)dp = *(complex *)(s->data);

        s->data = (char *)s->data - s->dsize;
        s->count--;
        return 1;
    }
}

complex add(complex c1, complex c2) //returns addition of two complex
{
    complex y = {c1.real + c2.real, c1.imag + c2.imag};
    return y;
}

complex sub(complex c1, complex c2) //return difference of two complex
{
    complex y = {c1.real - c2.real, c1.imag - c2.imag};
    return y;
}

complex mul(complex c1, complex c2) //returns product of two complexes
{
    complex y = {c1.real * c2.real, c1.imag * c2.imag};
    return y;
}

void main()
{
    gstack stk = create_gstack(10, sizeof(complex)); //defining and making stack

    //defining complexes, can be changed
    complex c1 = {63, 324};
    complex c2 = {54, 497};
    complex c3 = {32, 197};

    char expression[] = "c1 c2 c3 + *"; //defining expression, can be changed

    int i = 0; //array counter for expression[]

    while (expression[i] != '\0') //postfix evaluation algorithm
    {
        char x = expression[i];

        if (x == 'c')
        {
            i++;
            if (expression[i] == '1') //as word are of type c1, c2, comparing the next character after c to determine complex
                push_gstack(&stk, &c1);
            if (expression[i] == '2')
                push_gstack(&stk, &c2);
            if (expression[i] == '3')
                push_gstack(&stk, &c3);
        }
        else
        {
            if (expression[i] == '+')
            {
                complex a, b;
                pop_gstack(&stk, &a);
                pop_gstack(&stk, &b);
                complex c = add(a, b);
                push_gstack(&stk, &c);
            }
            if (expression[i] == '-')
            {
                complex a, b;
                pop_gstack(&stk, &a);
                pop_gstack(&stk, &b);
                complex c = sub(a, b);
                push_gstack(&stk, &c);
            }
            if (expression[i] == '*')
            {
                complex a, b;
                pop_gstack(&stk, &a);
                pop_gstack(&stk, &b);
                complex c = mul(a, b);
                push_gstack(&stk, &c);
            }
        }
        i++;
    }

    complex ans;
    pop_gstack(&stk, &ans); //end result

    //printing to console c1,c2,c3
    printf("c1 = (%f) + i(%f)\n", c1.real, c1.imag);
    printf("c2 = (%f) + i(%f)\n", c2.real, c2.imag);
    printf("c3 = (%f) + i(%f)\n", c3.real, c3.imag);
    //printing expression
    printf("\nExpression = %s\n\n", expression);
    //printing ans
    printf("ans = (%f) + i(%f)\n", ans.real, ans.imag);

    //freeing the stack
    free_gstack(&stk);
}