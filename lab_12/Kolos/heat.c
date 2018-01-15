# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mpi.h"

/******************************************************************************/

int main( int argc, char **argv )
{
	int rank, size;
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	int sendarray[9];
	int i;

	for ( i = 0; i < 9; i++ )
	{
		sendarray[i] = (rank + 1) * 10 + (i + 1);
		//printf( "[%d] %d\n", (rank + 1), sendarray[i] );
	}
	//printf( "\n" );

	int *rbuf;
	rbuf = (int *) malloc( 9 * sizeof( int ));
	for ( i = 0; i < 9; i++ )
		rbuf[i] = 0;

	//Odkomentuj interesującą Cię operację resztę pozostawiając zakomentowaną
	MPI_Gather( &sendarray[1], 1, MPI_INT, &rbuf[3], 1, MPI_INT, 0, MPI_COMM_WORLD );
	//MPI_Scatter( &sendarray[0], 3, MPI_INT, &rbuf[0], 3, MPI_INT, 0, MPI_COMM_WORLD );
	//MPI_Allgather( &sendarray[1], 2, MPI_INT, &rbuf[3], 2, MPI_INT, MPI_COMM_WORLD );
	//MPI_Scatter( &sendarray[2], 2, MPI_INT, &rbuf[2], 2, MPI_INT, 2, MPI_COMM_WORLD );
	//MPI_Allreduce(&sendarray[3], &rbuf[2], 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	for ( i = 0; i < 9; i++ )
		printf( "P%d : %d\n", (rank + 1), rbuf[i] );
	printf("\n");

	MPI_Finalize();
	return (0);
}
