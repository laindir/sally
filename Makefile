CFLAGS=-Wall -Wextra -pedantic -ansi -g

interpreter: primitives.o arch.o

primitives.o: primitives.h arch.h

arch.o: arch.h

interpreter.o: primitives.h arch.h
