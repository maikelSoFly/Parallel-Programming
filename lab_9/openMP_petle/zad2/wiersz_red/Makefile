CC = gcc
LD = gcc


OPT = -O3 -fopenmp
LIB = -lm

static3: static3.o
	$(LD) $(OPT) static3.o -o static3 $(LIB)

static3.o: static3.c
	$(CC) -c  $(OPT) static3.c

staticD: staticD.o
	$(LD) $(OPT) staticD.o -o staticD $(LIB)

staticD.o: staticD.c
	$(CC) -c  $(OPT) staticD.c

dynamic2: dynamic2.o
	$(LD) $(OPT) dynamic2.o -o dynamic2 $(LIB)

dynamic2.o: dynamic2.c
	$(CC) -c  $(OPT) dynamic2.c

dynamicD: dynamicD.o
	$(LD) $(OPT) dynamicD.o -o dynamicD $(LIB)

dynamicD.o: dynamicD.c
	$(CC) -c  $(OPT) dynamicD.c

clean:
	rm -f *.o
