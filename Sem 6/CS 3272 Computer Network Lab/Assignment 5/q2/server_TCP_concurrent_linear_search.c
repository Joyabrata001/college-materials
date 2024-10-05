/*
            NETWORK PROGRAMMING WITH SOCKETS

In this program we illustrate the use of Berkeley sockets for interprocess
communication across the network. We show the communication between a server
process and a client process.

Since many server processes may be running in a system, we identify the
desired server process by a "port number". Standard server processes have
a worldwide unique port number associated with it. For example, the port
number of SMTP (the sendmail process) is 25. To see a list of server
processes and their port numbers see the file /etc/services

In this program, we choose port number 6000 for our server process. Here we
shall demonstrate TCP connections only. For details and for other types of
connections see:

     Unix Network Programming
        -- W. Richard Stevens, Prentice Hall India.

To create a TCP server process, we first need to open a "socket" using the
socket() system call. This is similar to opening a file, and returns a socket
descriptor. The socket is then bound to the desired port number. After this
the process waits to "accept" client connections.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

/* The following three files must be included for network programming */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 100
int sockfd, newsockfd; /* Socket descriptors */
#define ARRSIZE 20

/* THE SERVER PROCESS */

/* Compile this program with gcc server.c -o server
   and then execute it as ./server &
*/

char *ANTONYMS[][2] = {
    {"absence", "presence"},
    {"admit", "deny"},
    {"beginning", "ending"},
    {"borrow", "lend"},
    {"comfort", "discomfort"},
    {"courage", "cowardice"},
    {"dark", "light"},
    {"demand", "supply"},
    {"encourage", "discoruage"},
    {"entrance", "exit"},
    {"fail", "succeed"},
    {"foolish", "wise"},
    {"gloomy", "cheerful"},
    {"giant", "dwarf"},
    {"happy", "sad"},
    {"healthy", "unhealthy"},
    {"immense", "tiny"},
    {"inferior", "superior"},
    {"justice", "injustice"},
    {"knowldge", "ignorance"},
    {"lazy", "energetic"},
    {"little", "large"},
    {"misunderstand", "understand"},
    {"possible", "impossible"},
    {"prudent", "imprudent"},
    {"rapid", "slow"},
    {"rigid", "soft"},
    {"satisfactory", "unsatisfactory"},
    {"scatter", "collect"},
};
const int ANTONYM_SIZE = 28;

int linearSearch(char *key)
{
   for (int i = 0; i < ANTONYM_SIZE; i++)
      if (strcmp(ANTONYMS[i][0], key) == 0)
         return i;

   return -1;
}

void clearBuffer(char *buf, int size)
{
   for (int i = 0; i < size; i++)
      if (buf[i] == '\0')
         break;
      else
         buf[i] = '\0';
}

void closeSock(int sig)
{
   close(sockfd);
   close(newsockfd);
   exit(0);
}

int main()
{
   signal(SIGINT, closeSock);

   struct sockaddr_in serv_addr;

   char buf[100]; /* We will use this buffer for communication */

   /* The following system call opens a socket. The first parameter
      indicates the family of the protocol to be followed. For internet
      protocols we use AF_INET. For TCP sockets the second parameter
      is SOCK_STREAM. The third parameter is set to 0 for user
      applications.
   */
   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror("Cannot create socket\n");
      kill(0, SIGINT);
   }

   /* The structure "sockaddr_in" is defined in <netinet/in.h> for the
      internet family of protocols. This has three main fields. The
      field "sin_family" specifies the family and is therefore AF_INET
      for the internet family. The field "sin_addr" specifies the
      internet address of the server. This field is set to INADDR_ANY
      for machines having a single IP address. The field "sin_port"
      specifies the port number of the server.
   */
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(6000);

   /* With the information provided in serv_addr, we associate the server
      with its port using the bind() system call.
   */
   if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
   {
      perror("Unable to bind local address");
      kill(0, SIGINT);
   }

   listen(sockfd, 5); /* This specifies that up to 5 concurrent client
                 requests will be queued up while the system is
                 executing the "accept" system call below.
              */

   /* In this program we are illustrating an iterative server -- one
      which handles client connections one by one.i.e., no concurrency.
      The accept() system call returns a new socket descriptor
      which is used for communication with the server. After the
      communication is over, the process comes back to wait again on
      the original socket descriptor.
   */
   while (1)
   {

      /* The accept() system call accepts a client connection.
         It blocks the server until a client request comes.

         The accept() system call fills up the client's details
         in a struct sockaddr which is passed as a parameter.
         The length of the structure is noted in clilen. Note
         that the new socket descriptor returned by the accept()
         system call is stored in "newsockfd".
      */
      struct sockaddr_in cli_addr;
      int clilen = sizeof(cli_addr);
      newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,
                         &clilen);

      if (newsockfd < 0)
      {
         perror("Accept error");
         kill(0, SIGINT);
      }

      /* We initialize the buffer, copy the message to it,
          and send the message to the client.
      */
      // for (i = 0; i < 100; i++)
      //     buf[i] = '\0';
      // strcpy(buf, "Message from server");
      // send(newsockfd, buf, 100, 0);

      /* We again initialize the buffer, and receive a
          message from the client.
      */

      if (fork() == 0)
      {
         clearBuffer(buf, BUFSIZE);
         printf("waiting to receive data\n");
         recv(newsockfd, buf, BUFSIZE, 0);

         printf("received data %s\n", buf);

         int idx = linearSearch(buf);

         clearBuffer(buf, BUFSIZE);
         if (idx == -1)
            strcpy(buf, "Antonym NF");
         else
            strcpy(buf, ANTONYMS[idx][1]);

         printf("sending data %s\n", buf);
         send(newsockfd, buf, BUFSIZE, 0);
         printf("data sent");
      }

      close(newsockfd);
   }
}
