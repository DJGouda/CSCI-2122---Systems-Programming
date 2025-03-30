
# compilers, linkers, utilities, and flags
CC = gcc
CFLAGS = -Wall -g
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(CFLAGS) -o $@ 

# implicit rule to build .o from .c files
%.o: %.c 
	$(COMPILE) -c -o $@ $<


# explicit rules
jumpy: main.o
	$(LINK) main.o

makej: makej.o 
	$(LINK) makej.o
	
encodej: encodej.o 
	$(LINK) encodej.o
	
clean:
	rm -f *.o $(PROGRAM) encodej makej
