#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //for abs()

typedef struct gbst //definition of Generic Binary Search Tree
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void *, void *);
    struct bstnode *root;
} gbst;

typedef gbst *genericBST;

typedef struct bstnode //definition of Node
{
    int height; //new parameter for AVL Tree
    void *data;
    struct bstnode *lchild;
    struct bstnode *rchild;
    struct bstnode *par;
} bstnode;

int compareFn_int(void *a, void *b) //compare Function for nodes with int data type data
{
    if (*((int *)(((bstnode *)a)->data)) == *((int *)(((bstnode *)b)->data)))
        return 0;
    else if (*((int *)(((bstnode *)a)->data)) > *((int *)(((bstnode *)b)->data)))
        return 1;
    else
        return -1;
}

void printNode_int(void *node) //print function of nodes for data with int data type
{
    printf("%d ", *((int *)((bstnode *)node)->data));
}

genericBST createGBST(int dsize, int (*cfunction)(void *, void *), void (*printNode)(void *))
{
    //making genericBST and giving it default values and returning
    genericBST g;
    g = (gbst *)malloc(sizeof(gbst));
    g->dsize = dsize;
    g->compareFn = cfunction;
    g->printNode = printNode;
    g->root = NULL;

    return g;
}

int searchAVL(genericBST gt, void *val)
{
    int comparisions = 0; //the thing to be returned

    //making a node with given value, to use on the inbuilt function in genericBST
    bstnode *a = (bstnode *)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, val, gt->dsize);
    a->lchild = NULL;
    a->rchild = NULL;
    a->height = 1;
    a->par = NULL;

    if (gt->root != NULL) //if tree is empty, the value is absolutely not present in tree
    {
        //iterator for traversal
        bstnode *temp = gt->root;

        while (temp != NULL)
        {
            if (gt->compareFn(temp, a) == 0) //value is present
            {
                return comparisions;
            }
            else if (gt->compareFn(temp, a) == 1)
            {
                comparisions++;
                temp = temp->lchild;
            }
            else
            {
                comparisions++;
                temp = temp->rchild;
            }
        }
    }
    return 0; //return 0 if value not found
}

int printBF(bstnode *t) //returns balance factor, i.e |l-r| of a node, where l is height of lchild and r is height of rchild
{
    int l = 0;
    int r = 0;

    if (t->lchild != NULL) //chcecking NULL, otherwise will give error
        l = t->lchild->height;
    if (t->rchild != NULL)
        r = t->rchild->height;

    return abs(l - r);
}

int max(int a, int b) //same as cpp function max()
{
    if (a > b)
        return a;
    else
    {
        return b;
    }
}

void heightRepairNode(bstnode *a) //repairs height of node given, as height changes after rotation
{
    int l = 0;
    int r = 0;

    if (a->lchild != NULL)
        l = a->lchild->height;
    if (a->rchild != NULL)
        r = a->rchild->height;

    a->height = max(l, r) + 1;
}

void heightRepairAVL(bstnode *a) //repairs height of the node, going from a to root,
{
    bstnode *temp = a;
    bstnode *par = a->par;

    if (par == NULL)
        return;

    while (par != NULL)
    {
        int l = 0;
        int r = 0;

        if (par->lchild != NULL)
            l = par->lchild->height;
        if (par->rchild != NULL)
            r = par->rchild->height;

        par->height = max(l, r) + 1;

        temp = par;
        par = par->par;
    }
}

void rotate(genericBST gt, bstnode *upper, bstnode *lower) //rotates upper and lower nodes
{
    if (gt->root == upper)
    {
        if (upper->lchild == lower)
        {
            bstnode *t1 = lower->lchild;
            bstnode *t2 = lower->rchild;
            bstnode *t3 = upper->rchild;

            gt->root = lower;
            lower->par = NULL;

            lower->rchild = upper;
            upper->par = lower;

            upper->lchild = t2;

            if (t2 != NULL)
                t2->par = upper;
        }
        else if (upper->rchild == lower)
        {
            bstnode *t1 = upper->lchild;
            bstnode *t2 = lower->lchild;
            bstnode *t3 = lower->rchild;

            gt->root = lower;
            lower->par = NULL;

            lower->lchild = upper;
            upper->par = lower;

            upper->rchild = t2;
            if (t2 != NULL)
                t2->par = upper;
        }
    }
    else
    {
        if (upper->rchild == lower)
        {
            bstnode *t1 = upper->lchild;
            bstnode *t2 = lower->lchild;
            bstnode *t3 = lower->rchild;
            bstnode *par = upper->par;

            if (par->lchild == upper)
            {
                par->lchild = lower;
                lower->par = par;
            }
            else
            {
                par->rchild = lower;
                lower->par = par;
            }

            lower->lchild = upper;
            upper->par = lower;

            upper->rchild = t2;
            if (t2 != NULL)
                t2->par = upper;
        }
        else if (upper->lchild == lower)
        {
            bstnode *t1 = lower->lchild;
            bstnode *t2 = lower->rchild;
            bstnode *t3 = upper->rchild;
            bstnode *par = upper->par;

            if (par->lchild == upper)
            {
                par->lchild = lower;
                lower->par = par;
            }
            else
            {
                par->rchild = lower;
                lower->par = par;
            }

            lower->rchild = upper;
            upper->par = lower;

            upper->lchild = t2;
            if (t2 != NULL)
                t2->par = upper;
        }
    }
}

void treeRepairInsert(genericBST gt, bstnode *a) //repairs tree after insertion
{
    bstnode *z = a;
    bstnode *y = a;
    bstnode *x = a;

    while (z != NULL) //finding x,y,z , where z is the first unbalanced node while going through inserted node and root,y is chile of z along path, x is child of y along path
    {
        if (printBF(z) > 1)
            break;

        x = y;
        y = z;
        z = z->par;
    }

    if (z != NULL) //checking for 4 cases and rotating as per case
    {
        if (z->lchild == y)
        {
            if (y->lchild == x)
            {
                rotate(gt, z, y);
            }
            else if (y->rchild == x)
            {
                rotate(gt, y, x);
                rotate(gt, z, x);
            }
        }
        else if (z->rchild == y)
        {
            if (y->rchild == x)
            {
                rotate(gt, z, y);
            }
            else if (y->lchild == x)
            {
                rotate(gt, y, x);
                rotate(gt, z, x);
            }
        }

        //repairing height of x,y,z as they have been moved
        heightRepairNode(x);
        heightRepairNode(y);
        heightRepairNode(z);
    }
}

bstnode *insAVL(genericBST gt, void *val) //inserts a node in tree, and checks for AVL properties and if not following, repairs the tree
{
    //making a node to be inserted on the tree
    bstnode *a = (bstnode *)malloc(sizeof(bstnode));
    a->data = malloc(gt->dsize);
    memcpy(a->data, val, gt->dsize);
    a->lchild = NULL;
    a->rchild = NULL;
    a->height = 1;
    a->par = NULL;

    if (gt->root == NULL) //tree empty
        gt->root = a;
    else //tree not empty
    {
        //usual BST search and insert
        bstnode *temp = gt->root;
        bstnode *par = gt->root;

        while (temp != NULL)
        {
            if (gt->compareFn(temp, a) == 0)
            {
                return NULL;
            }
            else if (gt->compareFn(temp, a) == 1)
            {
                par = temp;
                temp = temp->lchild;
            }
            else
            {
                par = temp;
                temp = temp->rchild;
            }
        }

        if (gt->compareFn(par, a) == -1)
        {
            par->rchild = a;
            a->par = par;
        }
        else
        {
            par->lchild = a;
            a->par = par;
        }

        //repair height of AVL tree
        heightRepairAVL(a);
        //checks for any AVL problem, and repairs the tree
        treeRepairInsert(gt, a);
        //again repair tree, as the rotation may have cause changes
        heightRepairAVL(a);
    }
}

void in_order(genericBST gt, bstnode *t) //in-order traversal of tree
{
    if (t != NULL)
    {
        in_order(gt, t->lchild);
        gt->printNode((void *)t);
        in_order(gt, t->rchild);
    }
}

void pre_order(genericBST gt, bstnode *t) //pre-order traversal of tree
{
    if (t != NULL)
    {
        gt->printNode((void *)t);
        pre_order(gt, t->lchild);
        pre_order(gt, t->rchild);
    }
}

void post_order(genericBST gt, bstnode *t) //post-order traversal of tree
{
    if (t != NULL)
    {
        post_order(gt, t->lchild);
        post_order(gt, t->rchild);
        gt->printNode((void *)t);
    }
}

int trvsAVL(genericBST gt, int order) //traversal of AVL tree
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

int height(bstnode *t) //returns height of a node
{
    return t->height;
}

void main()
{
    //creating Generic BST with int data type
    genericBST gt = createGBST(sizeof(int), compareFn_int, printNode_int);

    //values to be inserted
    int a[9] = {100, 50, 40, 30, 60, 110, 109, 120, 55};

    //inserting in AVL tree, and also printing Pre-order Traversal of tree formed
    for (int i = 0; i < 9; i++)
    {
        printf("Inserting %d:\n", a[i]);
        insAVL(gt, (void *)&a[i]);

        printf("pre_order:\n");
        trvsAVL(gt, 1);
        printf("\n\n");
    }

    printf("No. of Comparisions to reach 109: %d\n", searchAVL(gt, (void *)&a[6]));

    printf("Balance factor of 50: %d\n", printBF(gt->root));

    printf("Height of 50: %d\n", height(gt->root));
}
