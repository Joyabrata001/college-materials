/*				THE CLIENT PROCESS

    Please read the file server.c before you read this file. To run this,
    you must first change the IP address specified in the line:

        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    to the IP-address of the machine where you are running the server.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define BUFSIZE 100
#define ARRSIZE 20
#define NUM_CONNECTIONS 4

void clearBuffer(char *buf, int size)
{
    for (int i = 0; i < size; i++)
        if (buf[i] == '\0')
            break;
        else
            buf[i] = '\0';
}

void *work(void *d)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    char buf[BUFSIZE];

    /* Opening a socket is exactly similar to the server process */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Unable to create socket\n");
        exit(0);
    }

    /* Recall that we specified INADDR_ANY when we specified the server
       address in the server. Since the client can run on a different
       machine, we must specify the IP address of the server.

       TO RUN THIS CLIENT, YOU MUST CHANGE THE IP ADDRESS SPECIFIED
       BELOW TO THE IP ADDRESS OF THE MACHINE WHERE YOU ARE RUNNING
       THE SERVER.
    */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(6000);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    /* With the information specified in serv_addr, the connect()
       system call establishes a connection with the server process.
    */
    if ((connect(sockfd, (struct sockaddr *)&serv_addr,
                 sizeof(serv_addr))) < 0)
    {
        perror("Unable to connect to server");
        exit(0);
    }

    /* After connection, the client can send or receive messages.
       However, please note that recv() will block when the
       server is not sending and vice versa. Similarly send() will
       block when the server is not receiving and vice versa. For
       non-blocking modes, refer to the online man pages.
    */
    // clearBuffer(buf, BUFSIZE);
    // recv(sockfd, buf, 100, 0);
    // printf("%s\n", buf);

    int data[ARRSIZE];
    for (int i = 0; i < ARRSIZE; i++)
        data[i] = rand() % 10000;

    clearBuffer(buf, BUFSIZE);
    strcpy(buf, "[");
    send(sockfd, buf, BUFSIZE, 0);

    for (int i = 0; i < ARRSIZE; i++)
    {
        clearBuffer(buf, BUFSIZE);
        sprintf(buf, "%d", data[i]);
        send(sockfd, buf, BUFSIZE, 0);
    }

    clearBuffer(buf, BUFSIZE);
    strcpy(buf, "]");
    send(sockfd, buf, BUFSIZE, 0);

    clock_t start_t = clock();

    int idx = 0;
    while (1)
    {

        clearBuffer(buf, BUFSIZE);

        recv(sockfd, buf, BUFSIZE, 0);

        if (strcmp(buf, "[") != 0 && strcmp(buf, "]") != 0)
        {
            data[idx++] = atoi(buf);
        }

        if (strcmp(buf, "]") == 0)
            break;
    }

    clock_t end_t = clock();

    printf("[%d,%d,%d,%d,%d, ...]", data[0], data[1], data[2], data[3], data[4]);

    long numCpuClocks = end_t - start_t;
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("\t%li clocks\t%lf sec\n", numCpuClocks, total_t);

    close(sockfd);
}

int main()
{
    srand(time(NULL));
    pthread_t tid[NUM_CONNECTIONS];

    for (int i = 0; i < NUM_CONNECTIONS; i++)
        pthread_create(&tid[i], NULL, work, NULL);

    for (int i = 0; i < NUM_CONNECTIONS; i++)
        pthread_join(tid[i], NULL);
}
