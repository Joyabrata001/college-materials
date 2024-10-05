//Write Function to support generic linked list with file handling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node //definition of node
{
    void *data;
    struct node *next;

}node;

typedef struct gll  //definition of gll
{
    int dsize;
    struct node *list;
    int (*compareFn)(void* a, void* b) ;  
}gll;

typedef struct gll* genericLL;  

int int_compare (void* a, void* b) //compare function for int
{
        
    if( *(int*)a == *(int*)b )
        return 0;
    else if( *(int*)a < *(int*)b )
        return -1;
    else 
    return 1;      
}

int float_compare(void * a, void *b)    //compare function for float
{
    if( *(float*)a == *(float*)b )
        return 0;
    else if( *(float*)a < *(float*)b )
        return -1;
    else 
        return 1;    
}

int char_compare (void *a, void*b)      //compare function for char
{
    if( *(char*)a == *(char*)b )
        return 0;
    else if( *(char*)a < *(char*)b )
        return -1;
    else 
        return 1;
}

genericLL createGLL(int dsize, int (*cfunction)(void *, void *)) //makes Generic Linked List
{
    genericLL g;
    g = (gll*)malloc(sizeof(gll)); 

    g->dsize = dsize;
    g->list = NULL;
    g->compareFn = cfunction;

    return g;
}

void addNodeGLL(genericLL g, void *d)       //add node in the end
{
    node* temp = (node*) malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data,d,g->dsize);
    temp -> next = NULL;

    if(g->list == NULL)
        g->list = temp;
    else
    {
        node* temp2 = g->list;

        while(temp2->next != NULL)
            temp2 = temp2->next;

        temp2->next = temp;
    }
 
}

void addNodeGLLSorted(genericLL g, void *d)     //add node to make ascending order
{
    node* temp = (node*) malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data,d,g->dsize);
    temp -> next = NULL;

    if( g->list == NULL)
    {
        g->list = temp;
    }
    else
    {   
        if(g->compareFn(temp->data,g->list->data) == -1)
        {
            temp -> next = g->list;
            g->list = temp;
        }
        else
        {
            node* current = g->list;
            node* previous = current;

            while(current != NULL && (g->compareFn(current->data,previous->data) == -1 || g->compareFn(current->data,previous->data) == 0 ))
            {
                previous = current;
                current = current->next;
            }

            if (current == NULL)
                previous -> next = temp;
            else
            {
                temp->next = current;
                previous ->next = temp;
            }
        }
        
        /*if(g->dsize == sizeof(int))
        {
            if(*(int*)(temp -> data) < *(int*)(g-> list -> data))
            {
                temp -> next = g->list;
                g->list = temp;
            }
            else
            {
                node* temp2 = g->list;

                while(!((*(int*)(temp2->data) <= *(int*)(temp->data)) && (*(int*)((temp2->next)->data) >= *(int*)(temp->data)))) 
                    temp2 = temp2->next;

                temp->next = temp2->next;
                temp2->next = temp;
            }
        }
        else if (g->dsize == sizeof(float))
        {
            if(*(float*)(temp -> data) < *(float*)(g-> list -> data))
            {
                temp -> next = g->list;
                g->list = temp;
            }
            else
            {
                node* temp2 = g->list;

                while(!((*(float*)(temp2->data) <= *(float*)(temp->data)) && (*(float*)((temp2->next)->data) >= *(float*)(temp->data)))) 
                    temp2 = temp2->next;

                temp->next = temp2->next;
                temp2->next = temp;
            }
        }
        else if( g->dsize == sizeof(char))
        {
            if(*(char*)(temp -> data) < *(char*)(g-> list -> data))
            {
                temp -> next = g->list;
                g->list = temp;
            }
            else
            {
                node* temp2 = g->list;

                while(!((*(char*)(temp2->data) <= *(char*)(temp->data)) && (*(char*)((temp2->next)->data) >= *(char*)(temp->data)))) 
                    temp2 = temp2->next;

                temp->next = temp2->next;
                temp2->next = temp;
            }
        }*/
    }
}

int isPresentGLL(genericLL g, void *d)      //checks of value present in node
{
    node* temp = g->list;

    int pos = 0;
    int is_found = 0;

    while(temp != NULL)
    {
        if(g->compareFn(temp->data,d) == 0) 
        {
            is_found = 1;
            return pos;
        }

        pos++;
        temp = temp->next;
    }

    if(is_found == 0)
        return 0;
}

int deleteNodeGLL(genericLL g, void *d)     //deletes node
{
    node* temp = g->list;
    int pos =0 ;

    while(temp != NULL)
    {
        if(g->compareFn(temp->data,d) == 0) 
        {
            if (temp == g->list)
                g->list = g->list->next;
            else
            {
                node* temp2 = g->list;
                while(temp2->next != temp)
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

int getNodeDataGLL(genericLL g, int i, void *d)     //give output of ith node
{
    int pos = 1;
    node* temp = g->list;

    while(temp != NULL && pos != i-1)
    {
        temp = temp->next;
        pos++;
    }
    if(temp == NULL)
        return 0;
    
    memcpy(d,temp->data,g->dsize);
    return 1;
    
}

void exportGLL(genericLL g, FILE *fp)           //exports the content of the genericLL g to a file pointed by fp
{
    fwrite(g,sizeof(gll),1,fp); //writing contents of g to file

    while(g->list != NULL)  //writing data of linked list to file
    {
        fwrite(g->list->data,g->dsize,1,fp);
        node* temp = g->list;
        g->list = g->list->next;
        free(temp);
        
        
    }
}

genericLL importGLL( FILE *fp)          //imports the content of file pointed by fp to a genericLL and returns it
{
    genericLL g;    //the genericLL which will be returned
    g = (gll*)malloc(sizeof(gll)); 
    

    fread(g,sizeof(gll),1,fp);  //reading the contents of g from file
    g -> list = NULL;   //as new linked list is being formed, no need of old list
    g->compareFn = NULL;    //the old pointer value is now invalid, so making it NULL to avoid issues

    node* temp;     //making a node for using it for fread()
    temp = (node*) malloc(sizeof(node));
    temp->data = malloc(g->dsize);

    while(fread(temp->data,g->dsize,1,fp)) //reading data from file and making it linked list
    {
        temp->next = NULL;
        addNodeGLL(g,temp->data);
    }

    free(temp->data); //as temp is not needed now, freeing it
    free(temp);

    return g;
}

void setCompareFn(genericLL g, int (*compFn)(void *, void*))        //sets g->compareFn to compFn
{
    g->compareFn = compFn;
}

void print_all(genericLL g)     //prints all the value of the linked list of g as is
{
    printf("LIST : ");
    node* temp = g ->list;

    while(temp != NULL)
    {
        printf("%d->",*(int*)temp->data);
        temp=temp->next;
    }

    printf("NULL\n\n");
}

void main()
{
    printf("Made Generic Stack of int\n\n");
    genericLL g = createGLL(sizeof(int), int_compare);  //makes stack

    printf("adding 1 in linked list (with sort)\n");
    int a = 1;
    addNodeGLLSorted(g,&a);
    print_all(g);       

    printf("adding 3 in linked list (with sort)\n");
    int b = 3;
    addNodeGLLSorted(g,&b); 
    print_all(g);    

    printf("adding 2 in linked list (with sort)\n");
    int c = 2;
    addNodeGLLSorted(g,&c);
    print_all(g);   

    printf("adding 4 in linked list \n");
    int d = 4;
    addNodeGLL(g,&d);
    print_all(g);          

    /*
    printf("isPresentNode for 2: %d\n",isPresentGLL(g,&c));

    printf("deleteNodeGLL() for 3 : %d\n",deleteNodeGLL(g,&b));
    printf("list = 1->2->4\n");  

    int* ptr = (int*)malloc(sizeof(int));
    getNodeDataGLL(g,3,(void*)ptr);
    printf("getNodeDataGLL for 3: %d\n",*ptr);
    */
    

    printf("Exporting file to data.dat\n\n");
    FILE* fp;
    fp = fopen("data.dat","w");

    if(fp == NULL)
    {
        printf("Error: File can't be opened");
        exit(1);
    }
    exportGLL(g,fp);
    fclose(fp);


    printf("Importing file from data.dat\n\n");
    fopen("data.dat","r");
    if(fp == NULL)
    {
        printf("Error: File can't be opened");
        exit(1);
    }
    g = importGLL(fp);
    fclose(fp);
    setCompareFn(g,int_compare);

    printf("Imported Output: \n");
    print_all(g);


    


}   