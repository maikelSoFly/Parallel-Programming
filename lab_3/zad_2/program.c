#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];


double czasozajmowacz(){
  int i, j, k;
  int n=WYMIAR;
  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
  for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i+n*j]=0.0;
      for(k=0;k<n;k++){
	c[i+n*j] += a[i+n*k]*b[k+n*j];
      }
    }
  }
  return(c[ROZMIAR-1]);
}

void * zadanie_watku (void * arg_wsk)
{
	int przeslane_id = *((int*)arg_wsk);
	printf("[system tid: %lu] przeslane id: %d\n", pthread_self(), przeslane_id);

	return(NULL);
}

int main()
{
	int size = 10;
	pthread_t tid[size];
	pthread_attr_t attr;
	void *wynik;
	int i;

	//Wątek przyłączalny
	for(i = 0; i < size; i++) {
		pthread_create(&tid[i], NULL, zadanie_watku, (void*)&i);
		wait(1);
	}

	for(i = 0; i < size; i++) {
		pthread_join(tid[i], &wynik);
	}

	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
