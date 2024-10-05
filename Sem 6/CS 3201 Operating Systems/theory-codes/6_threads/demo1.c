#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread1(void *vargp)
{
    printf("hello world1\n");
    return NULL;
}

int main()
{
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_join(tid1, NULL);
    printf("Hello \n");
    return 0;
}

