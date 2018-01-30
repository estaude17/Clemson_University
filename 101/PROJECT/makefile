SRC = mainDriver.c contest.c guessedWeight.c personalityTest.c
OBJ = mainDriver.o contest.o guessedWeight.o personalityTest.o
PROG = carnival

$(PROG):$(OBJ)
	gcc -Wall $(OBJ) -o $(PROG)

$(OBJ):$(SRC)

clean: 
	rm *.o carnival
