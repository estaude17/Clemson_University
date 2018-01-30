/*
Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600
Due October 3, 2016
Like all .h files, the purpose of Practical.h is to house
the names and parameters of the functions used in the .c files with
#include "Practical.h" as one of their header files.
*/

#ifndef PRACTICAL_H_
#define PRACTICAL_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

// Handle error with user msg
void DieWithUserMessage(const char *msg, const char *detail);
// Handle error with sys msg
void DieWithSystemMessage(const char *msg);
// Print socket address
void PrintSocketAddress(const struct sockaddr *address, FILE *stream);
// Test socket address equality
bool SockAddrsEqual(const struct sockaddr *addr1, const struct sockaddr *addr2);
// Create, bind, and listen a new TCP server socket
int SetupTCPServerSocket(const char *service);
// Accept a new TCP connection on a server socket
int AcceptTCPConnection(int servSock);
// Handle new TCP client
void HandleTCPClient(int clntSocket);
// Create and connect a new TCP client socket
int SetupTCPClientSocket(const char *server, const char *service);

enum sizeConstants {
  MAXSTRINGLENGTH = 128,
  BUFSIZE = 512,
};

#endif // PRACTICAL_H_
