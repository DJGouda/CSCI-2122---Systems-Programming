all: disasm

# implicit rule to build .o from .c files
%.o: %.c 
	gcc -c $<

disasm: main.o line.o max3.o min.o sum.o
	gcc -Wall -o disasm main.o line.o max3.o min.o sum.o
