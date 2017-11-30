// A simple echo server using UCP 

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

#define SERVER_UDP_PORT 	7005	// Default port
#define MAXLEN			65000	//Buffer length
#define TRUE			1
 
int main (int argc, char **argv)
{
	int	sd, client_len, port, n;
	char	buf[MAXLEN];
	struct	sockaddr_in server, client, cli2, svr2;

	switch(argc)
	{
		case 1:
			port = SERVER_UDP_PORT;	// Default port
		break;
		case 2:
			port = atoi(argv[1]);	//User specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
   	}

	// Create a datagram socket
	if ((sd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror ("Can't create a socket"); 
		exit(1);
	}

	// Bind an address to the socket
	bzero((char *)&server, sizeof(server)); 
	server.sin_family = AF_INET; 
	server.sin_port = htons(port); 
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror ("Can't bind name to socket");
		exit(1);
	}

	while (TRUE)
	{
		client_len = sizeof(client);
		if ((n = recvfrom (sd, buf, MAXLEN, 0, (struct sockaddr *)&client, &client_len)) < 0)
		{
			perror ("recvfrom error");
			exit(1);
		}

        int num;
        char action[256], fname[256];
        num = sscanf(buf,"%s %s",action,fname);

        printf("S< word count(%i): 1>%s 2>%s (remainder ignored...)\n",num,action,fname);

        // determine action
        if (strcmp(action,"get")==0)
            printf("S< get [%s]\n",fname);
        else if (strcmp(action,"put")==0)
            printf("S< put [%s]\n",fname);
        else if (strcmp(action,"ll")==0)
            printf("S< local listing\n");
        else if (strcmp(action,"rl")==0)
            printf("S< remote listing\n");
        else if (strcmp(action,"exit")==0)
            printf("S< exit selected\n");
        else
            printf("S< unknown action [%s]\n", action);

		if (sendto (sd, buf, n, 0,(struct sockaddr *)&client, client_len) != n)
		{
			perror ("S< sendto error");
			exit(1);
		}
		printf ("S< Received %d bytes\t", n);
		printf ("... from host: %s\n", inet_ntoa (client.sin_addr));
	}
	close(sd);
	return(0);
}
