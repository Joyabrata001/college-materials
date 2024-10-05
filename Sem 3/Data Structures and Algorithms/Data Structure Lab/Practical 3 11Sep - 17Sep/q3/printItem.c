#include <stdio.h>
#include <stdlib.h>

struct item 
{
    char itemName[20];
    double unitP;
    double itemQ;
};

void main(int argc, char *argv[])
{
    //checking if command line arguments are ok or not
    if(argc != 3)
    {
        printf("Error: Command Line Parameters are wrong\n");
        exit(1);
    }

    //transferring argv[2] to usable data
    int num = atoi(argv[2]);

    FILE *fin;

    fin = fopen(argv[1],"r");

    struct item i;

    int count = 1;

    while(!feof(fin))
    {
        fread(&i,sizeof(i),1,fin);
        if(count == num)
        {
            printf("Name: %s\nPrice: %lf\nItem No.: %lf\n",i.itemName,i.unitP,i.itemQ);
            break;
        }
        count++;
    }

    //closing file
    fclose(fin);


    if(num > count)
        printf("Error: Item does not exist\n");

}