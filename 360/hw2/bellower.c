/*
Elizabeth Stauder(estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
First client: sends a string (US-ASCII string). which is provided as a 
parameter at the command line to a networked server, called caseConverter.c. 
Then, bellower.c waits for a response from caseConverter and, once the 
message is received or control-c is entered, displays a message.
Other than main(), the routines are:
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
#include "Practical.h"
char *server = "", *echoString = "", *servPort = "";
int count = 0, start = 0;
double time_used = 0;
char buffer[BUFSIZE];
/*This is bellower.c's version of handling a ctrl c input.
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
int main(int argc, char *argv[]) {
  //signal(SIGINT, Handler);
  int start = clock();
  int i = 0;
  if(argc != 7) DieWithUserMessage("Parameter(s)", 
    "<Server Address/Name> <Echo Word> [<Server Port/Service>]");
  //handling of argument order
  for(i = 1; i < argc; i+=2){
        if(strcmp(argv[i] , "-s") == 0) server = argv[i+1];
        else if(strcmp(argv[i] , "-m") == 0) echoString = argv[i+1];
        else if(strcmp(argv[i] , "-p") == 0) servPort = argv[i+1];
  }
  // Create a connected TCP socket
  int sock = SetupTCPClientSocket(server, servPort);
  count++;
  // if there is no server, then enter loop until signal is received
  if (sock < 0){
    //DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");
    //printf("SetupTCPClientSocket() failed unable to connect");
    for(;;){
      signal(SIGINT, Handler);
    }
  }
  size_t echoStringLen = strlen(echoString); // Determine input length
  // Send the string to the server
  ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
  if (numBytes < 0)
    DieWithSystemMessage("send() failed");
  else if (numBytes != echoStringLen)
    DieWithUserMessage("send()", "sent unexpected number of bytes");
  // Receive the same string back from the server
  unsigned int totalBytesRcvd = 0; // Count of total bytes received
  //fputs("Received: ", stdout);     // Setup to print the echoed string
  
  while (totalBytesRcvd < echoStringLen) {
    char buffer[BUFSIZE]; // I/O buffer
    // Receive up to the buffer size (minus 1 to leave space for
    // a null terminator) bytes from the sender
    numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
    //count++;
    if (numBytes < 0)
      DieWithSystemMessage("recv() failed");
    else if (numBytes == 0)
      DieWithUserMessage("recv()", "connection closed prematurely");
    totalBytesRcvd += numBytes; // Keep tally of total bytes
    buffer[numBytes] = '\0';    // Terminate the string!
    int end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%i\t %f\t %s\t %s\n", count, time_used, echoString, buffer);
    //fputs(buffer, stdout);      // Print the buffer
  }
  //fputc('\n', stdout); // Print a final linefeed
  close(sock);
  exit(0);
}
