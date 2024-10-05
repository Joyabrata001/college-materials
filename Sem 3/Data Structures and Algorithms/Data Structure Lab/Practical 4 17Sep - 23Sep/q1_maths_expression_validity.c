#include <stdio.h>
#include <string.h>

char stack[100]; //definition of stack
int top;         //defining top which will be set to 0 later

void push(char a) //push function
{
    if(top == 99)
        printf("Error: Size full\n");
    else
    {
        top++;
        stack[top]= a;   
    }
    
}

char pop() //pop function
{
    if(top == 0)
        printf("Error: Stack already empty");
    else
    {
        char temp = stack[top];
        top --;
        return temp;
    }
    
}

int isValid(char *exp) //this will only consider brackets and will ignore anything else
{
    for(int i=0;i<10;i++) //loop over the whole expression
    {
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{') //pushing starting brackets to stack
            push(exp[i]);
        else if (exp[i] == ')') //checking validity of (
        {
            if(pop() != '(')
                return 0;
        }
        else if (exp[i] == ']') //checking validity of [
        {
            if(pop() != '[')
                return 0;
        }
        else if (exp[i] == '}') //checking validity of }
        {
            if(pop() != '{')
                return 0;
        }
    }
    return 1;
}


void main()
{
    top = 0;

    printf("Enter Expression: "); //Input of expression
    
    char expression[10];
    scanf("%s",expression);

    printf("%d\n",isValid(expression)); //output of isValid()

}