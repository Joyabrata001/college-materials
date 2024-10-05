#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tbst //definition of tbst
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void *, void *);
    struct tbstnode *header;
} tbst;

typedef tbst *genericTBST; //typedef to fit question

typedef struct tbstnode //definition of tbstnode
{
    void *data;
    struct tbstnode *lchild;
    struct tbstnode *rchild;
    int lthread; //act as bool; 0 is false; 1 in true
    int rthread; //act as bool; 0 is false; 1 in true
} tbstnode;

int compareFn_int(void *a, void *b) //compare function of int
{
    if (*((int *)(((tbstnode *)a)->data)) == *((int *)(((tbstnode *)b)->data)))
        return 0;
    else if (*((int *)(((tbstnode *)a)->data)) > *((int *)(((tbstnode *)b)->data)))
        return 1;
    else
        return -1;
}

void printNode_int(void *node) //print node for int
{
    printf("%d ", *((int *)((tbstnode *)node)->data));
}

genericTBST createTGBST(int dsize, int (*cfunction)(void *, void *), void (*printNode)(void *)) //will create base for a gst, with NULL header
{
    //creating header
    tbstnode *header = (tbstnode *)malloc(sizeof(tbstnode));
    header->data = NULL;
    header->lchild = header;
    header->rchild = header;
    header->lthread = 1;
    header->rthread = 1;

    //creating genericTBST
    genericTBST gt;
    gt = (tbst *)malloc(sizeof(tbst));
    gt->dsize = dsize;
    gt->compareFn = cfunction;
    gt->printNode = printNode;
    gt->header = header;

    return gt;
}

tbstnode *searchTGBST(genericTBST gt, void *d, tbstnode **par) //this function outputs the pointer to found node, as well as its parent to par
{
    if (gt->header->lchild == gt->header) //tree empty
        return NULL;
    else
    {
        tbstnode *temp = gt->header->lchild;
        tbstnode *prev = gt->header;

        while (temp->lthread != 1 || temp->rthread != 1)
        {
            if (gt->compareFn((void *)temp, d) == 0) //node found
            {
                *par = prev;
                return temp;
            }
            else if (gt->compareFn((void *)temp, d) == 1) //value < node value, i.e go left
            {
                if (temp->lthread == 0)
                {
                    prev = temp;
                    temp = temp->lchild;
                }
                else
                {
                    *par = prev;
                    return temp;
                }
            }
            else //value > node value, i.e go right
            {
                if (temp->rthread == 0)
                {
                    prev = temp;
                    temp = temp->rchild;
                }
                else
                {
                    *par = prev;
                    return temp;
                }
            }
        }
        *par = prev;
        return temp;
    }
}

void insertNodeTGBST(genericTBST gt, void *d) //inserts a node with its data being d
{
    //making node
    tbstnode *a;
    a = (tbstnode *)malloc(sizeof(tbstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, d, gt->dsize); //copying data from d to a->data
    a->lchild = gt->header;
    a->rchild = gt->header;
    a->lthread = 1;
    a->rthread = 1;

    tbstnode *par = gt->header;

    tbstnode *temp = searchTGBST(gt, a, &par);

    if (temp == NULL && par == gt->header)
    {
        gt->header->lchild = a;
        gt->header->lthread = 0;
    }
    else if (gt->compareFn(temp, a) == 1)
    {
        a->lchild = temp->lchild;
        a->rchild = temp;
        temp->lthread = 0;
        temp->lchild = a;
    }
    else
    {
        a->rchild = temp->rchild;
        a->lchild = temp;
        temp->rthread = 0;
        temp->rchild = a;
    }
}

tbstnode *in_order_successor(tbstnode *t)
{
    tbstnode *temp = t->rchild;

    if (temp->lthread == 0)
    {
        while (temp->lthread != 1)
            temp = temp->lchild;
    }

    return temp;
}

int traverseTGBST(genericTBST gt) //traverse the tree according to given order
{
    if (gt->header->lchild == gt->header) //tree empty
        return 0;

    tbstnode *temp = in_order_successor(gt->header);

    do
    {
        if (temp != gt->header)
            gt->printNode(temp);

        if (temp->rthread == 1)
            temp = temp->rchild;
        else
            temp = in_order_successor(temp);

    } while (temp != gt->header);
}

void free_node(tbstnode *node) //frees the node given
{
    free(node->data);
    free(node);
}

void del_case_A(genericTBST gt, tbstnode *loc, tbstnode *par) //case for no or one child
{
    tbstnode *child;

    if (loc->lthread == 1 && loc->rthread == 1)
        child = NULL;
    else if (loc->lthread != 1)
        child = loc->lchild;
    else
        child = loc->rchild;

    if (par != gt->header)
    {
        if (loc == par->lchild)
        {
            if (child != NULL)
            {
                par->lchild = child;
                if (loc->lchild == child)
                    child->rchild = loc->rchild;
                else
                    child->lchild = loc->lchild;
            }
            else
            {
                par->lthread = 1;
                par->lchild = loc->lchild;
            }
        }
        else
        {

            if (child != NULL)
            {
                par->rchild = child;
                if (loc->lchild == child)
                    child->rchild = loc->rchild;
                else
                    child->lchild = loc->lchild;
            }
            else
            {
                par->rthread = 1;
                par->rchild = loc->rchild;
            }
        }
    }
    else
    {
        if (child != NULL)
        {
            par->lchild = child;
            if (loc->lchild == child)
                child->rchild = loc->rchild;
            else
                child->lchild = loc->lchild;
        }
        else
        {
            par->lthread = 1;
            par->lchild = par;
        }
    }
}

void del_case_B(genericTBST gt, tbstnode *loc, tbstnode *par) //case for two childs
{

    tbstnode *ptr = in_order_successor(loc);

    tbstnode *par_suc = gt->header;
    tbstnode *suc = searchTGBST(gt, ptr, &par_suc);

    del_case_A(gt, suc, par_suc);

    *((int *)(loc->data)) = *((int *)(suc->data));
}

int deleteNodeGBST(genericTBST gt, void *d) //delets a node if any, with its data = d
{
    tbstnode *a;
    a = (tbstnode *)malloc(sizeof(tbstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, d, gt->dsize);
    a->lchild = gt->header;
    a->rchild = gt->header;
    a->lthread = 1;
    a->rthread = 1;

    tbstnode *par = gt->header;
    tbstnode *loc = searchTGBST(gt, a, &par);

    if (loc == NULL)
    {
        printf("Item Not Found");
        return -1;
    }

    if (loc->lthread != 1 && loc->rthread != 1)
        del_case_B(gt, loc, par);
    else
        del_case_A(gt, loc, par);

    free_node(a);
}

void main()
{
    genericTBST gt = createTGBST(sizeof(int), compareFn_int, printNode_int);

    int a[8] = {100, 50, 40, 60, 110, 109, 120, 55};

    for (int i = 0; i < 8; i++)
    {
        insertNodeTGBST(gt, (void *)&a[i]);
    }

    printf("in_order for gt1:\n");
    traverseTGBST(gt);
    printf("\n\n");

    printf("Deleting 110 with 2 child\n");
    deleteNodeGBST(gt, (void *)&a[4]);
    traverseTGBST(gt);
    printf("\n\n");

    printf("Deleting 120 with no child\n");
    deleteNodeGBST(gt, (void *)&a[6]);
    traverseTGBST(gt);
    printf("\n\n");

    printf("Deleting 60 with 1 child\n");
    deleteNodeGBST(gt, (void *)&a[3]);
    traverseTGBST(gt);
    printf("\n\n");
}
