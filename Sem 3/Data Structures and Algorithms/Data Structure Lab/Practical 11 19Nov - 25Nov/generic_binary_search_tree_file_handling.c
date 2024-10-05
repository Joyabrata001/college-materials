#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gbst //definition of gbst
{
    int dsize;
    void (*printNode)(void*);
    int (*compareFn)(void*,void*);
    struct bstnode *root;
}gbst;

typedef gbst* genericBST;   //typedef to fit question 

typedef struct bstnode  //definition of bstnode
{
    void* data;
    struct bstnode *lchild;
    struct bstnode *rchild;
}bstnode;

int compareFn_int(void *a, void* b)     //compare function of int
{
    if ( *((int*)(((bstnode*)a)->data)) == *((int*)(((bstnode*)b)->data)) )
        return 0;
    else if ( *((int*)(((bstnode*)a)->data)) > *((int*)(((bstnode*)b)->data)) )
        return 1;
    else  
        return -1;
    
}

void printNode_int(void* node)  //print node for int
{
    printf("%d ", *((int*)((bstnode*)node)->data) );
}

genericBST createGBST(int dsize, int (*cfunction)(void *, void *), void (*printNode)(void*))    //will create base for a gst, with NULL root
{
    genericBST g;
    g = (gbst*)malloc(sizeof(gbst));
    g->dsize = dsize;
    g->compareFn = cfunction;
    g->printNode = printNode;

    return g;
}

struct bstnode* searchGBST(genericBST gt, void *d, bstnode** par)   //this function outputs the pointer to found node, as well as its parent to par
{
    if(gt->root == NULL)    //tree empty
        return NULL;
    else
    {
        bstnode* temp = gt->root;
        bstnode* prev = NULL;

        while(temp!= NULL)
        {
            if(gt->compareFn((void*)temp,d)==0) //node found
            {    
                *par = prev;
                return temp;
            }
            else if(gt->compareFn((void*)temp,d)==1)    //value < node value, i.e go left
            {
                prev = temp;
                temp = temp->lchild;
            }
            else        //value > node value, i.e go right
            {
                prev = temp;
                temp = temp->rchild;
            }
            
        }
        return prev;
    }  
}

void insertNodeGBST(genericBST gt, void *d) //inserts a node with its data being d
{
    //making node
    bstnode* a;
    a = (bstnode*)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data,d,gt->dsize);    //copying data from d to a->data
    a->lchild = NULL;
    a->rchild = NULL;

    bstnode* par;

    bstnode* temp = searchGBST(gt,a,&par);  

    if(temp == NULL)
        gt->root = a;
    else if(gt->compareFn(temp,a) == 1)
        temp->lchild = a;
    else
        temp->rchild = a;
    

}

void in_order(genericBST gt,bstnode* t) //prints in order
{
    if(t != NULL)
    {
        in_order(gt,t->lchild);
        gt->printNode((void*)t);
        in_order(gt,t->rchild);        
    }
}

void pre_order(genericBST gt,bstnode* t)    //prints pre order
{
    if(t != NULL)
    {
        gt->printNode((void*)t);
        pre_order(gt,t->lchild);
        pre_order(gt,t->rchild);        
    }
}

void post_order(genericBST gt,bstnode* t)   //prints post order
{
    if(t != NULL)
    {
        post_order(gt,t->lchild);
        post_order(gt,t->rchild);    
        gt->printNode((void*)t);    
    }
}

int traverseGBST(genericBST gt, int order)  //traverse the tree according to given order
{
    if(gt->root == NULL)
        return 0;

    if(order == 0)
        in_order(gt,gt->root);
    else if(order == 1)
        pre_order(gt,gt->root);
    else if(order == 2)
        post_order(gt,gt->root);

    return 1;
}

void free_node(bstnode* node)   //frees the node given
{
    free(node->data);
    free(node);
}

void del_case_A(bstnode * root,bstnode* loc, bstnode* par)  //case for no or one child
{
    bstnode* child;

    if(loc->lchild == NULL && loc->rchild == NULL)
        child = NULL;
    else if( loc->lchild != NULL )
        child = loc->lchild;
    else
        child = loc->rchild;

    if(par!= NULL)
    {
        if(loc == par->lchild)
            par->lchild = child;
        else
            par->rchild = child;
    }
    else
        root = child;
}

void del_case_B(bstnode * root,bstnode* loc, bstnode* par)  //case for two childs
{
    bstnode *suc,*par_suc,*ptr,*save;

    ptr = loc->rchild;

    while(ptr->lchild != NULL)
    {
        save = ptr;
        ptr = ptr->lchild;
    }
    
    suc = ptr;
    par_suc = save;

    del_case_A(root,suc,par_suc);

    if(par!= NULL)
    {
        if(loc = par->lchild)
            par->lchild = suc;
        else
            par->rchild = suc;
    }
    else
        root = suc;

    suc->lchild = loc->lchild;
    suc->rchild = loc->rchild;
}

int deleteNodeGBST(genericBST gt, void *d)      //delets a node if any, with its data = d
{
    bstnode* a;
    a = (bstnode*)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data,d,gt->dsize);
    a->lchild = NULL;
    a->rchild = NULL;

    bstnode* par;
    bstnode* loc;
    
    loc = searchGBST(gt,a,&par);

    if(loc == NULL)
    {
        printf("Item Not Found");
        return -1;
    }

    if(loc->lchild != NULL && loc->rchild != NULL)
        del_case_B(gt->root,loc,par);
    else
        del_case_A(gt->root,loc,par);

    free_node(loc);
}

void pre_order_export(genericBST gt,bstnode* t,FILE* fout)  //exports the tree in pre_order format. done as pre order reconstruction of tree is same as original
{
    if(t != NULL)
    {
        fwrite(t->data,gt->dsize,1,fout);
        pre_order_export(gt,t->lchild,fout);
        pre_order_export(gt,t->rchild,fout);        
    }
}

int exportGBST(genericBST gt, const char *fname)    //exports tree to fname
{
    FILE* fout = fopen(fname,"w");  

    if(fout == NULL)    
    {
        printf("Error: File can't be opened");
        return 0;
    }

    if(gt->root == NULL)
        return 0;

    fwrite(gt,sizeof(gbst),1,fout);     //first write content of gt

    pre_order_export(gt,gt->root,fout);     //then writes the whole tree in pre_order format

    fclose(fout);
}

int setPrintNodeFnGBST(genericBST gt,  void (*pn)(void*))   //set print function of given gt to pn
{
    if ((pn == NULL) || (gt == NULL))
        return 0;
    
    gt->printNode = pn;
    return 1;
}

int setCompareFnGBST(genericBST gt,  int (*cf)(void*,void*))    //sets compare fn. of given gt to cf
{
    if ((cf == NULL) || (gt == NULL))
        return 0;

    gt->compareFn = cf;
    return 1;
}

genericBST importGBST(const char *fname, int (*cf)(void *, void *), void (*pn)(void*))  //imports tree from fname, with compare fn as cf and print function as pn
{
    genericBST gt;
    gt = (gbst*)malloc(sizeof(gbst));

    FILE* fin = fopen(fname,"r");

    fread(gt,sizeof(gbst),1,fin);   //first element is gt, so reading it
    setPrintNodeFnGBST(gt,pn);      //setting gt's print fn.
    setCompareFnGBST(gt,cf);        //setting gt's compare fn.
    gt->root = NULL;                //previous address is now invalid, so making it null

    
    void* data = malloc(gt->dsize);

    while(fread(data,gt->dsize,1,fin))
    {
        insertNodeGBST(gt,data);  //inserting node as per the file, as file node data has been written in pre_order format, the copied tree will be same as original
    }

    free(data);   //freeing data, as it has served it's purpose
    return gt;    //returning the made gt

}

void main()
{   
    genericBST gt = createGBST(sizeof(int),compareFn_int,printNode_int);

    int a[9] = {100,50,40,30,60,110,109,120,55};

    for(int i = 0;i<9;i++)
    {
        insertNodeGBST(gt, (void*)&a[i]);
    }

    printf("pre_order for gt1:\n");
    traverseGBST(gt,1);
    printf("\n\n");

    char file_name[] = "data.dat";
    printf("Exporting data to '%s' \n\n",file_name);
    exportGBST(gt,file_name);

    printf("Importing data from '%s' to gt2\n\n",file_name);
    genericBST gt2 = importGBST(file_name,compareFn_int,printNode_int);
    printf("pre_order for gt2:\n");
    traverseGBST(gt2,1);
    printf("\n\n");

    printf("Inserting 111 in gt2:\n");
    int temp = 111;
    insertNodeGBST(gt2,(void*)&temp);
    printf("pre_order for gt2:\n");
    traverseGBST(gt2,1);
    printf("\n\n");

    printf("removing 111 from gt2\n");
    deleteNodeGBST(gt2,(void*)&temp);
    printf("pre_order for gt2:\n");
    traverseGBST(gt2,1);
    printf("\n\n");

    printf("Inserting 70 in gt2:\n");
    temp = 70;
    insertNodeGBST(gt2,(void*)&temp);
    printf("pre_order for gt2:\n");
    traverseGBST(gt2,1);
    printf("\n\n");

    printf("Removing 50 form gt2, which have 2 childs\n");
    temp = 50;
    deleteNodeGBST(gt2,(void*)&temp);
    printf("pre_order for gt2:\n");
    traverseGBST(gt2,1);
    printf("\n\n");
}

