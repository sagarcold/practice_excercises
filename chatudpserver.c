#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100
int main()
{
	struct sockaddr_in server, client;
	int server_sockfd,i,slen = sizeof(server);
	char buf[SIZE];
	char buffer[SIZE];
	if((server_sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
	{
		perror("SERVER SOCKET");
		exit(0);
	}
	memset((char *)&server,0,sizeof(server));
	server.sin_port = htons(6000);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(server_sockfd,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("SERVER BIND");
		exit(1);
	}
	while(1)
	{
		if(recvfrom(server_sockfd,buf,SIZE,0,(struct sockaddr *)&client,&slen)==-1)
		{
			perror("SERVER RECVFROM");
			exit(2);
		}
		printf("the received message is:\n");
		printf("%s\n",buf);
		printf("enter your message\n");
		fgets(buffer,SIZE,stdin);
		if(sendto(server_sockfd,buffer,SIZE,0,(struct sockaddr*)&client,slen)==-1)
		{
			perror("client sendto");
			exit(1);
		}
	}
}
