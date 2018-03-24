/* server2.c */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SIZE 100


int main( )
{
	int sock_server_fd, sock_client_fd;
	struct sockaddr_in server, client;
	char letter[SIZE];
	char buf[SIZE];

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.70.122");
	server.sin_port = htons(6000);

	if( (sock_server_fd = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
	{
		perror( "SERVER SOCKET" );
		exit(0);
	}	

	if( (bind( sock_server_fd, (struct sockaddr *)&server, sizeof(server))) < 0 )
	{
		perror ( "SERVER BIND" );	
		exit(1);
	}	

	if( listen( sock_server_fd, 5 ) < 0 )
	{
		perror ( "SERVER LISTEN" );
		exit(2);
	}

	int client_len = sizeof(client);		
	sock_client_fd = accept( sock_server_fd, (struct sockaddr *)&client, &client_len );

	while( 1 )
	{
		
		if( read(sock_client_fd, buf, SIZE) < 1 )
		{
			perror ("SERVER READ");
			exit(3);
		} 
		printf("the received message is\n");
		printf("%s\n",buf);
		printf("enter your message\n");
		fgets(letter,SIZE,stdin);
		if(write(sock_client_fd,letter,SIZE) < 1)
		{
			perror("SERVER WRITE");
			exit(4);
		}
	}
}
