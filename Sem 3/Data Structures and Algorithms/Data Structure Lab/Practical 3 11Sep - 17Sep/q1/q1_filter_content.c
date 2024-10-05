#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char* argv[]){

    //Checking if the command line input is correct or not
    if(argc != 4){
        printf("Error: Wrong Inputs, Please check again\n");
        exit(1);
    }

    FILE *fin;
    FILE *fout;

    fin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");

    //checking if fin and fout are successfully opened or not
    if(fin == NULL)
    {
        printf("Error: Input File couldn't be opened");
        exit(1);
    }
    
    if(fout == NULL)
    {
        printf("Error: Output FIle couldn't be opened");
        exit(1);
    }
    char remove_letter[10];
    strcpy(remove_letter, argv[3]);

    char ch; // this will be the input character

    int is_same = 0; // counter to check if ch is one of the character of argv[3]

    while (!feof(fin)) //this will run till eof is reached
    {
        ch = fgetc(fin);

        //checking if ch has same character as in argv[3]
        for(int i=0;i<strlen(remove_letter);i++)
        {
            if(remove_letter[i] == ' ')
                continue; //avoids ' ' character
            else
            {
                if(remove_letter[i] == ch)
                    is_same = 1;
            } 
        }

        if(is_same == 1)
        {
            is_same =0; //resets is_same so as to make it usable in next loop
        }
        else
        {
            fputc(ch,fout); //put character in outfile
           
        }
        
    }

    //telling user that the file has been created
    printf("%s has been created is the directory\n",argv[2] ); 


    //closing FILE
    fclose(fin);
    fclose(fout);

}