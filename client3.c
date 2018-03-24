/* client2.c */

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
	int sock_client_fd;
	struct sockaddr_in server;
	char letter;

	if( (sock_client_fd = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
	{
		perror( "CLIENT SOCKET" );
		exit(0);
	}	

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr( "192.168.70.50" );
	server.sin_port = htons(6000);

	if(connect( sock_client_fd, (struct sockaddr *)&server, sizeof(server)) < 0 )
	{
		perror( "CLIENT CONNECT" );
		exit(1);
	}	

	printf( "Enter small case letters, press 0 to exit \n" );
	scanf( "%c", &letter );
	
	while(letter)
	{
	//printf("sock fd = %d\n",sock_client_fd);
		if( letter == '0' )
			exit(2);

		if( letter < 'a' || letter > 'z' )
		{
			printf( "Enter small case dear\n");
			__fpurge(stdin);
			scanf( "%c", &letter );
			continue;
		}

		if( write( sock_client_fd, &letter, 1 ) != 1 )
		{
			perror ( "CLIENT WRITE" );
			exit(3);
		}
		
		if( read( sock_client_fd, &letter, 1 ) != 1 )
		{
			perror ( "CLIENT READ" );
			exit(4);
		}	
		
		printf( "Server Converted to upper case : %c\n", letter );
		__fpurge(stdin);
		printf( "Enter small case letters, press 0 to exit\n" );
		scanf( "%c", &letter );
	}
	printf( "Client OFF\n" );
	close(sock_client_fd);
}
