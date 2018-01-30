all: starLord chopper ahsoka
chopper: chopper.o AddressUtility.o TCPClientUtility.o DieWithMessage.o
ahsoka:ahsoka.o AddressUtility.o TCPClientUtility.o DieWithMessage.o
starLord: starLord.o AddressUtility.o TCPServerUtility.o DieWithMessage.o
chopper.c: Practical.h
ahsoka.c: Practical.h
starLord.c: Practical.h
TCPClientUtility.c: Practical.h
TCPServerUtility.c: Practical.h
DieWithMessage.c: Practical.h
clean:
	-rm *.o starLord chopper ahsoka
