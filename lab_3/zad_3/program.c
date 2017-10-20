#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];

typedef struct {
	int liczba;
	char* napis;
	char znak;
} MojaStruktura;


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
	MojaStruktura* przeslana_struktura = (MojaStruktura*)arg_wsk;
	printf("[system tid: %u] liczba: %d, napis: %s, znak: %c\n", pthread_self(), przeslana_struktura->liczba, przeslana_struktura->napis, przeslana_struktura->znak);
	przeslana_struktura->napis = "Nowy napis";
	przeslana_struktura->znak = 'd';
	przeslana_struktura->liczba = 255;
	
	MojaStruktura lokalna_struktura = { przeslana_struktura->liczba, przeslana_struktura->napis, przeslana_struktura->znak };
	printf("[system tid: %u] liczba: %d napis: %s, znak: %c //local\n", pthread_self(), lokalna_struktura.liczba, lokalna_struktura.napis, lokalna_struktura.znak);
	
	lokalna_struktura.napis = "zmiana lokalna";
	lokalna_struktura.liczba = 1111;
	lokalna_struktura.znak = 'f';

	return(NULL);
}

int main()
{
	int size = 10;
	pthread_t tid[size];
	pthread_attr_t attr;
	void *wynik;
	int i;
	MojaStruktura ms = {16, "Mikolaj Stepniewski", 'c'};
	
	printf("Przed utworzeniem watkow:\n  liczba: %d, napis: %s, znak: %c\n\n", ms.liczba, ms.napis, ms.znak);
	
	

	//Wątek przyłączalny
	for(i = 0; i < size; i++) {
		pthread_create(&tid[i], NULL, zadanie_watku, (void*)&ms);
		wait(1);
	}
	
	for(i = 0; i < size; i++) {
		pthread_join(tid[i], &wynik);
		
	}

	
	
	
	
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}



