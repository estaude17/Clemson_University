Elizabeth Stauder (estaude) and Kaitlin Helfter (khelfte) Connor Rouillard (crouill)
and Jordan Washington (jewashi).
CPSC 3600-project3
Due October 24, 2016


This program has two major components:
The first, chopper.c, sends a message to my server, here called
"starLord", and the server either adds my message to a list of messages, or 
lets me view those messages.

*chopper.c walkthrough*
the first thing that chopper.c checks is that the number of arguments
put into its input is between 7 and 9 (each phrase counts as an arguments: <server name>,
-s, <message>, -m, <server port>, -p, <hostHeader>, -h, <message>, -a, and if the
optional -v is there.). Then, using a for-loop,
the program goes through each argument and if the argument is "-s", then
the program sets the server is set to the argument immediately following it.
The same method is used for the -m/message(which will be placed in a variable
called echoString), -h/hostHead, and -p/serverPort. 
If -v is also entered as an argument, it will set the boolean variable Vflag to
true, which will cause the "view" option to be activated, and the message, if 
there is one, will be ignored and not added, as it would if there was not a -v
argument, which causes the activation of "add".

After this is confirmed, the program starts timing itself by setting a
global variable start to clock(). This will be concluded later.
Before the message can be sent, the spaces between the words of the message,
if any exist, will be replaces with + characters to make the process easier. 
After that, the program uses sendto() to send the needed info
to the server (echoString and its length as well as the client's socket
descriptor) and the echoString will be sent starLord.c, or more 
speficially, to TCPServerUtility.c, and will be added to the bigger message, and 
the initial message will be .

The returned message, now placed in the variable buffer and having the + characters
replaced with spaces so that it returns to its original format (after this process,
if the "view" command is entered, the full message is placed in the variable temp),
the message will be received via recv(), and after checking that the recv() 
function returned an actual message, and that it the message it sent was the correct
length, it creates the variable end and sets it equal to clock(), ending the timer. 
After that, the amount of times a connection to the server was made, the amount of time
the client took, the original string, and the new string. After this, the
program terminates. 

If the server and the client don't make a connection, the
user can enter Control-C to prematurely exit the yeller program. This causes
the function signal(), which is at the top of main(), to activate, and redirects
the program to the Handler() function. This function stops the timer and prints out
the same information as the original main() would before terminating, but there will
be an empty space in place of a new message, because the buffer string had not
been set to anything yet.

*ahsoka.c walkthrough*
The way ahsoka.c operates is similar to chopper.c (see above walkthrough for 
greater detail) but verifies whether the webserver performs the task as stated. 
It will do so by sending sequences of add requests and view requests and receiving 
the responses in due order. This process is very simlar to the TCP and UDP 
verifications in the previous assignments. If the final buffer contents are the 
same as expected, the server is "verified" and this program terminates displaying 
an appropriate message to the user. This client must send messages one at a time 
and in the order requested at run-time.

*starLord.c walkthrough*
The server starLord's main purpose is to use the HandleTCPClient() function in
TCPServerUtility.c to add the message to a list called serverBuffer, and copy that
list into a variable called message when the view command is typed.
