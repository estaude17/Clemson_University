#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <netdb.h>      /* for getHostByName() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXBUFFER 65536

void DieWithError(char *errorMessage);  /* Error handling function */

int main(int argc, char *argv[])
{
	int sock;                        /* Socket descriptor */
	struct sockaddr_in servAddr;     /* server address */
	struct hostent *thehost;         /* Hostent from gethostbyname() */
	char *httpString = malloc(MAXBUFFER);                /* String to send to server */
	char buffer[MAXBUFFER];		 /* Buffer for response string */
	unsigned int httpStringLen;      /* Length of string to */
	int isdNameSet = 0;
	char* dName;
	int portNum = 8080;
	char* fileName;
	char* httpIndex;
	char* header = malloc(sizeof(char) * 5);
	int hasIndex = 0;
	int directoryIndex;
	int afterhttpIndex = 0;
	int hasFileName = 0;
	char* hostName = malloc(sizeof(char) * 1000);
	FILE* filePath;

	if ((argc < 2) || (argc > 6))    /* Test for correct number of arguments */
	{
	fprintf(stderr, "Usage: %s <Server URL> [-p port] [-O filename]\n",
	       argv[0]);
	exit(1);
	}

	int i;
	for (i = 1; i < argc; i++) {
		if(strcmp(argv[i],"-p") == 0) {
			portNum = atoi(argv[i + 1]);
			i++;
		} else if(strcmp(argv[i],"-O") == 0) {
			fileName = argv[i + 1];
			hasFileName = 1;
			i++;
		} else {
			isdNameSet = 1;
			dName = argv[i];
		}
	}
	if (isdNameSet == 0) {
		DieWithError("URL required\n");
	}
	strncpy(header,dName,4);
	*(header+4) = 0;

	int index = 0;
	int count = 0;
	
	/*Move pointer until after the http://*/
	if(strcmp(header,"http") == 0) {
		while( count != 3 && *(dName + index) != 0 ) {
			if( *(dName + index) == '/' ) {
				count = count + 1;
			}

			if ( count == 3 ) {
				index++;
				httpIndex = dName + index;
				hasIndex = 1;
				
			}
			index++;

			if (count == 2 && afterhttpIndex == 0){
				afterhttpIndex = index;
			}

		}

	} else {
		while( count != 1 && *(dName + index) != 0 ) {
			if( *(dName + index) == '/' ) {
				count++;
			}
			if ( count == 1 ) {
				index++;
				httpIndex = dName + index;
				hasIndex = 1;
			}
			index++;
		}

	}

	directoryIndex = 0;
	while ( (httpIndex + directoryIndex) != 0 ) {
		directoryIndex++;
	}

	/*
		- 2 is for removal of null character and the last /
	*/
	strncpy(hostName,dName + afterhttpIndex,index - afterhttpIndex - 2);


	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	memset(&servAddr, 0, sizeof(servAddr));     /* Zero out structure */
	servAddr.sin_family      = AF_INET;             /* Internet address family */
	thehost = gethostbyname(hostName);
	servAddr.sin_addr.s_addr = *((unsigned long *) thehost->h_addr_list[0]);
	servAddr.sin_port        = htons(portNum); /* Server port */


	/* Establish the connection to the server */
	//if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		//DieWithError("connect() failed");


	//Create httpString
	


	strcpy(httpString,"GET /");
	int ptr = strlen("GET /");

	if ( hasIndex == 1 ) {
		strncpy(httpString + ptr, httpIndex, strlen(httpIndex));
		ptr = ptr + strlen(httpIndex);

	}

	strcpy(httpString + ptr, " HTTP/1.1\r\nUser-Agent: Wget/1.14 (darwin12.2.1)\r\nAccept: */*\r\nHost: ");
	ptr += strlen(" HTTP/1.1\r\nUser-Agent: Wget/1.14 (darwin12.2.1)\r\nAccept: */*\r\nHost: ");
	strncpy(httpString + ptr, hostName, strlen(hostName));
	ptr += strlen(hostName);
	strcpy(httpString + ptr, "\r\nConnection: Keep-Alive\r\n\r\n\0");

	httpStringLen = strlen(httpString);         /* Determine input length */


	/* Establish the connection to the server */
	if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithError("connect() failed");

	/* Send the string to the server */
	if (send(sock, httpString, httpStringLen, 0) != httpStringLen)
		DieWithError("send() sent a different number of bytes than expected");

	if ( hasFileName == 1) {
		filePath = fopen(fileName,"w");
	}
	while (recv(sock, buffer, MAXBUFFER - 1, 0) != 0)
	{
		if(hasFileName == 1) {
			fprintf(filePath, "%s", buffer);
		} else {
			printf("%s", buffer);
		}

	}
	if ( hasFileName == 1) {
		fclose(filePath);
	}


return 0;
}



