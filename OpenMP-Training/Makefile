CC = gcc-7
LD = gcc-7


OPT = -O3 -fopenmp
LIB = -lm

integral: integral.o
	$(LD) $(OPT) integral.o -o integral $(LIB)

integral.o: integral.c
	$(CC) -c  $(OPT) integral.c

integral-single-thread: integral-single-thread.o
	$(LD) $(OPT) integral-single-thread.o -o integral-single-thread $(LIB)

integral-single-thread.o: integral-single-thread.c
	$(CC) -c  $(OPT) integral-single-thread.c

helloWorld: helloWorld.o
	$(LD) $(OPT) helloWorld.o -o helloWorld $(LIB)

helloWorld.o: helloWorld.c
	$(CC) -c  $(OPT) helloWorld.c



clean:
	rm -f *.o
