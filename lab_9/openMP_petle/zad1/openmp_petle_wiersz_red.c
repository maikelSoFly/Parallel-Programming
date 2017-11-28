#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 13

main ()
{
	double a[WYMIAR][WYMIAR];
	int n,i,j;

	for(i=0;i<WYMIAR;i++) 
		for(j=0;j<WYMIAR;j++) 
			a[i][j]=1.02*i+1.01*j;

	n=WYMIAR;

	double suma=0.0;
	for(i=0;i<WYMIAR;i++) {
		for(j=0;j<WYMIAR;j++) {
			suma += a[i][j];
		}
	}

	printf("Suma wyrazów tablicy: %lf\n", suma);

	omp_set_nested(1);

	double suma_parallel=0.0;
	#pragma omp parallel for ordered shared(a) private(i, j) reduction(+:suma_parallel)
	for(i=0;i<WYMIAR;i++) {
		int id_w = omp_get_thread_num();
		// ...
		for(j=0;j<WYMIAR;j++) {
			suma_parallel += a[i][j];
			// ...
			#pragma omp ordered
			{
				printf("(%2d,%2d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num());
			}
		}
		// ...
		printf("\n");
	}

	printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}
