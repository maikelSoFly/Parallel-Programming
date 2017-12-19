#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define FINISH 0

int main( int argc, char** argv ){

        int rank, ranksent, size, source, dest, tag, i;
        MPI_Status status;

        MPI_Init( &argc, &argv );
        MPI_Comm_rank( MPI_COMM_WORLD, &rank );
        MPI_Comm_size( MPI_COMM_WORLD, &size );

        if(size>1) {

            if(rank == 0) {
                dest = rank+1;
                MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
                printf("Proces %d wysłał dane do procesu %d\n", rank, rank+1);
                fflush(stdout);

                if(FINISH==0) {
                    MPI_Recv( &ranksent, 1, MPI_INT, rank-1,
                              MPI_ANY_TAG, MPI_COMM_WORLD, &status );
                    printf("Proces %d otrzymał liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);
                    fflush(stdout);
                }
            }

            else if(rank == size-1) {
                MPI_Recv( &ranksent, 1, MPI_INT, rank-1,
                          MPI_ANY_TAG, MPI_COMM_WORLD, &status );
                printf("Proces %d otrzymał liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);
                fflush(stdout);

                if(FINISH==0) {
                    MPI_Send( &rank, 1, MPI_INT, 0, tag, MPI_COMM_WORLD );
                    printf("Proces %d wysłał dane do procesu %d\n", rank, 0);
                    fflush(stdout);
                } else {
                    printf("Koniec przesyłania - proces: %d\n", rank);
                    fflush(stdout);
                }

            }

            else {
                dest = rank+1;
                MPI_Recv( &ranksent, 1, MPI_INT, rank-1,
                          MPI_ANY_TAG, MPI_COMM_WORLD, &status );
                printf("Proces %d otrzymał liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);
                fflush(stdout);

                MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
                printf("Proces %d wysłał dane do procesu %d\n", rank, dest);
                fflush(stdout);
            }

        }
        else{
            printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
        }


        MPI_Finalize();

        return(0);

}
