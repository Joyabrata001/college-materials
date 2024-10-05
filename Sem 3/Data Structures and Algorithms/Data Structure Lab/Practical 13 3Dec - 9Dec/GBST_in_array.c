#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gbst //definition of gbst
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void *, void *);
    struct bstnode *root;
} gbst;

typedef gbst *genericBST; //typedef to fit question

typedef struct bstnode //definition of bstnode
{
    void *data;
    struct bstnode *lchild;
    struct bstnode *rchild;
} bstnode;

int compareFn_int(void *a, void *b) //compare function of int
{
    if (*((int *)(((bstnode *)a)->data)) == *((int *)(((bstnode *)b)->data)))
        return 0;
    else if (*((int *)(((bstnode *)a)->data)) > *((int *)(((bstnode *)b)->data)))
        return 1;
    else
        return -1;
}

void printNode_int(void *node) //print node for int
{
    printf("%d ", *((int *)((bstnode *)node)->data));
}

genericBST createGBST(int dsize, int (*cfunction)(void *, void *), void (*printNode)(void *)) //will create base for a gst, with NULL root
{
    genericBST g;
    g = (gbst *)malloc(sizeof(gbst));
    g->dsize = dsize;
    g->compareFn = cfunction;
    g->printNode = printNode;

    return g;
}

struct bstnode *searchGBST(genericBST gt, void *d, bstnode **par) //this function outputs the pointer to found node, as well as its parent to par
{
    if (gt->root == NULL) //tree empty
        return NULL;
    else
    {
        bstnode *temp = gt->root;
        bstnode *prev = NULL;

        while (temp != NULL)
        {
            if (gt->compareFn((void *)temp, d) == 0) //node found
            {
                *par = prev;
                return temp;
            }
            else if (gt->compareFn((void *)temp, d) == 1) //value < node value, i.e go left
            {
                prev = temp;
                temp = temp->lchild;
            }
            else //value > node value, i.e go right
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
    bstnode *a;
    a = (bstnode *)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, d, gt->dsize); //copying data from d to a->data
    a->lchild = NULL;
    a->rchild = NULL;

    bstnode *par;

    bstnode *temp = searchGBST(gt, a, &par);

    if (temp == NULL)
        gt->root = a;
    else if (gt->compareFn(temp, a) == 1)
        temp->lchild = a;
    else
        temp->rchild = a;
}

void in_order(genericBST gt, bstnode *t) //prints in order
{
    if (t != NULL)
    {
        in_order(gt, t->lchild);
        gt->printNode((void *)t);
        in_order(gt, t->rchild);
    }
}

void pre_order(genericBST gt, bstnode *t) //prints pre order
{
    if (t != NULL)
    {
        gt->printNode((void *)t);
        pre_order(gt, t->lchild);
        pre_order(gt, t->rchild);
    }
}

void post_order(genericBST gt, bstnode *t) //prints post order
{
    if (t != NULL)
    {
        post_order(gt, t->lchild);
        post_order(gt, t->rchild);
        gt->printNode((void *)t);
    }
}

int traverseGBST(genericBST gt, int order) //traverse the tree according to given order
{
    if (gt->root == NULL)
        return 0;

    if (order == 0)
        in_order(gt, gt->root);
    else if (order == 1)
        pre_order(gt, gt->root);
    else if (order == 2)
        post_order(gt, gt->root);

    return 1;
}

void free_node(bstnode *node) //frees the node given
{
    free(node->data);
    free(node);
}

void del_case_A(bstnode *root, bstnode *loc, bstnode *par) //case for no or one child
{
    bstnode *child;

    if (loc->lchild == NULL && loc->rchild == NULL)
        child = NULL;
    else if (loc->lchild != NULL)
        child = loc->lchild;
    else
        child = loc->rchild;

    if (par != NULL)
    {
        if (loc == par->lchild)
            par->lchild = child;
        else
            par->rchild = child;
    }
    else
        root = child;
}

void del_case_B(bstnode *root, bstnode *loc, bstnode *par) //case for two childs
{
    bstnode *suc, *par_suc, *ptr, *save;

    ptr = loc->rchild;

    while (ptr->lchild != NULL)
    {
        save = ptr;
        ptr = ptr->lchild;
    }

    suc = ptr;
    par_suc = save;

    del_case_A(root, suc, par_suc);

    if (par != NULL)
    {
        if (loc = par->lchild)
            par->lchild = suc;
        else
            par->rchild = suc;
    }
    else
        root = suc;

    suc->lchild = loc->lchild;
    suc->rchild = loc->rchild;
}

int deleteNodeGBST(genericBST gt, void *d) //delets a node if any, with its data = d
{
    bstnode *a;
    a = (bstnode *)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, d, gt->dsize);
    a->lchild = NULL;
    a->rchild = NULL;

    bstnode *par;
    bstnode *loc;

    loc = searchGBST(gt, a, &par);

    if (loc == NULL)
    {
        printf("Item Not Found");
        return -1;
    }

    if (loc->lchild != NULL && loc->rchild != NULL)
        del_case_B(gt->root, loc, par);
    else
        del_case_A(gt->root, loc, par);

    free_node(loc);
}

void tree_to_array(genericBST gt, bstnode *arr, bstnode *node, int pos)
{
    if (node == NULL)
        return;

    arr[pos].data = malloc(gt->dsize);
    memcpy(arr[pos].data, node->data, gt->dsize);

    if (node->lchild != NULL)
        tree_to_array(gt, arr, node->lchild, pos * 2);
    if (node->rchild != NULL)
        tree_to_array(gt, arr, node->rchild, pos * 2 + 1);
}

void main()
{
    genericBST gt = createGBST(sizeof(int), compareFn_int, printNode_int);

    int a[7] = {50, 25, 20, 30, 100, 80, 110};

    for (int i = 0; i < 7; i++)
    {
        insertNodeGBST(gt, (void *)&a[i]);
    }

    printf("pre_order for gt:\n");
    traverseGBST(gt, 1);
    printf("\n\n");

    bstnode arr[10];

    for (int i = 0; i < 10; i++)
        arr[i].data = NULL;

    tree_to_array(gt, arr, gt->root, 1);

    printf("Array Representation: \n");
    for (int i = 1; i < 10; i++)
        if (arr[i].data != NULL)
            printf("%d ", *((int *)(arr[i].data)));
        else
            continue;
}
