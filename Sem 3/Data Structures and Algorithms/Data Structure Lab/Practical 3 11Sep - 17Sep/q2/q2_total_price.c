#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    //checking if command line arguments are ok or not
    if(argc != 2)
    {
        printf("Error: Wrong Command Line Parameters\n");
        exit(1);
    }

    FILE *fin;

    fin = fopen(argv[1],"r");

    //checking if file is opened successfully or not
    if(fin == NULL)
    {
        printf("Error: File couldn't be opened\n");
        exit(1);
    }

    float sum =0; //this will be the output value
    float price,rate; //these are the values to be read
    char name[10];  //this is the value to be read

    while(fscanf(fin,"%s\t%f\t%f\n",name,&price,&rate) != EOF)
    {
        sum = sum + price*rate;
    }

    float del = 0.0003; //made to compensate slight errors in the float
    if((-del)<sum && sum<del) //checking        -del < sum < del
        printf("Error: Input File does not contain a valid Shopping List\n");
    else
        printf("Rs. %f\n",sum);
}
