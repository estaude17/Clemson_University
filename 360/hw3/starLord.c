/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte) Connor Rouillard (crouill)
and Jordan Washington (jewashi).
CPSC 3600-project3
Due October 24, 2016
The server part of the assignment. much like the UDP version of EchoServer, it
receives messages from clients, inverts the messages and sends them back to the
clients. 
Other than main(), the only other routine is:
Handler()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <limits.h>
#include "Practical.h"
static const int MAXPENDING = 5;
int MessageCount = 0;
/*
This Handler() routine is called if the program is terminated with control-C
rather than ending naturally. It calculates the run-time of the program and
prints out the time, number of times contact with the server was attempted,
the total time, the original string, and the new string, which, since a 
connection was not made, will be an empty space.
*/
void Handler(int sig){
        printf("\n%d\t", MessageCount);
        printAddresses();
        exit(0);
}
int main(int argc, char *argv[]) {
  signal(SIGINT, Handler);
  char* serverBuffer = malloc(INT_MAX);
  
  if (argc != 3) // Test for correct number of arguments
    DieWithUserMessage("Parameter(s)", "<Server Port/Service>");
  char *service = argv[2]; // First arg:  local port
  // Create socket for incoming connections
  int servSock = SetupTCPServerSocket(service);
  if (servSock < 0)
    DieWithUserMessage("SetupTCPServerSocket() failed", service);
  for (;;) { // Run forever
    // New connection creates a connected client socket
    int clntSock = AcceptTCPConnection(servSock);
    
    HandleTCPClient(clntSock, serverBuffer); // Process client
    close(clntSock);
    MessageCount++;
    //break;
  }
  // NOT REACHED
  close(servSock);
}
