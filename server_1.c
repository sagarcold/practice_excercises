#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	struct sockaddr_in server,client;
	int server_sockfd, i, slen = sizeof(server);
	char buf[1024];
	if((server_sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
	{
		perror("SERVER SOCKET");
		exit(0);
	}
	memset((char *)&server,0,sizeof(server));
	server.sin_port = htons(8944);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(server_sockfd,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("SERVER BIND");
		exit(1);
	}
	for(i = 0;i<100;i++)
	{
		if(recvfrom(server_sockfd,buf,1024,0,(struct sockaddr *)&client,&slen) == -1)
		{
			perror("SERVER RECVFROM");
			exit(2);
		}
	printf("Received packet from %s: %d \n Data :%s \n \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
	}
	//printf("Received packet from %s: %d \n Data :%s \n \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
	close(server_sockfd);
	return 0;
}
		
