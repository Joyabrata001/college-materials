#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    char temp[50];
    for(int i=0;i<argc-1;i++)
        for(int j=0;j<argc-i-1;j++)
            if(strcmp(argv[j] , argv[j+1]) > 0)
            {
                strcpy(temp,argv[j]);
                strcpy(argv[j],argv[j+1]);
                strcpy(argv[j+1],temp);
            }




    for(int i=0;i<argc;i++)
        printf("%s\n",argv[i]);
}