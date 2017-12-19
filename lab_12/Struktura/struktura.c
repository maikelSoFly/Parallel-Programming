#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>

#include "mpi.h"

#define TAB_SIZE 4

struct my_struct
{
	int liczba;
	double liczba2;
	char znak;
	char tab[TAB_SIZE];
};

int main(int argc, char **argv)
{
	int rank, ranksent, size, source, dest, tag, i;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rozm, pakiet_size, poz;
	void* buforIn, *buforOut;

	MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozm);
	pakiet_size = rozm;
	MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &rozm);
	pakiet_size += rozm;
	MPI_Pack_size(1, MPI_CHAR, MPI_COMM_WORLD, &rozm);
	pakiet_size += rozm;
	MPI_Pack_size(TAB_SIZE, MPI_CHAR, MPI_COMM_WORLD, &rozm);
	pakiet_size += rozm;

	buforIn = (void*) malloc(pakiet_size);
	buforOut = (void*) malloc(pakiet_size);
	poz = 0;

	if (size > 1)
	{
		if (rank == 0)
		{
			dest = 1;
			tag = 0;

			struct my_struct rekord = {rank, 21.37, (char)(rank + 67), {'a', 'b', 'c', 'd'}};

			MPI_Pack(&rekord.liczba, 1, MPI_INT, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekord.liczba2, 1, MPI_DOUBLE, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekord.znak, 1, MPI_CHAR, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekord.tab[0], TAB_SIZE, MPI_CHAR, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);

			MPI_Send(buforIn, poz, MPI_PACKED, dest, tag, MPI_COMM_WORLD);
		}
		else
		{
			dest = rank + 1;

			struct my_struct rekordOut;

			MPI_Recv(buforOut, pakiet_size, MPI_PACKED, (rank - 1), MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			MPI_Unpack(buforOut, pakiet_size, &poz, &rekordOut.liczba, 1, MPI_INT, MPI_COMM_WORLD);
			MPI_Unpack(buforOut, pakiet_size, &poz, &rekordOut.liczba2, 1, MPI_DOUBLE, MPI_COMM_WORLD);
			MPI_Unpack(buforOut, pakiet_size, &poz, &rekordOut.znak, 1, MPI_CHAR, MPI_COMM_WORLD);
			MPI_Unpack(buforOut, pakiet_size, &poz, &rekordOut.tab, TAB_SIZE, MPI_CHAR, MPI_COMM_WORLD);

			printf("Proces %d otrzymal od procesu %d:\n\tliczbe: %d\n\tliczbe2: %lf\n\tznak: %c\n\ttablice: %s\n\n",
			       rank, status.MPI_SOURCE, rekordOut.liczba, rekordOut.liczba2, rekordOut.znak, rekordOut.tab);


			struct my_struct rekordIn = {rank,44.423,(char)(rank + 63),{'e', 'f', 'g', 'h'}};
			poz = 0;
			MPI_Pack(&rekordIn.liczba, 1, MPI_INT, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekordIn.liczba2, 1, MPI_DOUBLE, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekordIn.znak, 1, MPI_CHAR, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);
			MPI_Pack(&rekordIn.tab[0], TAB_SIZE, MPI_CHAR, buforIn, pakiet_size, &poz, MPI_COMM_WORLD);

			if (rank != (size - 1))
				MPI_Send(buforIn, poz, MPI_PACKED, dest, tag, MPI_COMM_WORLD);
		}
	}
	else
	{
		printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
	}


	MPI_Finalize();

	return (0);
}
