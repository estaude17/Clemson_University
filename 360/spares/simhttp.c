#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define DIRECTORYSET 1
#define DIRECTORYNOTSET 0

void DieWithError(char *errorMessage);  /* Error handling function */
void HandleTCPClient(int clntSocket, char* dir);   /* TCP client handling function */

int main(int argc, char *argv[])
{
	int servSock;                    /* Socket descriptor for server */
	int clntSock;                    /* Socket descriptor for client */
	struct sockaddr_in servAddr; /* Local address */
	struct sockaddr_in clntAddr; /* Client address */
	unsigned short servPort = 8080;     /* Server port */
	unsigned int clntLen;            /* Length of client address data structure */
	char* directory;
	int isDirectorySet = DIRECTORYNOTSET;

	if (argc > 4)     /* Test for correct number of arguments */
	{
		fprintf(stderr, "Usage:  %s <-p Server Port> <Directory>\n", argv[0]);
		exit(1);
	}
	/*Input parameters into their variables*/
	int i;
	for (i = 1; i < argc; i++) {
		if(strcmp(argv[i],"-p") == 0) {
			servPort = atoi(argv[i + 1]);
			i++;
		} else {
			isDirectorySet = DIRECTORYSET;
			directory = argv[i];
		}
	}
	if ( isDirectorySet != DIRECTORYSET ) {
		directory = malloc(2);
		strcpy(directory, ".");
	}


	/* Create socket for incoming connections */
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct local address structure */
	memset(&servAddr, 0, sizeof(servAddr));   /* Zero out structure */
	servAddr.sin_family = AF_INET;                /* Internet address family */
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	servAddr.sin_port = htons(servPort);      /* Local port */

	/* Bind to the local address */
	if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithError("bind() failed");

	/* Mark the socket so it will listen for incoming connections */
	if (listen(servSock, MAXPENDING) < 0)
		DieWithError("listen() failed");

	for (;;) /* Run forever */
	{
		/* Set the size of the in-out parameter */
		clntLen = sizeof(clntAddr);

		/* Wait for a client to connect */
		if ((clntSock = accept(servSock, (struct sockaddr *) &clntAddr, 
				       &clntLen)) < 0)
		    DieWithError("accept() failed");

		/* clntSock is connected to a client! */

		/*This handler handles all of the HTTP Requests*/
		HandleTCPClient(clntSock, directory);
	}

return 0;
}
