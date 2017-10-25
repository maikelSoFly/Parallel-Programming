#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <stdbool.h>

#define KUFEL_SIZE = 4;
pthread_mutex_t lock;

void * watek_klient (void * arg);

main() {
    int l_kufel = 3;
    int l_klient = 8;
    int i;
    pthread_t tid[l_klient];
    bool kufle[l_kufel];

    for (i = 0; i < l_kufel; i++) {
        kufle[i] = true;
    }

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex nie zostal utworzony\n");
    }

    printf("\nOtwieramy pub!\n");
    printf("\nLiczba wolnych kufli %d\n", l_kufel);

    for(i = 0; i < l_klient; i++) {
        pthread_create(&tid, NULL, watek_klient, (void*)&kufle);
        wait(1);
    }


    for (i = 0; i < l_klient; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("\nStan kufli:\n");
    for (int i = 0; i < l_kufel; i++) {
        printf("%d ", kufle[i]);
    }
    printf("\n");
}

void * watek_klient (void * arg) {
    int chce_wypic = 2;
    int i;
    int j;
    bool *array = arg;
    unsigned long int id = pthread_self();

    for (i = 0; i < chce_wypic; i++) {
        int id_kufla;
        bool sukces = false;


        while(sukces == false) {
            pthread_mutex_lock(&lock);
            for(j = 0; j < 3; j++) {
                printf("%d, %d", array[i], i);
                if (array[j] == true) { // Jeśli kufel jest wolny
                    printf("\nKlient %lu, wybieram kufel nr.%d\n", id, j);
                    array[j] = false; // Pobranie kufla

                    id_kufla = j;
                    sukces = true;
                    break;
                }
            }
            pthread_mutex_unlock(&lock);
            if(sukces == false) {
                printf("\nKlient %lu, czeka\n", id);
                usleep(300);
            }

        }


        printf("\nKlient %lu, nalewam z kranu\n", id);
        usleep(300);
        printf("\nKlient %lu, pije\n", id);
        usleep(3000);
        pthread_mutex_lock(&lock);
        printf("\nKlient %lu, odkladam kufel nr. %d\n", id, id_kufla);
        array[id_kufla] = true;
        pthread_mutex_unlock(&lock);
    }

    printf("\nKlient %lu, wychodzi z pubu\n", id);

    return NULL;
}
