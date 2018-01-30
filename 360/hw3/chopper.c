/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte) Connor Rouillard (crouill)
and Jordan Washington (jewashi).
CPSC 3600-project3
Due October 24, 2016
Other than main(), the other routine is:
Handler()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include "Practical.h"
char *server = "", *echoString = "", *servPort = "", *hostHead = "";
char *httpString, *status;
char buf[80];
bool Vflag = false;
int count = 0, start = 0;
int echoStringLen;
double time_used = 0;
char buffer[BUFSIZE];

/*This is chopper.c's version of handling a ctrl-c input.
It is identical to the one used in project 1; it is called if the program
is terminated with control-c rather than ending naturally with a returned
message from the server. Like the print statement at the end of main(),
this shows the number of times contact was attempted, the amount of time
the process took, the original message, and a black space where the new
message would have been. Then, after that, the program terminates completely.
*/
void Handler(){
  int end2 = clock();
  time_used = ((double) (end2 - start)) / CLOCKS_PER_SEC;
  printf("\n%i\t %f\t %s\t %s\n", count, time_used, echoString, buffer);
  exit(0);
}
/*
The main() routine takes in a message, sends it to the server,
*/
int main(int argc, char *argv[]) {
  //signal(SIGINT, Handler);
  int start = clock();
  int i=1, bytesToRecv = 0;
  httpString = (char *)malloc(100);
  status = (char *)malloc(1000);
  if(argc < 8 || argc > 10) {
    printf("%d\n", argc);
    DieWithUserMessage("Parameter(s)", "<server Address><server Port><host Header><message><view>");
  }
  if(argc == 9){
  for(i = 1; i < argc; i+=2){
        if(strcmp(argv[i] , "-s") == 0) server = argv[i+1];
        else if(strcmp(argv[i] , "-a") == 0) echoString = argv[i+1];
        else if(strcmp(argv[i] , "-p") == 0) servPort = argv[i+1];
        else if(strcmp(argv[i] , "-h") == 0) hostHead = argv[i+1];
    } 
  }
  //handling of argument order
  //argc would equal 7 if there was no message and only a -v command.
  else if(argc == 8 || argc == 10){
  for(i = 1; i < argc; i+=2){
        if(strcmp(argv[i] , "-s") == 0) server = argv[i+1];
        else if(strcmp(argv[i] , "-a") == 0) echoString = argv[i+1];
        else if(strcmp(argv[i] , "-p") == 0) servPort = argv[i+1];
        else if(strcmp(argv[i] , "-h") == 0) hostHead = argv[i+1];
        else if(strcmp(argv[i], "-v") == 0) Vflag = true;
    }
  }
  //replacing spaces in echoString for easier parsing
  echoStringLen = strlen(echoString);
  for(i = 0; i < echoStringLen; i++){
    if(echoString[i] == ' ') echoString[i] = '+';
  }
  //creating httpString here
  strcpy(httpString, "GET /");
  //int pointer = strlen("GET /");
  /* message to server = 'GET /add?data=<message> HTTP/1.1';
  <message> is the message from arguments
  */
  if(Vflag){
    //send entire buffer
    /* message to server += 'view?';
    means that message should be ignored
    */
    strcat(httpString, "view? HTTP/1.1\r\n");
    bytesToRecv = BUFSIZE;
  }
  else if (!Vflag){
    //send message to add
    /* message to server += 'add?data=';
    message to server += echoString;
    server should add this data to the buffer.
    */
    strcat(httpString, "add?data=");
    strcat(httpString, echoString);
    strcat(httpString, " HTTP/1.1\r\n");
  }

  //second line of http header
  strcat(httpString, "Host: ");
  strcat(httpString, hostHead);
  strcat(httpString, "\r\n\r\n");

  //printf("%s\n", httpString); //DEBUG to see what httpString is

  // Create a connected TCP socket
  int sock = SetupTCPClientSocket(server, servPort);
  // if there is no server, then enter loop until signal is received
  if (sock < 0){
    //DieWithUserMessage("socket() failed", "unable to connect");
    //printf("socket() failed unable to connect");
    for(;;){
      signal(SIGINT, Handler);
    }
  }

  if(!Vflag) bytesToRecv = strlen(httpString);
  else bytesToRecv = 300;

 // CREATE THE HTTP TYPE STRING BEFORE SENDING IT
  // Send the string to the server
  int httpStringLen = strlen(httpString);
  ssize_t numBytes = send(sock, httpString, httpStringLen, 0);
  if (numBytes < 0)
    DieWithSystemMessage("send() failed");
  else if (numBytes != httpStringLen)
    DieWithUserMessage("send()", "sent unexpected number of bytes");

  unsigned int totalBytesRcvd = 0;
  while (totalBytesRcvd < bytesToRecv) {
    //char buffer[BUFSIZE]; // I/O buffer
    // Receive up to the buffer size (minus 1 to leave space for
    // a null terminator) bytes from the sender
    numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
    count++;
       
    if (numBytes < 0)
      DieWithSystemMessage("recv() failed");
    else if (numBytes == 0)
      DieWithUserMessage("recv()", "connection closed prematurely");
    totalBytesRcvd += numBytes; // Keep tally of total bytes
    //buffer[numBytes] = '\0';    // Terminate the string!
   
  }
  buffer[totalBytesRcvd] = '\0';
    int k = 0;
    while(buffer[k] != '\0'){
      char l = buffer[k];
      char m = buffer[k+1];
      if(l == 'O' && m == 'K')status = "HTTP OK 200";
      k++;
      }
    if(strcmp(status, "HTTP OK 200") != 0) status = "HTTP ERROR";
    if(Vflag)status = "HTTP OK 200";

  const char s[2] = " ";
  char *temp;
  temp = strtok(buffer, s);
  for(i = 0; i < strlen(temp); i++){
    if(temp[i] == '+') temp[i] = ' ';
  }
 
  for(i = 0; i < echoStringLen; i++){
    if(echoString[i] == '+') echoString[i] = ' ';
  }
  int end = clock();
  time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  if(Vflag) printf("%i\t %f\t %s\t %s\t \n%s", count, time_used, echoString, status, temp);
  else printf("%i\t %f\t %s\t %s", count, time_used, echoString, status);
  fputc('\n', stdout); // Print a final linefeed

  close(sock);
  exit(0);
}
