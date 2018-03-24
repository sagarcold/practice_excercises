


#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

void error(char *msg)
{
	error(msg);
	exit(1);
}

int main()
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	char buf[255];
	sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("ERROR opening socket");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi("7100");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(6000);

	if (bind (sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	listen(sockfd,5);

	clilen = sizeof(cli_addr);
	newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr, &clilen);
	
	if (newsockfd <0)
		error("ERROR on accept");
	bzero(buffer,256);
	
	while(1)
	{
		n = read(newsockfd, buffer, 255);
			if( n < 0)
				error("ERROR reading from socket");
		printf("client sending: %s\n", buffer);
			fgets(buf, 40, stdin);
			write(newsockfd, buf, 255);
	}
	return 0;
}
	


