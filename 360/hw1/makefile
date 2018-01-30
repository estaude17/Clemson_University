all: caseInverter yeller checker

caseInverter: caseInverter.o AddressUtility.o diewithmessage.o

yeller: yeller.o AddressUtility.o diewithmessage.o

checker: checker.o AddressUtility.o diewithmessage.o

caseInverter.c: Practical.h
diewithmessage.c: Practical.h
checker.c: Practical.h
yeller.c: Practical.h

clean:
	-rm *.o caseInverter yeller checker
