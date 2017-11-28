CC = gcc
LD = gcc


OPT = -O3 -fopenmp
LIB = -lm

parallel2_1D: parallel2_1D.o
	$(LD) $(OPT) parallel2_1D.o -o parallel2_1D $(LIB)

parallel2_1D.o: parallel2_1D.c
	$(CC) -c  $(OPT) parallel2_1D.c

parallel2_2D: parallel2_2D.o
	$(LD) $(OPT) parallel2_2D.o -o parallel2_2D $(LIB)

parallel2_2D.o: parallel2_2D.c
	$(CC) -c  $(OPT) parallel2_2D.c

parallel2_DD: parallel2_DD.o
	$(LD) $(OPT) parallel2_DD.o -o parallel2_DD $(LIB)

parallel2_DD.o: parallel2_DD.c
	$(CC) -c  $(OPT) parallel2_DD.c

clean:
	rm -f *.o
