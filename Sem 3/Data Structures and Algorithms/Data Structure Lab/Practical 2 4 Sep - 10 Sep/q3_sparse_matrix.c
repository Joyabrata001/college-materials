#include <stdio.h>
#include <stdlib.h>

struct element{
    int data;
    int row;
    int col;
};

int addMatrix(struct element m1[], struct element m2[], struct element m3[])
{   
    //Checking if there is size mismatch
    if(m1[0].col != m2[0].col && m1[0].row != m2[0].row)
        return 0;

    int counter =1; //for keeping track of m3[]

    //adding all the element of m1[] and m2[] with same coordinates
    for(int i=1;i<= m1[0].data;i++)
        for(int j=1;j<=m2[0].data;j++)
        {
            if(m1[i].col == m2[j].col && m1[i].row == m2[j].row)
            {
                m3[counter].col = m1[i].col;
                m3[counter].row = m1[i].row;
                m3[counter].data = m1[i].data + m2[j].data;
                counter++;

                //declaring everything zero so as they do not interfere below
                m1[i].col =0;
                m1[i].col =0;
                m1[i].data =0;
                m2[j].col =0;
                m2[j].row =0;
                m2[j].data =0;
            }
        }

    //putting all non common element of m1[] in m3[]
    for(int i=1;i<=m1[0].data;i++)
    {
        if (m1[i].data == 0)
            continue;
        else
        {
            m3[counter].col = m1[i].col;
            m3[counter].row = m1[i].row;
            m3[counter].data = m1[i].data;
            counter++;

            m1[i].col =0;
            m1[i].col =0;
            m1[i].data =0;
        }
    }

    //putting all non common element of m2[] in m3[]
    for(int j=1;j<=m2[0].data;j++)
    {
        if (m2[j].data == 0)
            continue;
        else
        {
            m3[counter].col = m2[j].col;
            m3[counter].row = m2[j].row;
            m3[counter].data = m2[j].data;
            counter++;

            m2[j].col =0;
            m2[j].col =0;
            m2[j].data =0;
        }
    }

    //defining matrix characteristics of m3[] in m3[0]
    m3[0].col = m1[0].col;
    m3[0].row = m1[0].row;
    m3[0].data = counter-1;

    //outputtihn m3[] in matrix form in console
    int m = m3[0].row;
    int n = m3[0].col;
    int output[m][n];

    //decalring every element as zero to remove previous garbage value
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            output[i][j] = 0;

    //putting value of m3[] in output matrix
    for(int i=1;i<=m3[0].data;i++)
    {
        output[m3[i].row -1][m3[i].col -1] = m3[i].data;
    }

    //printing output
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d\t",output[i][j]);
        printf("\n");
    }

    return 1;
}

void main()
{   //Initialization of m1[]
    printf("\nEnter data for Matrix 1:\n");
    printf("Enter no. of non zero numbers: ");
    int a; 
    //initially used int a as we don't know the size of m1
    scanf("%d",&a);
    //declaring m1[]
    struct element* m1 = (struct element*)calloc(a+1,sizeof(struct element));
    m1[0].data = a;
    printf("Enter the number of Rows: ");
    scanf("%d",&m1[0].row);
    printf("Enter number of cols: ");
    scanf("%d", &m1[0].col);

    //input of values of m1
    for(int i=1;i<=(m1[0].data);i++)
    {
        printf("\nContent of element %d:\n",i);
        printf("Data: ");
        scanf("%d",&m1[i].data);
        printf("Row: ");
        scanf("%d",&m1[i].row);
        printf("col: ");
        scanf("%d",&m1[i].col);
    }


    //Initialization of m2[]
    printf("\nEnter data for Matrix 2:\n");
    printf("Enter no. of non zero numbers: ");
    scanf("%d",&a);
    struct element* m2= (struct element*)calloc(a+1,sizeof(struct element));
    m2[0].data = a;
    printf("Enter the number of Rows: ");
    scanf("%d",&m2[0].row);
    printf("Enter number of cols: ");
    scanf("%d", &m2[0].col);

    // Input of values of m2[]
    for(int i=1;i<=(m2[0].data);i++)
    {
        printf("\nContent of element %d:\n",i);
        printf("Data: ");
        scanf("%d",&m2[i].data);
        printf("Row: ");
        scanf("%d",&m2[i].row);
        printf("col: ");
        scanf("%d",&m2[i].col);
    }

    //declaring m3[], that will have at most the size of m1 and m2
    struct element* m3 = (struct element*)calloc(m1[0].data + m2[0].data, sizeof(struct element));

    //functionCall
    a = addMatrix(m1,m2,m3);

    //Error Output
    if(a == 0)
        printf("Size Mismatch\n");
}



   





