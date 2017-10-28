#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <stdbool.h>

struct Pub {
    int num_mug;
    int num_client;
    int num_tap;
    bool *mugs;
    bool *taps;
    pthread_t *clients;
    int *client_ids;
} pub;

pthread_mutex_t lock;

void * client_thread( void * arg);

main() {
    int *client_iid;
    int i;
    int n_c, n_m, n_t;
    char *s;

    printf("Podaj liczbe klientow: "); scanf("%d", &n_c);
    printf("Podaj liczbe kufli: "); scanf("%d", &n_m);
    printf("Podaj liczbe kranow: "); scanf("%d", &n_t);

    pub.num_client = n_c;
    pub.num_mug = n_m;
    pub.num_tap = n_t;

    pub.clients = (pthread_t *) malloc(n_c * sizeof(pthread_t));
    pub.client_ids = (int *) malloc(n_c * sizeof(int));
    for(i = 0; i < n_c; i++) pub.client_ids[i] = i;
    pub.mugs = (bool *) malloc(n_c * sizeof(bool));
    pub.taps = (bool *) malloc(n_c * sizeof(bool));

    if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init err!\n");
    }

    for(i = 0; i < pub.num_mug; i++) {
        pub.mugs[i] = false;
    }

    printf("Otwieramy pub. Wpuszczamy gosci!\n\n");

    for(i = 0; i < pub.num_client; i++) {
        pthread_create(&pub.clients[i], NULL, client_thread, (void *)&pub.client_ids[i]);
        sleep(1);
    }


    for(i = 0; i < pub.num_client; i++) {
        pthread_join(pub.clients[i], NULL);
        printf("\tThread %lu joined\n", (unsigned long) pub.clients[i]);
    }

    printf("\nMugs state:\n[");
    for(int i = 0; i < pub.num_mug; i++) {
        printf("%d, ", pub.mugs[i]);
    }
    printf("]\n");


    exit(0);
}

void * client_thread(void * arg_ptr) {
    int wants_to_drink = 2;
    int i = 0;
    int j = 0;
    int id = *(int*)arg_ptr;
    bool got_mug = false;
    bool *my_mug = NULL;

    for(j = 0; j < wants_to_drink; j++) {
        while(!got_mug) {
            pthread_mutex_lock(&lock);
            for(i = 0; i < pub.num_mug; i++) {
                if(pub.mugs[i] == false) {
                    printf("[Klient o id %d]\t bierze kufel nr. %d\n", id, i);
                    pub.mugs[i] = true;
                    my_mug = &pub.mugs[i];
                    got_mug = true;
                    break;
                }
            }
            pthread_mutex_unlock(&lock);
            if(!got_mug) printf("[Klient o id %d]\t czeka na kufel\n", id);
            usleep(400000);
        }

        printf("[Klient o id %d]\t nalewa piwo z kranu\n", id);
        usleep(200000);
        printf("[Klient o id %d]\t pije piwo\n", id);
        sleep(2);

        printf("[Klient o id %d]\t odnosi pusty kufel\n", id);
        pthread_mutex_lock(&lock);
        *my_mug = false;
        got_mug = false;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    printf("[Klient o id %d]\t wychodzi z baru\n", id);

    return(NULL);
}
