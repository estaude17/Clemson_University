/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
This file contains the functions used by caseConverter to setup client-server
connections and keep track of the different addresses that access the server.
The routines in this files are:
copycat()
addAddresses()
printAddresses()
SetupTCPServerSocket()
AcceptTCPConnection()
HandleTCPClient()
*/
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
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
static const int MAXPENDING = 5; // Maximum outstanding connection requests
/*
This routine sets up the TCP Server Socket. It also adds the currently-used 
address to a list of addresses in addAddresses().
*/
int SetupTCPServerSocket(const char *service) {
  // Construct the server address structure
  struct addrinfo addrCriteria;                   // Criteria for address match
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  addrCriteria.ai_flags = AI_PASSIVE;             // Accept on any address/port
  addrCriteria.ai_socktype = SOCK_STREAM;         // Only stream sockets
  addrCriteria.ai_protocol = IPPROTO_TCP;         // Only TCP protocol
  struct addrinfo *servAddr; // List of server addresses
  int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));
  int servSock = -1;
  struct addrinfo * addr;
  for (addr = servAddr; addr != NULL; addr = addr->ai_next) {
    // Create a TCP socket
    servSock = socket(addr->ai_family, addr->ai_socktype,
        addr->ai_protocol);
    if (servSock < 0)
      continue;       // Socket creation failed; try next address
    // Bind to the local address and set socket to listen
    if ((bind(servSock, addr->ai_addr, addr->ai_addrlen) == 0) &&
        (listen(servSock, MAXPENDING) == 0)) {
      // Print local address of socket
      struct sockaddr_storage localAddr;
      socklen_t addrSize = sizeof(localAddr);
      if (getsockname(servSock, (struct sockaddr *) &localAddr, &addrSize) < 0)
        DieWithSystemMessage("getsockname() failed");
      /*fputs("Binding to ", stdout);
      PrintSocketAddress((struct sockaddr *) &localAddr, stdout);
      fputc('\n', stdout);*/
      break;       // Bind and listen successful
    }
    close(servSock);  // Close and try again
    servSock = -1;
  }
  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);
  return servSock;
}
//creates a connection between server and client
int AcceptTCPConnection(int servSock) {
  struct sockaddr_storage clntAddr; // Client address
  // Set length of client address structure (in-out parameter)
  socklen_t clntAddrLen = sizeof(clntAddr);
  // Wait for a client to connect
  int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
  if (clntSock < 0)
    DieWithSystemMessage("accept() failed");
  // clntSock is connected to a client!
  addAddresses((struct sockaddr *) &clntAddr);
  fputs("Handling client ", stdout);
  PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
  fputc('\n', stdout);
  return clntSock;
}
/*The main function is to convert the message
from uppercase to lowercase, and vice versa. It also echoes the message back
to the client (bellower or frank) after this is done.
*/
void HandleTCPClient(int clntSocket) {
  char buffer[BUFSIZE]; // Buffer for echo string
  // Receive message from client
  ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
  if (numBytesRcvd < 0)
    DieWithSystemMessage("recv() failed");
  // Send received string and receive again until end of stream
  while (numBytesRcvd > 0) { // 0 indicates end of stream
    // Echo message back to client
    
    
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
    
    ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
    if (numBytesSent < 0)
      DieWithSystemMessage("send() failed");
    else if (numBytesSent != numBytesRcvd)
      DieWithUserMessage("send()", "sent unexpected number of bytes");
    // See if there is more data to receive
    numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
      DieWithSystemMessage("recv() failed");
  }
  close(clntSocket); // Close client socket
}
