Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte)
CPSC 3600-project2
Due October 3, 2016
This project will operate in a similar way to the first project, which used
UDP format; this version will use the TCP socket format. The main difference
between the two is that TCP is connection-oriented, and once a connection is
established, data can be sent bidirectionally. UDP is much simplr, and is a
connectionless Internet protocol (IP).
This program has two major components:
The first, bellower.c, sends a message to my server, here called
"caseConverter", and the caseInverter switches the cases of the original
message from bellower.c and sends the new message back.
*bellower.c walkthrough*
the first thing that bellower.c checks is that the number of arguments
put into its input is 7 (each phrase counts as an arguments: <server name>,
-s, <message>, -m, <server port>, -p. argc=7). Then, using a for-loop,
the program goes through each argument and if the argument is "-s", then
the program sets the server is set to the argument immediately following it.
The same method is used for the -m/message(which will be placed in a variable
called echoString) and -p/serverPort.
After this is confirmed, the program starts timing itself by setting a
global variable start to clock(). This will be concluded later.
After that, the program uses sendto() to send the needed info
to the server (echoString and its length as well as the client's socket
descriptor) and the echoString will be converted in caseCoverter.c, or more 
speficially, in TCPServerUtility.c, into the proper response message.
This new message, now placed in the variable buffer, will be received via
recv(), and after checking that the recv() function returned an actual message,
and that it the message it sent was the correct length, it creates the
variable end and sets it equal to clock(), ending the timer. After that,
the amount of times a connection to the server was made, the amount of time
the client took, the original string, and the new string. After this, the
program terminates. If the server and the client don't make a connection, the
user can enter Control-C to prematurely exit the yeller program. This causes
the function signal(), which is at the top of main(), to activate, and redirects
the program to the Handler() function. This function stops the timer and prints out
the same information as the original main() before terminating, but there will
be an empty space in place of a new message, because the buffer string had not
been set to anything yet.
When frank.c is executed, its process is similar to yeller.c, but
with an added step: once it receives the new message from the server,
it sends the new message back to the server to be translated again
(renamed buffer2), and then compares the modified message with the original
to ensure that the two are the same.
*frank.c walkthrough*
The first steps of frank.c are the same as bellower.c
(see walkthrough above). The only difference is the added
sendto()/recvfrom() to re-send buffer to the server, now called buffer2.
The code for re-sending the message is the exact same as it was before, but
because of these added commands, a verify() function is needed to ensure that
the original message and the second new message, which, given it is the
inverted state of an inverted message, should equal the original echoString.
The verify() function, which is called in the print statement when deciding
whether to print verification that the inverted statement is the correct one,
goes through the original echoString and the buffer2 and, character by
character, determines if they are the same. If they are, "Verified" is printed;
if not, "Wrong" is printed.
*caseCoverter.c walkthrough*
The way the server (caseCoverter.c) changes the message is to go through the
received message and place it in the variable buffer. In doing so, it takes the
upper case letters and switches them to lower case, and vice versa, leaving any
other symbol as is. This file also connects to functions in TCPServerUtility.c; 
one of these functions handles a linked list of unique client
addresses, using the copycat() and addAddresses() functions to add the unique
IP addresses if they do not already exist in the list. The server remains
running forever until the command "ctrl c" is signaled, in which the file
prints out the number of messages sent and the list of unique IP addresses(via 
printAddresses() in TCPServerUtility.c).
