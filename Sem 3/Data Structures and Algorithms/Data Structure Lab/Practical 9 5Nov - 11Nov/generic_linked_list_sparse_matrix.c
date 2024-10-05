//Write Function to support generic linked list and adding functionality for Sparse Matrix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{ //definition of element
    int data;
    int row;
    int col;
} element;

typedef struct node //definition of node
{
    void *data;
    struct node *next;

} node;

typedef struct gll //definition of gll
{
    int dsize;
    struct node *list;
    int (*compareFn)(void *a, void *b);
} gll;

typedef struct gll *genericLL;

int element_compare(void *a, void *b) //compare fuction of elements, acts according to row, the col
{
    if ((((element *)a)->row) == (((element *)b)->row)) //row check
    {
        if ((((element *)a)->col) == (((element *)b)->col)) //if rows equal, then col check
            return 0;
        else if ((((element *)a)->col) < (((element *)b)->col))
            return -1;
        else if ((((element *)a)->col) > (((element *)b)->col))
            return 1;
    }
    else if ((((element *)a)->row) < (((element *)b)->row))
        return -1;
    else if ((((element *)a)->row) > (((element *)b)->row))
        return 1;
}

int int_compare(void *a, void *b) //compare function for int
{

    if (*(int *)a == *(int *)b)
        return 0;
    else if (*(int *)a < *(int *)b)
        return -1;
    else
        return 1;
}

int float_compare(void *a, void *b) //compare function for float
{
    if (*(float *)a == *(float *)b)
        return 0;
    else if (*(float *)a < *(float *)b)
        return -1;
    else
        return 1;
}

int char_compare(void *a, void *b) //compare function for char
{
    if (*(char *)a == *(char *)b)
        return 0;
    else if (*(char *)a < *(char *)b)
        return -1;
    else
        return 1;
}

genericLL createGLL(int dsize, int (*cfunction)(void *, void *)) //makes and inserts node
{
    genericLL g;
    g = (gll *)malloc(sizeof(gll));

    g->dsize = dsize;
    g->list = NULL;
    g->compareFn = cfunction;

    return g;
}

void addNodeGLL(genericLL g, void *d) //add node in the end
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
        g->list = temp;
    else
    {
        node *temp2 = g->list;

        while (temp2->next != NULL)
            temp2 = temp2->next;

        temp2->next = temp;
    }
}

void addNodeGLLSorted(genericLL g, void *d) //add node to make ascending order
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
    {
        g->list = temp;
    }
    else
    {
        if (g->compareFn(temp->data, g->list->data) == -1)
        {
            temp->next = g->list;
            g->list = temp;
        }
        else
        {
            node *current = g->list;
            node *previous = current;

            while (current != NULL && g->compareFn(current->data, temp->data) == -1)
            {
                previous = current;
                current = current->next;
            }

            if (current == NULL)
                previous->next = temp;
            else
            {
                temp->next = current;
                previous->next = temp;
            }
        }
    }
}

int isPresentGLL(genericLL g, void *d) //checks of value present in node
{
    node *temp = g->list;

    int pos = 1;
    int is_found = 0;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            is_found = 1;
            return pos;
        }

        pos++;
        temp = temp->next;
    }

    if (is_found == 0)
        return 0;
}

int deleteNodeGLL(genericLL g, void *d) //deletes node
{
    node *temp = g->list;
    int pos = 1;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            if (temp == g->list)
                g->list = g->list->next;
            else
            {
                node *temp2 = g->list;
                while (temp2->next != temp)
                    temp2 = temp2->next;

                temp2->next = temp->next;
            }

            free(temp);
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    return 0;
}

int getNodeDataGLL(genericLL g, int i, void *d) //give output of ith node
{
    int pos = 1;
    node *temp = g->list;

    while (temp != NULL && pos != i)
    {
        temp = temp->next;
        pos++;
    }
    if (temp == NULL)
        return 0;

    memcpy(d, temp->data, g->dsize);
    return 1;
}

genericLL initMat(int r, int c) //initialises matrix
{
    genericLL g = createGLL(sizeof(element), element_compare); //making a GLL and setting it for struct element

    element *e; //making the first element with matrix config
    e = (element *)malloc(sizeof(element));
    e->data = 0;
    e->row = r;
    e->col = c;

    addNodeGLL(g, (void *)e);

    return g;
}

int addMatElement(genericLL m, struct element e) //add an element in the list
{
    node *config = m->list;      //as config has highest row and col, it will always be on then end of list
    while (config->next != NULL) //going to the config
        config = config->next;

    if (e.row > ((element *)(config->data))->row || e.col > ((element *)(config->data))->col) //checking if its possible to add element in given row and col
        return -1;

    int pos = isPresentGLL(m, (void *)&e); //checking if any element present with same row and col as e

    if (e.row == ((element *)(config->data))->row && e.col == ((element *)(config->data))->col) //as config will have same row and element with the lowermost corner of the matrix, we have a special case
    {                                                                                           //this makes an extra node in the linked list as config, but is present in the second last position of the list

        node *temp = m->list; //making a temp node for traversal to second last pos
        while (temp->next != config)
            temp = temp->next; //traversing to second last pos

        node *new = (node *)malloc(sizeof(node)); //making a new node and assigning it data
        new->data = malloc(m->dsize);
        ((element *)(new->data))->data = e.data;
        ((element *)(new->data))->row = e.row;
        ((element *)(new->data))->col = e.col;

        new->next = config; //changing list to make set the new node in second last pos
        temp->next = new;
        ((element *)(config->data))->data++; //as new node is made, changing the config file
    }
    else if (pos == 0) //if there is no present node with given row and col
    {
        addNodeGLLSorted(m, (void *)&e);
        ((element *)(config->data))->data++;
    }
    else //if there exist a node with given row and col, we have to add the data
    {
        node *temp = (m->list);                             //making a node for traversal
        element *copy = (element *)malloc(sizeof(element)); //making a new node for copying the content of the node with found pos
        getNodeDataGLL(m, pos, copy);                       //copying the node

        while (m->compareFn((void *)temp->data, (void *)copy) != 0) //traversing till pos
        {
            temp = temp->next;
        }

        ((element *)(temp->data))->data = ((element *)(temp->data))->data + e.data; //adding data
        free(copy);                                                                 //freeing copy as its not required
    }

    return 0;
}

genericLL addMat(genericLL m1, genericLL m2) //adds two matrices
{
    node *config1 = m1->list; //finding config of m1
    while (config1->next != NULL)
        config1 = config1->next;

    node *config2 = m2->list; //finding config of m2
    while (config2->next != NULL)
        config2 = config2->next;

    //checking if m1 and m2 has same dimensions or not
    if ((((element *)(config1->data))->row != ((element *)(config2->data))->row) || (((element *)(config1->data))->col != ((element *)(config2->data))->col))
        return NULL;

    genericLL ans = initMat(((element *)(config1->data))->row, ((element *)(config1->data))->col);

    //temporary nodes for traversal
    node *temp1 = m1->list;
    node *temp2 = m2->list;

    while (temp1 != config1 && temp2 != config2)
    {
        if (m1->compareFn((void *)(temp1->data), (void *)(temp2->data)) == -1)
        {
            addMatElement(ans, *((element *)(temp1->data)));
            temp1 = temp1->next;
        }
        else if (m1->compareFn((void *)(temp1->data), (void *)(temp2->data)) == 1)
        {
            addMatElement(ans, *((element *)(temp2->data)));
            temp2 = temp2->next;
        }
        else
        {
            element temp;
            temp.row = ((element *)(temp1->data))->row;
            temp.col = ((element *)(temp1->data))->col;
            temp.data = ((element *)(temp1->data))->data + ((element *)(temp2->data))->data;
            addMatElement(ans, temp);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    if (temp1 == config1)
    {
        while (temp2 != config2)
        {
            addMatElement(ans, *((element *)(temp2->data)));
            temp2 = temp2->next;
        }
    }
    else
    {
        while (temp1 != config1)
        {
            addMatElement(ans, *((element *)(temp1->data)));
            temp1 = temp1->next;
        }
    }

    return ans;
}

void printMat(genericLL m) //prints the matrix in human readable form
{
    //the idea is to convert LL to actual matrix then print it as we do it with 2D arrays
    node *config = m->list; //going to config
    while (config->next != NULL)
        config = config->next;

    //finding rows and cols for the matrix form config
    int rows = ((element *)(config->data))->row;
    int cols = ((element *)(config->data))->col;

    //making an actual 2D array matrix
    int matrix[rows][cols];

    //initializing all the values of matrix to 0
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0;

    //node for traversal of LL
    node *temp = m->list;

    //transforming LL to actual array
    while (temp != config)
    {
        int row = ((element *)(temp->data))->row;
        int col = ((element *)(temp->data))->col;
        matrix[row - 1][col - 1] = ((element *)(temp->data))->data;
        temp = temp->next;
    }

    //printing array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

genericLL subMat(genericLL m1, genericLL m2) //same as addMat() but has a minus (some extra nuisance not included :) )
{
    node *config1 = m1->list;
    while (config1->next != NULL)
        config1 = config1->next;

    node *config2 = m2->list;
    while (config2->next != NULL)
        config2 = config2->next;

    if ((((element *)(config1->data))->row != ((element *)(config2->data))->row) || (((element *)(config1->data))->col != ((element *)(config2->data))->col))
        return NULL;

    genericLL ans = initMat(((element *)(config1->data))->row, ((element *)(config1->data))->col);

    node *temp1 = m1->list;
    node *temp2 = m2->list;

    while (temp1 != config1 && temp2 != config2)
    {
        if (m1->compareFn((void *)(temp1->data), (void *)(temp2->data)) == -1)
        {
            addMatElement(ans, *((element *)(temp1->data)));
            temp1 = temp1->next;
        }
        else if (m1->compareFn((void *)(temp1->data), (void *)(temp2->data)) == 1)
        {
            //if we are printing just the value of m2, we have to make sure it goes with a minus sign
            element temp = *((element *)(temp2->data)); //copying temp to an new structure so as to avoid changing the LL
            temp.data = -temp.data;                     //reversing sign
            addMatElement(ans, temp);
            temp2 = temp2->next;
        }
        else
        {
            element temp;
            temp.row = ((element *)(temp1->data))->row;
            temp.col = ((element *)(temp1->data))->col;
            temp.data = ((element *)(temp1->data))->data - ((element *)(temp2->data))->data;
            addMatElement(ans, temp);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    if (temp1 == config1)
    {
        while (temp2 != config2)
        {
            element temp = *((element *)(temp2->data));
            temp.data = -temp.data;
            addMatElement(ans, temp);
            temp2 = temp2->next;
        }
    }
    else
    {
        while (temp1 != config1)
        {
            addMatElement(ans, *((element *)(temp1->data)));
            temp1 = temp1->next;
        }
    }

    return ans;
}

genericLL multMat(genericLL m1, genericLL m2)
{
    //idea is to convert m1 and m2 to actual 2D array, then do the 2D array multiplication, then changing the matrix to LL

    //traversing to configs of both the matrix
    node *config1 = m1->list;
    while (config1->next != NULL)
        config1 = config1->next;

    node *config2 = m2->list;
    while (config2->next != NULL)
        config2 = config2->next;

    //finding rows and columns of the tro matrix, using configs
    int rows1 = ((element *)(config1->data))->row;
    int cols1 = ((element *)(config1->data))->col;

    int rows2 = ((element *)(config2->data))->row;
    int cols2 = ((element *)(config2->data))->col;

    //checking if matrix multiplication is actually possible or not
    if (cols1 != rows2)
        return NULL;

    int matrix1[rows1][cols1];
    int matrix2[rows2][cols2];

    //initialising value of matrices to zero, to remove initial garbage values
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < cols1; j++)
            matrix1[i][j] = 0;

    for (int i = 0; i < rows2; i++)
        for (int j = 0; j < cols2; j++)
            matrix2[i][j] = 0;

    //adding data of m1(LL) to matrix1(2D Array)
    node *temp = m1->list;

    while (temp != config1)
    {
        int row = ((element *)(temp->data))->row;
        int col = ((element *)(temp->data))->col;
        matrix1[row - 1][col - 1] = ((element *)(temp->data))->data;
        temp = temp->next;
    }

    //adding data of m2(LL) to matrix2(2D Array)
    temp = m2->list;

    while (temp != config2)
    {
        int row = ((element *)(temp->data))->row;
        int col = ((element *)(temp->data))->col;
        matrix2[row - 1][col - 1] = ((element *)(temp->data))->data;
        temp = temp->next;
    }

    int mul_matrix[rows1][cols2];

    //the 2D array multiplication algorithm
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            mul_matrix[i][j] = 0;
            for (int k = 0; k < cols1; k++)
                mul_matrix[i][j] = mul_matrix[i][j] + matrix1[i][k] * matrix2[k][j];
        }
    }

    //changing the matrix to LL
    genericLL ans = initMat(rows1, cols2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            if (mul_matrix[i][j] != 0)
            {
                element temp;
                temp.data = mul_matrix[i][j];
                temp.row = i + 1;
                temp.col = j + 1;

                addMatElement(ans, temp);
            }
        }
    }

    return ans;
}

void freeMat(genericLL m)
{
    //the idea is to first free the LL, then free the genericLL struct
    node *temp;

    //freeing the LL
    while (temp != NULL)
    {
        temp = (m->list->next);
        free(m->list);
        m->list = temp;
    }

    free(m); //freeing the genericLL
}

void main()
{
    //assigning the values to m1
    genericLL m1 = initMat(3, 3);

    element e;

    e.data = 9;
    e.row = 1;
    e.col = 1;
    addMatElement(m1, e);

    e.data = 11;
    e.row = 2;
    e.col = 2;
    addMatElement(m1, e);

    e.data = 22;
    e.row = 3;
    e.col = 2;
    addMatElement(m1, e);

    printf("M1\n");
    printMat(m1); //printing m1
    printf("\n");

    //assigning m2
    genericLL m2 = initMat(3, 3);

    e.data = 9;
    e.row = 1;
    e.col = 2;
    addMatElement(m2, e);

    e.data = 11;
    e.row = 2;
    e.col = 3;
    addMatElement(m2, e);

    e.data = 22;
    e.row = 3;
    e.col = 2;
    addMatElement(m2, e);

    printf("M2\n");
    printMat(m2); //printing m2
    printf("\n");

    genericLL m3 = addMat(m1, m2); //addition

    printf("M3 = M1 + M2\n");
    printMat(m3);
    printf("\n");

    genericLL m4 = subMat(m1, m2); //subtraction

    printf("M4 = M1 - M2\n");
    printMat(m4);
    printf("\n");

    genericLL m5 = multMat(m1, m2); //multiplication

    printf("M5 = M1 * M2\n");
    printMat(m5);
    printf("\n");

    //freeing the genericLL's
    freeMat(m1);
    freeMat(m2);
    freeMat(m3);
    freeMat(m4);
    freeMat(m5);
}