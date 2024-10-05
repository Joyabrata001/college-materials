#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gbst
{
    int dsize;
    void (*printNode)(void*);
    int (*compareFn)(void*,void*);
    struct bstnode *root;
}gbst;

typedef gbst* genericBST;

typedef struct bstnode
{
    void* data;
    struct bstnode *lchild;
    struct bstnode *rchild;
}bstnode;

int compareFn_int(void *a, void* b)
{
    if ( *((int*)(((bstnode*)a)->data)) == *((int*)(((bstnode*)b)->data)) )
        return 0;
    else if ( *((int*)(((bstnode*)a)->data)) > *((int*)(((bstnode*)b)->data)) )
        return 1;
    else  
        return -1;
    
}

void printNode_int(void* node)
{
    printf("%d ", *((int*)((bstnode*)node)->data) );
}

genericBST createGBST(int dsize, int (*cfunction)(void *, void *), void (*printNode)(void*))
{
    genericBST g;
    g = (gbst*)malloc(sizeof(gbst));
    g->dsize = dsize;
    g->compareFn = cfunction;
    g->printNode = printNode;

    return g;
}

struct bstnode* searchGBST(genericBST gt, void *d, bstnode** par)
{
    if(gt->root == NULL)
        return NULL;
    else
    {
        bstnode* temp = gt->root;
        bstnode* prev = NULL;

        while(temp!= NULL)
        {
            if(gt->compareFn((void*)temp,d)==0)
            {    
                *par = prev;
                return temp;
            }
            else if(gt->compareFn((void*)temp,d)==1)
            {
                prev = temp;
                temp = temp->lchild;
            }
            else
            {
                prev = temp;
                temp = temp->rchild;
            }
            
        }
        return prev;
    }
    
}

void insertNodeGBST(genericBST gt, void *d)
{
    bstnode* a;
    a = (bstnode*)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data,d,gt->dsize);
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

void in_order(genericBST gt,bstnode* t)
{
    if(t != NULL)
    {
        in_order(gt,t->lchild);
        gt->printNode((void*)t);
        in_order(gt,t->rchild);        
    }
}

void pre_order(genericBST gt,bstnode* t)
{
    if(t != NULL)
    {
        gt->printNode((void*)t);
        pre_order(gt,t->lchild);
        pre_order(gt,t->rchild);        
    }
}

void post_order(genericBST gt,bstnode* t)
{
    if(t != NULL)
    {
        post_order(gt,t->lchild);
        post_order(gt,t->rchild);    
        gt->printNode((void*)t);    
    }
}

int traverseGBST(genericBST gt, int order)
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

void free_node(bstnode* node)
{
    free(node->data);
    free(node);
}

void del_case_A(bstnode * root,bstnode* loc, bstnode* par)
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

void del_case_B(bstnode * root,bstnode* loc, bstnode* par)
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

int deleteNodeGBST(genericBST gt, void *d)
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

void main()
{   
    genericBST gt = createGBST(sizeof(int),compareFn_int,printNode_int);

    int a[9] = {100,50,40,30,60,110,109,120,55};

    for(int i = 0;i<9;i++)
    {
        insertNodeGBST(gt, (void*)&a[i]);
    }

    printf("in_order:\n");
    traverseGBST(gt,0);
    printf("\n");

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("post_order:\n");
    traverseGBST(gt,2);
    printf("\n");

    printf("\nRemoving 30 with no child\n");
    deleteNodeGBST(gt,&a[3]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("\nReinserting 30\n");
    insertNodeGBST(gt, (void*)&a[3]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("\nRemoving 40 with 1 child\n");
    deleteNodeGBST(gt,&a[2]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("\nReinserting 40\n");
    insertNodeGBST(gt, (void*)&a[2]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("\nRemoving 50 with 2 child\n");
    deleteNodeGBST(gt,&a[1]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");

    printf("\nReinserting 50\n");
    insertNodeGBST(gt, (void*)&a[1]);

    printf("pre_order:\n");
    traverseGBST(gt,1);
    printf("\n");


    


}

