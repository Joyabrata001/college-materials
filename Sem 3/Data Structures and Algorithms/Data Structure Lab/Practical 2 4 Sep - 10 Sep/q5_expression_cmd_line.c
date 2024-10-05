#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{

    int temp;
    int a;
    int b;

    int ans =0;

    int i=1;
    
    while(i<argc)
    {  
        temp = atoi(argv[i]);

        if(temp == 0)
        {
            i++;
            b = atoi(argv[i]);

            if(strcmp(argv[i-1],"+") == 0)
                ans = ans + (a+b);
            else if(strcmp(argv [i-1],"-") == 0)
                ans = ans + (a-b);
            else
                printf("Not coded for handling * and /, sorry\n");


        }

        a = temp ;

        i++;
    }

    printf("%d\n",ans);
}