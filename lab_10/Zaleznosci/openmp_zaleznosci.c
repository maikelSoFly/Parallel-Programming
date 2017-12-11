#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<math.h>

#define N 100000000


int main(){

  int i;
  double *A = (double*)malloc(sizeof(double)*(N+2));
  double *B = (double*)malloc(sizeof(double)*(N+2));
  double suma;
  double *C = (double*)malloc(sizeof(double)*(N+2));
  double *D = (double*)malloc(sizeof(double)*(N+2));

  for(int i = 0; i < N+2; i++){
    C[i] = D[i] = 0;
  }

  for(i=0;i<N+2;i++) A[i] = (double)i/N;
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;

  // wersja sekwencyjna
  double t1 = omp_get_wtime();
  for(i=0; i<N; i++){
    C[i] += A[i+2] + sin(B[i]);
  }

  suma = 0.0;
  for(i=0;i<N+2;i++) suma+=C[i];
  t1 = omp_get_wtime() - t1;

  printf("suma %lf, czas obliczen %lf\n", suma, t1);


  // restore arrays
  for(i=0;i<N+2;i++) A[i] = (double)i/N;
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;



  // wersja równoległa
  omp_set_num_threads(4);
  printf("Liczba watkow %d\n", omp_get_max_threads());

  t1 = omp_get_wtime();
  #pragma omp parallel for
  for(int i = 0; i < N; i++){
    D[i] += A[i + 2] + sin(B[i]);
  }

  suma = 0.0;
  #pragma omp parallel for reduction(+:suma)
    for(i=0;i<N+2;i++) suma+=D[i];
  t1 = omp_get_wtime() - t1;

  printf("suma %lf, czas obliczen rownoleglych %lf\n", suma, t1);


}
