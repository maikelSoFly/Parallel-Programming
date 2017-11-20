#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
    while(!czytelnia_p->jest_co_czytac) pthread_cond_wait(&czytelnia_p->czytac, &czytelnia_p->mutex);
}

int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    czytelnia_p->ile_przeczytalo++;
    if(czytelnia_p->ile_przeczytalo == 10) {
        czytelnia_p->ile_przeczytalo = 0;
        czytelnia_p->jest_co_czytac = 0;
        pthread_cond_signal(&czytelnia_p->pisac);
    }
    czytelnia_p->ilosc_czytelnikow--;
}

int my_write_lock_lock(czytelnia_t* czytelnia_p){
    while(czytelnia_p->jest_co_czytac) pthread_cond_wait(&czytelnia_p->pisac, &czytelnia_p->mutex);
}

int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    czytelnia_p->ilosc_pisarzy--;
    pthread_cond_signal(&czytelnia_p->czytac);
}

void inicjuj(czytelnia_t* czytelnia_p){
    czytelnia_p->jest_pisarz = 0;
    czytelnia_p->jest_co_czytac = 0;
    pthread_rwlock_init(&czytelnia_p->mutex, NULL);
    pthread_cond_init(&czytelnia_p->czytac, NULL);
    pthread_cond_init(&czytelnia_p->pisac, NULL);
    czytelnia_p->ilosc_pisarzy = 0;
    czytelnia_p->ilosc_czytelnikow = 0;
    czytelnia_p->ile_przeczytalo = 0;
}

void czytam(czytelnia_t* czytelnia_p){
    czytelnia_p->ilosc_czytelnikow++;
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
    czytelnia_p->ilosc_pisarzy++;
    usleep(rand()%1000000);
    czytelnia_p->jest_co_czytac = 1;

}
