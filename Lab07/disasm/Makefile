all: disasm

# implicit rule to build .o from .c files
%.o: %.c 
	gcc -c $<

disasm: main.o enigma.o mystery.o puzzle.o riddle.o
	gcc -Wall -o disasm main.o enigma.o mystery.o puzzle.o riddle.o
