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
    pthread_mutex_t *taps;
    pthread_t *clients;
    int *client_ids;
    int ctr_beers_drinked;
} pub;

pthread_mutex_t lock;

void * client_thread( void * arg);

main() {
    int *client_iid;
    int i;
    int n_c, n_m, n_t;
    int ctr_return_mugs;

    printf("Podaj liczbe klientow: "); scanf("%d", &n_c);
    printf("Podaj liczbe kufli: "); scanf("%d", &n_m);
    printf("Podaj liczbe kranow: "); scanf("%d", &n_t);

    pub.num_client = n_c;
    pub.num_mug = n_m;
    pub.num_tap = n_t;
    pub.ctr_beers_drinked = 0;

    pub.clients = (pthread_t *) malloc(n_c * sizeof(pthread_t));
    pub.client_ids = (int *) malloc(n_c * sizeof(int));
    for(i = 0; i < n_c; i++) pub.client_ids[i] = i;
    pub.mugs = (bool *) malloc(n_m * sizeof(bool));
    pub.taps = (pthread_mutex_t *) malloc(n_t * sizeof(pthread_mutex_t));
    for(i = 0; i < n_t; i++) pthread_mutex_init(&pub.taps[i], NULL);

    if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init err!\n");
    }

    for(i = 0; i < pub.num_mug; i++) {
        pub.mugs[i] = false;
    }

    printf("\n🍻 Otwieramy pub. Wpuszczamy gosci!\n\n");

    for(i = 0; i < pub.num_client; i++) {
        pthread_create(&pub.clients[i], NULL, client_thread, (void *)&pub.client_ids[i]);
        sleep(1);
    }


    for(i = 0; i < pub.num_client; i++) {
        pthread_join(pub.clients[i], NULL);
        printf("\tThread %lu joined\n", (unsigned long) pub.clients[i]);
    }


    for(int i = 0; i < pub.num_mug; i++) {
        if(pub.mugs[i] == false) ctr_return_mugs++;
    }
    printf("\nMugs state:\t %d/%d returned\n", ctr_return_mugs, pub.num_mug);
    printf("Beers drinked: %d\n", pub.ctr_beers_drinked);

    exit(0);
}

void * client_thread(void * arg_ptr) {
    int wants_to_drink = 2;
    int i = 0;
    int j = 0;
    int id = *(int*)arg_ptr;
    bool got_mug = false;
    bool *my_mug = NULL;
    bool got_tap = false;
    int status;

    for(j = 0; j < wants_to_drink; j++) {
        while(!got_mug) {

            pthread_mutex_lock(&lock);
            for(i = 0; i < pub.num_mug; i++) {

                if(pub.mugs[i] == false) {
                    printf("[Klient o id %d]\t ✅ bierze kufel nr. %d\n", id, i);
                    pub.mugs[i] = true;
                    my_mug = &pub.mugs[i];
                    got_mug = true;
                    break;
                }
            }
            pthread_mutex_unlock(&lock);

            if(!got_mug) printf("[Klient o id %d]\t ⏱  czeka na kufel\n", id);
            usleep(400000);
        }

        while(!got_tap) {
            for(i = 0; i < pub.num_tap; i++) {
                status = pthread_mutex_trylock(&pub.taps[i]);
                if (status == 0) {
                    got_tap = true;
                    printf("[Klient o id %d]\t 🚰 nalewa piwo z kranu nr. %d\n", id, i);
                    sleep(4);
                    pthread_mutex_unlock(&pub.taps[i]);
                    if(got_tap) break;
                }
            }
            if(!got_tap) {
                printf("[Klient o id %d]\t ⏱  czeka na kran\n", id);
                usleep(500000);
            }
        }
        got_tap = false;

        printf("[Klient o id %d]\t 🍺 pije piwo\n", id);
        sleep(2);
        pub.ctr_beers_drinked++;

        printf("[Klient o id %d]\t ↩️  odnosi pusty kufel\n", id);
        pthread_mutex_lock(&lock);
        *my_mug = false;
        got_mug = false;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    printf("[Klient o id %d]\t 🚶 wychodzi z baru\n", id);

    return(NULL);
}
