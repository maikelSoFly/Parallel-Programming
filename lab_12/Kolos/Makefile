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

all: heat run

run: heat
	$(MPI_run) -hostfile hostfile -np 4 heat

# zaleznosci i komendy
heat : heat.o
	$(LOADER) $(OPT) heat.o -o heat $(LIB)

# jak uzyskac plik moj_program.o ?
heat.o: heat.c
	$(CCOMP) -c $(OPT) heat.c

clean:
	rm -f *.o
