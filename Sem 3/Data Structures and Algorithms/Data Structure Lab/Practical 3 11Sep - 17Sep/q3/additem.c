#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
    char itemName[20];
    double unitP;
    double itemQ;
};

void main(int argc, char* argv[])
{
    //checking if command line parameters are ok or not
    if(argc != 5)
    {
        printf("Error: Incorrect Command Line Parameters\n");
        exit(1);
    }

    struct item i;

    //copying argv[] elements to struct item i
    strcpy(i.itemName,argv[2]);
    i.unitP = atof(argv[3]);
    i.itemQ = atof(argv[4]);

    FILE *fout;

    //opening file with append so as to avoid overwriting
    fout = fopen(argv[1],"a"); 

    //checking if fopen is successful or not
    if(fout == NULL)
    {
        printf("Error: File Failed to open");
        exit(1);
    }

    //writing file to argv[1]
    fwrite(&i,sizeof(i),1,fout);

    //closing file
    fclose(fout);

    //printing prompt to user
    printf("changes saved to %s\n", argv[1]);

}