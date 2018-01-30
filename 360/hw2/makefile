all: caseConverter bellower frank caseInverter yeller checker
caseConverter: caseConverter.o AddressUtility.o DieWithMessage.o TCPServerUtility.o
bellower: bellower.o AddressUtility.o DieWithMessage.o TCPClientUtility.o
 
frank: frank.o AddressUtility.o DieWithMessage.o TCPClientUtility.o

caseInverter: caseInverter.o AddressUtility.o DieWithMessage.o

yeller: yeller.o AddressUtility.o DieWithMessage.o

checker: checker.o AddressUtility.o DieWithMessage.o

caseConverter.c: Practical.h
DieWithMessage.c: Practical.h
bellower.c: Practical.h
frank.c: Practical.h
TCPClientUtility.c: Practical.h
TCPServerUtility.c: Practical.h
caseInverter.c: Practical.h
checker.c: Practical.h
yeller.c: Practical.h

clean:
	-rm *.o caseConverter bellower frank caseInverter yeller checker
