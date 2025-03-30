
# compilers, linkers, utilities, and flags
CC = gcc
CFLAGS = -Wall -g
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(CFLAGS) -o $@ 

# implicit rule to build .o from .c files
%.o: %.c 
	$(COMPILE) -c -o $@ $<


# explicit rules
mycp: main.o
	$(LINK) main.o

clean:
	rm -f *.o mycp
