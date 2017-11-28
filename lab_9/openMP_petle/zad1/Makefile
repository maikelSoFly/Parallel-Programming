CC = gcc
LD = gcc


OPT = -O3 -fopenmp
LIB = -lm

openmp_petle_wiersz_red: openmp_petle_wiersz_red.o
	$(LD) $(OPT) openmp_petle_wiersz_red.o -o openmp_petle_wiersz_red $(LIB)

openmp_petle_wiersz_red.o: openmp_petle_wiersz_red.c
	$(CC) -c  $(OPT) openmp_petle_wiersz_red.c

openmp_petle_wiersz_tab: openmp_petle_wiersz_tab.o
	$(LD) $(OPT) openmp_petle_wiersz_tab.o -o openmp_petle_wiersz_tab $(LIB)

openmp_petle_wiersz_tab.o: openmp_petle_wiersz_tab.c
	$(CC) -c  $(OPT) openmp_petle_wiersz_tab.c

openmp_petle_kolu_red: openmp_petle_kolu_red.o
	$(LD) $(OPT) openmp_petle_kolu_red.o -o openmp_petle_kolu_red $(LIB)

openmp_petle_kolu_red.o: openmp_petle_kolu_red.c
	$(CC) -c  $(OPT) openmp_petle_kolu_red.c

openmp_petle_kolu_pryw: openmp_petle_kolu_pryw.o
	$(LD) $(OPT) openmp_petle_kolu_pryw.o -o openmp_petle_kolu_pryw $(LIB)

openmp_petle_kolu_pryw.o: openmp_petle_kolu_pryw.c
	$(CC) -c  $(OPT) openmp_petle_kolu_pryw.c

clean:
	rm -f *.o
