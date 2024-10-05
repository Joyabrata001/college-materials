// Web Server Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void *talk(void *newsockfd_ptr)
{
	int newsockfd = *((int *)newsockfd_ptr);
	char buf[1000];

	for (int i = 0; i < 1000; i++)
		buf[i] = '\0';

	recv(newsockfd, buf, 2500, 0);
	printf("Server Established\n------------------\n------------------\n%s", buf);

	char *token = strtok(buf, "/");
	token = strtok(NULL, " ");
	printf("Your Token -> %s\n", token);
	FILE *fp = fopen(token, "r");

	if (!fp)
	{
		// printf("File doesn't exist in Server Directory.\n");
		printf("\nRESPONSE\n--------\n");

		char header[1000];
		char data[1000] = "<html><head></head><body><h1>404 Not Found</h1></body></html>\r\n";

		sprintf(header, "HTTP/1.1 404 Not Found\naccept-ranges: bytes\ncontent-length: %ld\ncontent-type: text/html\r\n\r\n", strlen(data));
		printf("%s\n", header);
		send(newsockfd, header, strlen(header) * sizeof(char), 0);

		printf("%s\n", data);
		send(newsockfd, data, strlen(data) * sizeof(char), 0);

		close(newsockfd);
	}
	else
	{

		// printf("File exists in Server Directory\n");
		printf("\nRESPONSE\n--------\n");

		char header[1000];
		char data[10000];
		size_t charRead = fread(data, sizeof(char), 10000, fp);

		sprintf(header, "HTTP/1.1 200 OK\naccept-ranges: bytes\ncontent-length: %ld\ncontent-type: text/html\r\n\r\n", strlen(data));
		printf("%s\n", header);
		send(newsockfd, header, strlen(header) * sizeof(char), 0);

		printf("%s\n", data);
		send(newsockfd, data, charRead, 0);
		send(newsockfd, "\r\n", sizeof("\r\n"), 0);

		close(newsockfd);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd;
	int clilen;
	struct sockaddr_in cli_addr, serv_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Cannot create socket\n");
		exit(0);
	}

	int port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Unable to bind local address\n");
		exit(0);
	}

	listen(sockfd, 5);
	while (1)
	{

		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

		if (newsockfd < 0)
		{
			printf("Accept error\n");
			exit(0);
		}
		// talk(newsockfd);
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if (pthread_create(&thread, &attr, talk, &newsockfd) != 0)
		{
			fprintf(stderr, "error: pthread_create error");
		}
	}
	close(sockfd);
}
