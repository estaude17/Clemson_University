#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#define RCVBUFSIZE 5000   /* Size of receive buffer */
#define RSPBUFSIZE 500000
#define MAXSIZE 100
#define GETREQUEST 0
#define HEADREQUEST 1
#define BADREQUEST -1
#define WRONGREQUEST 405
#define READY 1
#define NOTREADY 0

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket, char* dir)
{
	char buffer[RCVBUFSIZE];        /* Buffer for http request */
	char respBuffer[RSPBUFSIZE];
	int recvMsgSize;                    /* Size of received message */
	int requestType = BADREQUEST;		/*Set to BADREQUEST until correct request is put in*/
	char* filePath = malloc(MAXSIZE);
	strcpy(filePath,dir);
	int errorMessageReady = NOTREADY;
	struct stat fs;
	char method[MAXSIZE];
	char dateAccess[MAXSIZE];
	char respDate[MAXSIZE];
	char contentType[MAXSIZE];
	char currDate[MAXSIZE];
	char* fileBuffer;
	time_t currTime = time(NULL);
	struct tm tm = *localtime(&currTime);

	/* Receive message from client */
	if ((recvMsgSize = recv(clntSocket, buffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed\n");

	/*Check to see what type of request there is*/
	if (strncmp(buffer, "GET", 3) == 0) {
		requestType = GETREQUEST;
	} else if (strncmp(buffer, "HEAD", 4) == 0) {
		requestType = HEADREQUEST;
	} else if ( strncmp(buffer, "OPTIONS", 7) == 0 ||
			strncmp(buffer, "POST", 4) == 0 ||
			strncmp(buffer, "PUT", 3) == 0 ||
			strncmp(buffer, "DELETE", 6) == 0 ||
			strncmp(buffer, "TRACE", 5) == 0 ||
			strncmp(buffer, "CONNECT", 7) == 0 ) {
		requestType = WRONGREQUEST;
		strcpy(respBuffer, "HTTP/1.1 405 Method Not Allowed\r\nAllow: GET, HEAD\n\nConnection: close\r\n\r\n");
		errorMessageReady = READY;
	} else {
		requestType = BADREQUEST;
		strcpy(respBuffer, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n");
		errorMessageReady = READY;
	}
	/*Parse the request to find the file path and then create proper response*/
	char * parser;
	int counter = 0;
	off_t fileSize = 0;
	if (requestType == GETREQUEST || requestType == HEADREQUEST || requestType == WRONGREQUEST) {
		parser = strtok(buffer," ");
		strcpy(method, parser);
		if ( requestType == GETREQUEST || requestType == HEADREQUEST) {
			while(parser != NULL) {

				parser = strtok (NULL, " ");
				counter++;
				if ( counter == 1 ) {
					if ( strcmp(parser,"/") == 0 ) {
						strcat(filePath,"/index.html");
					} else if ( strncmp(parser,"/..",3) == 0 ) {
						memset(respBuffer,0,RSPBUFSIZE);
						strcpy(respBuffer, "HTTP/1.1 403 Forbidden\r\nConnection: close\r\n\r\n");
						errorMessageReady = 1;
					} else if ( strncmp(parser,"/",1) == 0 ) {
						strcat(filePath,parser);
					} else {
						if (errorMessageReady != READY) {
							memset(respBuffer,0,RSPBUFSIZE);
							strcpy(respBuffer, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n");
							errorMessageReady = READY;
						}
					}
				}
			}
		}
		/*Write to standard output the correct string after checking for errors*/
		if (stat(filePath, &fs) < 0) {
			if (errorMessageReady != 1) {
				memset(respBuffer,0,RSPBUFSIZE);
				strcpy(respBuffer, "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n");
				if ( requestType == GETREQUEST ) {
					printf("GET\t%s\tDATE\t404\n",filePath);
				} else {
					printf("HEAD\t%s\tDATE\t404\n",filePath);
				}
				errorMessageReady = READY;
			}
		} else if ( access(filePath,R_OK) != 0 ) {
			strftime(dateAccess, MAXSIZE, "%d %b %Y %H:%M", gmtime(&(fs.st_mtime)));
			if (errorMessageReady != READY) {
				memset(respBuffer,0,RSPBUFSIZE);
				strcpy(respBuffer, "HTTP/1.1 403 Forbidden\r\nConnection: close\r\n\r\n");
				if ( requestType == GETREQUEST ) {
					printf("GET\t%s\t%s\t403\n",filePath,dateAccess);
				} else {
					printf("HEAD\t%s\t%s\t403\n",filePath,dateAccess);
				}
				errorMessageReady = HEADREQUEST;
			}
		} else if (requestType == WRONGREQUEST) {
			strftime(dateAccess, MAXSIZE, "%d %b %Y %H:%M", gmtime(&(fs.st_mtime)));
			printf("%s\t%s\t%s\t405\n",method, filePath,dateAccess);
		} else {
			strftime(dateAccess, MAXSIZE, "%d %b %Y %H:%M", gmtime(&(fs.st_mtime)));
			if (requestType == GETREQUEST) {
				printf("GET\t%s\t%s\t200\n",filePath,dateAccess);
			} else {
				printf("HEAD\t%s\t%s\t200\n",filePath,dateAccess);
			}
		}
		/*Create the response with extension, current date, last modified, file size and file*/ 
		if ((requestType == GETREQUEST || requestType == HEADREQUEST) && errorMessageReady != READY) {
			fileSize = fs.st_size;
			strftime(respDate, MAXSIZE, "%a, %d %b %Y %H:%M:S", gmtime(&(fs.st_mtime)));
			if (strstr(filePath,".css") != NULL) {
				strcpy(contentType,"text/css");
			} else if (strstr(filePath,".htm") != NULL) {
				strcpy(contentType,"text/html");
			} else if (strstr(filePath,".js") != NULL) {
				strcpy(contentType,"application/javascript");
			} else if (strstr(filePath,".txt") != NULL) {
				strcpy(contentType,"text/plain");
			} else if (strstr(filePath,".jpg") != NULL) {
				strcpy(contentType,"image/jpeg");
			} else if (strstr(filePath,".pdf") != NULL) {
				strcpy(contentType,"application/pdf");
			} else {
				strcpy(contentType,"application/octet-stream");
			}
			strftime(currDate, MAXSIZE, "%a, %d %b %Y %H:%M:S", &tm);

			if (requestType == GETREQUEST) {
				memset(respBuffer,0,RSPBUFSIZE);
				sprintf(respBuffer, "HTTP/1.1 200 OK\r\nDate: %s\r\nLast-Modified: %s\r\nContent -Type:\t%s\r\nContent -Length:\t %d\r\nServer: simhttp/1.0\r\nConnection: close\r\n\r\n", currDate, dateAccess,contentType,(int)fileSize);
				int c;
				FILE *fileToRead = fopen(filePath,"r");
				fileBuffer = malloc(fileSize);
				char * filePtr = fileBuffer;
				while ((c = getc(fileToRead)) != EOF)
					*filePtr++ = c;

				strcat(respBuffer,fileBuffer);
				free(fileBuffer);
			} else {
				memset(respBuffer,0,RSPBUFSIZE);
				sprintf(respBuffer, "HTTP/1.1 200 OK\r\nDate: %s\r\nLast-Modified: %s\r\nContent -Type:\t%s\r\nContent -Length:\t %d\r\nServer: simhttp/1.0\r\nConnection: close\r\n\r\n", currDate, dateAccess,contentType,(int)fileSize);
			}

		}



	}
	

	/* Send message back to client */
	if (send(clntSocket, respBuffer, strlen(respBuffer), 0) != strlen(respBuffer))
    		DieWithError("send() failed");

	free(filePath);

	close(clntSocket);    /* Close client socket */
}
