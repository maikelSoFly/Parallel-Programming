# kompilator c
CCOMP = /usr/local/bin/mpicc

# konsolidator
LOADER = /usr/local/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/local/bin/mpirun

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

all: pi run

run: pi
	$(MPI_run) -hostfile hostfile -np 8 pi

run2:
	$(MPI_run) --hostfile hostfile -np 8 pi 100000

# zaleznosci i komendy
pi : pi.o
	$(LOADER) $(OPT) pi.o -o pi $(LIB)

# jak uzyskac plik moj_program.o ?
pi.o: pi.c
	$(CCOMP) -c $(OPT) pi.c

clean:
	rm -f *.o
