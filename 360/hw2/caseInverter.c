/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
When the server receives data, it is to invert all lowercase characters
to uppercase, and uppercase characters to lowercase for the characters
where this can be done. All other characters are to remain unchanged.
Routines, other than main(), are:
copycat()
addAddresses()
printAddresses()
Handler()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include "Practical.h"

struct entry{
	struct sockaddr address;
	struct entry* next;
};

struct entry *start = NULL;
/*This function is called in the addAddresses() function, and it checks the 
socket address of the current client against those of the addresses that are in
addAddress()'s newnode struct. If it is not, it returns true, which adds it 
to the newnode.
*/
bool copycat(struct sockaddr *address){
  struct entry *temper = start;
  while (temper != NULL){
	if(((struct sockaddr_in*)&temper->address)->sin_addr.s_addr ==
		((struct sockaddr_in*) address)->sin_addr.s_addr){
			return false;
		temper = temper->next;
		}
	else return true;
	}
  return true;
}
/*This function calls copycat() on the address of the client the server is 
assisting, and if it returns true on the address, the address is added to 
the newnode struct, which is a list of unique IP addresses that got sent
to the server before it terminated.
*/
void addAddresses(struct sockaddr *newaddress){
	if (copycat(newaddress) == true){
		struct entry *newnode = malloc(sizeof(struct entry));
		newnode->address = *newaddress;
		newnode->next = start;
		start = newnode;
	}
}
/*This function is called in Handler() after the server terminates. 
It takes the socket address of the client(s) that were served and converts 
them to the typical IP address form (ex: 127.0.0.1) and prints out each part
(separated by periods); this function prints out each unique IP address 
(separated by commas).
*/
void printAddresses(){
  int IP = 0, parts[4], i = 0;
  struct entry *c = start;
  while (c != NULL){
	IP = ((struct sockaddr_in*)&c->address)->sin_addr.s_addr;
	for(i = 0; i < 4; i++){
 		parts[i] = IP & 0xff;
		IP = IP >> 8;
		}
 	printf("%i.%i.%i.%i, ",parts[0], parts[1], parts[2], parts[3]);
	c = c->next;
 	}

}
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
	printf("\n");
	exit(0);
}

int main(int argc, char *argv[]) {

  signal(SIGINT, Handler);

  if (argc != 3) // Test for correct number of arguments
    DieWithUserMessage("Parameter(s)", "<Server Port/Service>");

  char *service = argv[2]; // First arg:  local port/service

  // Construct the server address structure
  struct addrinfo addrCriteria;                   // Criteria for address
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  addrCriteria.ai_flags = AI_PASSIVE;             // Accept on any address/port
  addrCriteria.ai_socktype = SOCK_DGRAM;          // Only datagram socket
  addrCriteria.ai_protocol = IPPROTO_UDP;         // Only UDP socket

  struct addrinfo *servAddr; // List of server addresses
  int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

  // Create socket for incoming connections
  int sock = socket(servAddr->ai_family, servAddr->ai_socktype,
      servAddr->ai_protocol);
  if (sock < 0)
    DieWithSystemMessage("socket() failed");

  // Bind to the local address
  if (bind(sock, servAddr->ai_addr, servAddr->ai_addrlen) < 0)
    DieWithSystemMessage("bind() failed");

  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);

  for (;;) { // Run forever
    struct sockaddr_storage clntAddr; // Client address
    // Set Length of client address structure (in-out parameter)
    socklen_t clntAddrLen = sizeof(clntAddr);

    // Block until receive message from a client
    char buffer[MAXSTRINGLENGTH]; // I/O buffer
    // Size of received message
    ssize_t numBytesRcvd = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
        (struct sockaddr *) &clntAddr, &clntAddrLen);
    if (numBytesRcvd < 0)
      DieWithSystemMessage("recvfrom() failed");

   addAddresses((struct sockaddr *) &clntAddr);

    fputs("Handling client ", stdout);

    PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
    fputc('\n', stdout);

    // Send received datagram back to the client

    /*This converts the message in buffer, character by character, 
    until each lowercase letter is turned into an uppercase one, 
    and vice versa for uppercase letters in the new message.*/
     int c = 0;
     while (buffer[c] != '\0') {
      char ch = buffer[c];
      if (ch >= 'A' && ch <= 'Z')
         buffer[c] = buffer[c] + 32;
      else if (ch >= 'a' && ch <= 'z')
         buffer[c] = buffer[c] - 32;
      c++;
     }
 
    ssize_t numBytesSent = sendto(sock, buffer, numBytesRcvd, 0,
        (struct sockaddr *) &clntAddr, sizeof(clntAddr));
    if (numBytesSent < 0)
      DieWithSystemMessage("sendto() failed)");
    else if (numBytesSent != numBytesRcvd)
      DieWithUserMessage("sendto()", "sent unexpected number of bytes");
   MessageCount++;
  }
}
