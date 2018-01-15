# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mpi.h"

/******************************************************************************/

int main( int argc, char** argv ){

	int rank, i, root;
	int noElements, n_loc,size;
	double suma_plus=0, suma_minus=0, suma_cz=0, suma=0;
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	if( rank == 0 )
		noElements = atoi(argv[1]);

	root = 0;

	MPI_Bcast(&noElements, 1, MPI_INT, root, MPI_COMM_WORLD);

	int q = ceil(noElements/size);
	int r = size * q - noElements;

	if ( rank < (size - r) )
		n_loc = q;
	else
		n_loc = q-1;


	int mianownik = n_loc * rank * 2 + 1; //obliczenie wartości mianownika dla pierwszego wyrazu w danym przedziale

	for(i = 0; i<n_loc; i++)
	{
		//jeśli rozmiar zadania jest parzysty
		if ( n_loc % 2 == 0 )
		{
			suma_plus += 1.0 / mianownik;
			suma_minus += 1.0 / (mianownik + 2);
		}
		else //jeśli nie parzysty to na przemian raz trzeba do siebie dodać te wartości a raz trzeba je od siebie odjąć
		{
			if (i%2 == 0)
			{
				suma_plus += 1.0 / mianownik;
				suma_minus += 1.0 / (mianownik + 2);
			}
			else
			{
				suma_plus -= 1.0 / mianownik;
				suma_minus -= 1.0 / (mianownik + 2);
			}
		}

		mianownik += 4; //skok o 4 bo osobno sumujemy dodatnie a osobno sumujemy ujemne wartości
	}

	suma_cz = suma_plus - suma_minus;

	MPI_Reduce(&suma_cz, &suma, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

	if(rank == 0)
	{
		printf("\nWartosc oczekiwana = %lf\n", M_PI);
		printf("Wynik szeregu dla %d liczb wynosi = %lf\n\n", noElements, suma*4);
	}

	MPI_Finalize();
	return(0);
}
