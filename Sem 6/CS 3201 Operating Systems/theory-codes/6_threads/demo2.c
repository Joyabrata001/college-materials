#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int sum; /* this data is shared by the thread(s) */

/* The thread will execute in this function */
void *runner(void *param)
{
    int i, upper = atoi((char *)param);
    sum = 0;
    for (i = 1; i <= upper; i++)
        sum += i;
    pthread_exit(0);
}

void main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: give a parameter\n");
        exit(1);
    }

    pthread_t tid;       /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    /* set the default attributes of the thread */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* wait for the thread to exit */
    pthread_join(tid, NULL);
    printf("sum = %d\n", sum);
}