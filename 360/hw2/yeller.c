/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
First client: sends a string (US-ASCII string)
provided as a parameter at the command line to a networked server.
It waits for a response from the server and displays the entire message
recieved (to standard-out).
Other than main(), the routines are:
Handler()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>
#include <signal.h>
#include "Practical.h"

char *server = "", *echoString = "", *servPort = "";
int count = 0, start = 0;
double time_used = 0;
char *buffer = "";
/*
This Handler() routine is called if the program is terminated with control-C
rather than ending naturally. It calculates the run-time of the program and
prints out the time, number of times contact with the server was attempted,
the total time, the original string, and the new string, which, since a 
connection was not made, will be an empty space.
*/
void Handler(int sig){
 	int end2 = clock();
	time_used = ((double) (end2-start) ) / CLOCKS_PER_SEC;
	printf("\n%i\t %f\t %s\t %s\n", count, time_used, echoString, buffer);
	exit(0);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, Handler); 
  int start = clock();
  int i = 0;

  if(argc != 7) DieWithUserMessage("Parameter(s)", "<Server Address/Name> <Echo Word> [<Server Port/Service>]");

  for(i = 1; i < argc; i+=2){
	if(strcmp(argv[i] , "-s") == 0) server = argv[i+1];
	else if(strcmp(argv[i] , "-m") == 0) echoString = argv[i+1];
 	else if(strcmp(argv[i] , "-p") == 0) servPort = argv[i+1];
  }

  size_t echoStringLen = strlen(echoString);
  if (echoStringLen > MAXSTRINGLENGTH) // Check input length
    	DieWithUserMessage(echoString, "string too long");

  // Tell the system what kind(s) of address info we want
  struct addrinfo addrCriteria;                   // Criteria for address match
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  // For the following fields, a zero value means "don't care"
  addrCriteria.ai_socktype = SOCK_DGRAM;          // Only datagram sockets
  addrCriteria.ai_protocol = IPPROTO_UDP;         // Only UDP protocol

  // Get address(es)
  struct addrinfo *servAddr; // List of server addresses
  int rtnVal = getaddrinfo(server, servPort, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

  // Create a datagram/UDP socket
  int sock = socket(servAddr->ai_family, servAddr->ai_socktype,
      servAddr->ai_protocol); // Socket descriptor for client
  if (sock < 0)
    DieWithSystemMessage("socket() failed");

  // Send the string to the server
  ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0,
      servAddr->ai_addr, servAddr->ai_addrlen);
  if (numBytes < 0)
    DieWithSystemMessage("sendto() failed");
  else if (numBytes != echoStringLen)
    DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

  // Receive a response

  struct sockaddr_storage fromAddr; // Source address of server
  // Set length of from address structure (in-out parameter)
  socklen_t fromAddrLen = sizeof(fromAddr);
  char buffer[MAXSTRINGLENGTH + 1]; // I/O buffer
  numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
      (struct sockaddr *) &fromAddr, &fromAddrLen);
  count++;
  if (numBytes < 0)
    DieWithSystemMessage("recvfrom() failed");
  else if (numBytes != echoStringLen) DieWithUserMessage(
	"recvfrom() error", "received unexpected number of bytes");

  // Verify reception from expected source
  if (!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr *) &fromAddr))
    DieWithUserMessage("recvfrom()", "received a packet from unknown source");

  freeaddrinfo(servAddr);

  int end = clock();
  double time_used = ((double) (end-start) ) / CLOCKS_PER_SEC; 
  buffer[echoStringLen] = '\0';     // Null-terminate received data
  printf("%i\t %f\t %s\t %s\n", count, time_used, echoString, buffer); 
	// Print the echoed string

  close(sock);
  exit(0);
}
