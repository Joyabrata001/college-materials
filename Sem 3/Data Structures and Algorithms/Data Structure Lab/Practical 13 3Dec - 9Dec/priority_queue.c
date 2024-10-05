#include <stdio.h>
#include <math.h>   //for floor()
#include <stdlib.h> //for rand()and randomize()
#include <time.h>   //for time()

void insert_heap(int *tree, int *n, int item)
{
    *n = *n + 1;
    int ptr = *n;

    while (ptr > 0)
    {
        int par = floor(ptr / 2);

        if (item < tree[par])
        {
            tree[ptr] = item;
            return;
        }

        tree[ptr] = tree[par];
        ptr = par;
    }
    tree[0] = item;
}

int swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void del_heap(int tree[], int *n, int *item)
{
    *item = tree[0];
    tree[0] = tree[*n];
    *n = *n - 1;

    int ptr = 0;
    int left = 1;
    int right = 2;

    while (right <= *n)
    {
        if (tree[left] >= tree[right])
        {
            swap(&tree[ptr], &tree[left]);
            ptr = left;
        }
        else
        {
            swap(&tree[ptr], &tree[right]);
            ptr = right;
        }

        left = ptr * 2 + 1;
        right = ptr * 2 + 2;
    }

    if (left == *n)
    {
        swap(&tree[ptr], &tree[left]);
    }
}

void main()
{
    printf("Enter Size of Queue: ");
    int n;
    scanf("%d", &n);
    printf("\n");

    int heap[n];
    int size = -1;

    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        int coin_toss = rand() % 2; //0 of tail, 1 is head
        printf("Toss %d\n",i+1);
        if (coin_toss == 1)
        {
            printf("It's Head: Value to be Inserted\n");

            if (size >= n-1)
            {
                printf("Queue Full\n");
                printf("Queue Size: %d\n\n", size+1);
                continue;
            }
            else
            {
                int value;
                printf("Enter a Value to be inserted in Queue: ");
                scanf("%d", &value);
                insert_heap(heap, &size, value);
            }
        }
        else
        {
            printf("It's Tail: Value to be Extracted\n");
            if (size >= 0)
            {
                int value;
                del_heap(heap, &size, &value);
                printf("Value: %d\n", value);
            }
            else
            {
                printf("Queue Empty!\n");
            }
        }

        printf("Queue Size: %d\n\n", size+1);
    }

    printf("Tossed 10 times\n");
    
}