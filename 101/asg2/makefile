OBJS = transform.o mirror.o flipHoriz.o rotate.o  parse.o

transform: $(OBJS)
	gcc -Wall -g -o transform $(OBJS) 

clean:
	rm *.o
	rm *.err
	rm -f transform

