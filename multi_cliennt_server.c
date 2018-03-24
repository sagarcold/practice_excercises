/* server2.c */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main( )
{
	int sock_server_fd, sock_client_fd, letter;
	struct sockaddr_in server, client;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.70.122");
	server.sin_port = htons(6000);

	if( (sock_server_fd = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
	{
		perror( "SERVER SOCKET" );
		exit(0);
	}	
	printf("Socket is done\n");
	if( (bind( sock_server_fd, (struct sockaddr *)&server, sizeof(server))) < 0 )
	{
		perror ( "SERVER BIND" );	
		exit(1);
	}	
	printf("Binding is done\n");

	if( listen( sock_server_fd, 5 ) < 0 )
	{
		perror ( "SERVER LISTEN" );
		exit(2);
	}
	printf("Listen is done\n");


	while( 1 )
	{
		int client_len= sizeof(client);
		sock_client_fd = accept( sock_server_fd, (struct sockaddr *)&client, &client_len );
		printf("Accept is done\n");
		
		if(fork()==0)
		{
			while(1)
			{			
				if( read(sock_client_fd, &letter, 1) != 1 )
				{
					perror ("SERVER READ");
					exit(3);
				}
				printf("Client sent letter %c\n", letter); 
				letter = letter - 32;
				printf("Server converted it into upper case\n That is %c\n",letter);
				if( write(sock_client_fd, &letter, 1 ) != 1 )
				{
					perror ("SERVER WRITE");
					exit(4);
				}
			}
		}
	}
}
