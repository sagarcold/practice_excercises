/*   client.c   */
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<sys/stat.h>
#define MAXLINE 80
char buffer[255];
#define 
#define SERVER_PORT_NUM 6002

void str_cli(FILE *fp,int sfd)
{
	char line[MAXLINE];
	printf("enter str_cli\n");
	while(fgets (line, MAXLINE, fp) != NULL)
	{
		write(sfd, line, strlen(line));
		sleep(2);
		if(read (sfd, buffer, 255));
			printf("server responding = %s",buffer);
	}
	printf("returning from str_cli \n");
}

int main()
{
	int sfd;
	//char buffer[255];
	struct sockaddr_in config_client;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd < 0)
	{
		printf("client : Failed to create socket \n");
		exit(1);
	}

	memset (&config_client, 0, sizeof (struct sockaddr_in));
	
	config_client.sin_family = AF_INET;
	config_client.sin_port = htons(SERVER_PORT_NUM);
	//config_client.sin_addr = (struct in_addr) SERVER_ADDR;
	inet_aton(SERVER_ADDR, &config_client.sin_addr);

	connect(sfd, (struct sockaddr *) &config_client , sizeof(config_client));
		
	printf("connect successful \n");
	str_cli (stdin, sfd);
	exit(0);
}
	


