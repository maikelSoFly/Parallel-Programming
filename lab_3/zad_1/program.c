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
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	printf("\t[watek potomny]: uniemozliwione zabicie\n");

	czasozajmowacz();

	printf("\t[watek potomny]: umozliwienie zabicia\n");
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	pthread_testcancel();

	zmienna_wspolna++;
	printf("\t[watek potomny]: zmiana wartosci zmiennej wspolnej\n");

	return(NULL);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;

	//Wątek przyłączalny

	printf("[watek glowny]: tworzenie watku potomnego nr. 1\n");


	pthread_create(&tid, NULL, zadanie_watku, NULL);   // !!
	sleep(2); // czas na uruchomienie watku

	printf("\t[watek glowny]: wyslanie sygnalu zabicia watku\n");
	pthread_cancel(tid);

	pthread_join(tid, &wynik);

	// Co nalezy zrobić przed sprawdzeniem czy wątki się skonczyły?
	if (wynik == PTHREAD_CANCELED)
		printf("\twatek glowny: watek potomny zostal zabity\n");
	else
		printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");


	zmienna_wspolna = 0;

	printf("[watek glowny]: tworzenie watku potomnego nr. 2\n");


	pthread_create(&tid, NULL, zadanie_watku, NULL);   // !!
	sleep(2); // czas na uruchomienie watku

	printf("\t[watek glowny]: odlaczenie watku potomnego\n");
	pthread_detach(tid);

	printf("\t[watek glowny]: wyslanie sygnalu zabicia watku odlaczonego\n");
	pthread_cancel(tid);

	//Czy watek został zabity? Jak to sprawdzić?
	printf("\t[watek glowny]: czy watek potomny zostal zabity\n");
	printf("\t[watek glowny]: sprawdzanie wartosci zmiennej wspolnej\n");
	for (i = 0;i < 3; i++) {
    printf("\t.\n");
		sleep(6);
		if(zmienna_wspolna != 0) break;
	}


	//Wątek odłączony
	if(zmienna_wspolna == 0)
		printf("\t[watek glowny]: odlaczony watek potomny prawdopodobnie zostal zabity\n");
	else printf("\t[watek glowny]: odlaczony watek potomny prawdopodobnie NIE zostal zabity\n");


	//Inicjacja atrybutów?
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


	//Ustawianie typu watku na odłaczony
	printf("[watek glowny]: tworzenie odlaczonego watku potomnego nr. 3\n");
	pthread_create(&tid, &attr, zadanie_watku, NULL);

	//Niszczenie atrybutów
	pthread_attr_destroy(&attr);

	printf("\twatek glowny: koniec pracy, watek odlaczony pracuje dalej\n");
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
