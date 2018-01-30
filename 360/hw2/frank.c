/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
The second of two types of clients. Frank is similar to Bellower in that it
sends a message inputed by the user, however, it resends the message and checks
to make sure it is inverted correctly by the server.
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
char buffer2[BUFSIZE];
/* compares the original message to the one that was doubly inverted. if they 
are the same it returns the "Verified" message*/
int verify(char *converted, char *original){
  while(*converted && *original){
        if (*converted != *original) return 1;
        converted++;
        original++;
        }
  if(*converted == *original) return 0;
  else return 0;
}
/* a function used in the signal call. it only runs when someone tries to connect to a server that
doesnt exist and enters an infinite loop, then presses ctrl c. the function prints out why it 
failed and what it should have sent*/
void Handler(){
  int end2 = clock();
  time_used = ((double) (end2 - start)) / CLOCKS_PER_SEC;    
  printf("\n%i\t %f\t %s\t %s\t %s\n", count, time_used, echoString, buffer,
      verify(buffer, buffer2) ? "Verified" : "Wrong");
  exit(0);
}
int main(int argc, char *argv[]) {
 // signal(SIGINT, Handler);
  int start = clock();
  int i = 0;
  if(argc != 7) DieWithUserMessage("Parameter(s)",
    "<Server Address/Name> <Echo Word> [<Server Port/Service>]");
    // handles the inputs of the program
  for(i = 1; i < argc; i+=2){
        if(strcmp(argv[i] , "-s") == 0) server = argv[i+1];
        else if(strcmp(argv[i] , "-m") == 0) echoString = argv[i+1];
        else if(strcmp(argv[i] , "-p") == 0) servPort = argv[i+1];
  }
  // Create a connected TCP socket
  int sock = SetupTCPClientSocket(server, servPort);
  // if server is not activated enter while loop and wait for signal
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
  //fputs("\n", stdout);     // Setup to print the echoed string
  count++;
  while (totalBytesRcvd < echoStringLen) {
    // Receive up to the buffer size (minus 1 to leave space for
    // a null terminator) bytes from the sender
    numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
 //    count++;
    if (numBytes < 0)
      DieWithSystemMessage("recv() failed");
    else if (numBytes == 0)
      DieWithUserMessage("recv()", "connection closed prematurely");
    totalBytesRcvd += numBytes; // Keep tally of total bytes
    buffer[numBytes] = '\0';    // Terminate the string!
   // close(sock);
    //int end = clock();
    //time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   // printf("%i\t %f\t %s\t %s\n", count, time_used, echoString, buffer);
    //fputs(buffer, stdout);      // Print the buffer
  }
  //fputc('\n', stdout); // Print a final linefeed
  close(sock);
int sock2 = SetupTCPClientSocket(server, servPort);
  if (sock2 < 0)
    DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");
  size_t bufferLen = strlen(buffer); // Determine input length
  // Send the string to the server
  ssize_t numBytes2 = send(sock2, buffer, bufferLen, 0);
  if (numBytes2 < 0)
    DieWithSystemMessage("send() failed");
  else if (numBytes2 != bufferLen)
    DieWithUserMessage("send()", "sent unexpected number of bytes");
  // Receive the same string back from the server
  unsigned int totalBytesRcvd2 = 0; // Count of total bytes received
  //fputs("\n", stdout);     // Setup to print the echoed string
        count++;
  while (totalBytesRcvd2 < bufferLen) {
   // char buffer2[BUFSIZE]; // I/O buffer
    // Receive up to the buffer size (minus 1 to leave space for
    // a null terminator) bytes from the sender
    numBytes = recv(sock2, buffer2, BUFSIZE - 1, 0);
    //count++;
    if (numBytes2 < 0)
      DieWithSystemMessage("recv() failed");
    else if (numBytes2 == 0)
      DieWithUserMessage("recv()", "connection closed prematurely");
    totalBytesRcvd2 += numBytes2; // Keep tally of total bytes
    buffer2[numBytes2] = '\0';    // Terminate the string!
  }
    close(sock2);
    int end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%i\t %f\t %s\t %s\t %s\n", count, time_used, echoString, buffer,
      verify(buffer, buffer2) ? "Verified" : "Wrong");
  exit(0);
}
