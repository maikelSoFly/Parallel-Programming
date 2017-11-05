#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <math.h>
#include"pomiar_czasu.h"

#define PI 3.14159265358979323846
int num_threads = 10;
int N = 1000;
float result;
pthread_mutex_t mutex;

struct ThreadInput {
    float dx;
    int id;
    float result;
};

float f(float x) {
    return sin(x);
}

void * thread_func1(void * arg_ptr);
void * thread_func2(void * arg_ptr);


main() {
    int i;
    pthread_t tids[num_threads];
    int ids[num_threads];
    struct ThreadInput thread_inputs[num_threads];
    float f_val[2];
    double t;
    float loc_vals[num_threads];
    for(i = 0; i < num_threads; i++) ids[i] = i;



    // Opening txt file
    FILE *file = fopen("results_logs.txt", "a");
    if(file == NULL) {
        printf("Error opening file!\n");
    }

    printf("N: %d, l_watkow: %d:\n", N, num_threads);
    fprintf(file, "N: %d, l_watkow: %d:\n", N, num_threads);

    t = czas_zegara();

    float a, b, x1, x2, dx;

    a = 0;
    b = PI;

    dx = (b-a)/N;

    x1 = a;
    f_val[0] = f(x1);
    for(i = 0; i < N; i++) {
        x2 = x1 + dx;
        f_val[1] = f(x2);
        result += f_val[0] + f_val[1];
        f_val[0] = f_val[1];
        x1 = x2;
    }
    result *= 0.5 * dx;
    t = czas_zegara() - t;

    printf("\tCzas zegara: %f\n", t);
    printf("Wynik: %.6f\t[Single-thread]\n", result);
    fprintf(file, "\tCzas zegara: %f\n", t);
    fprintf(file, "Wynik: %.6f\t[Single-thread]\n", result);
    result = 0.0;


    // 4.

    if(pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex init error\n");
    }

    t = czas_zegara();

    for(i = 0; i < num_threads; i++) {
        pthread_create(&tids[i], NULL, thread_func1, (void*)&ids[i]);
    }

    for(i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
    }

    result *= 0.5 * dx;
    t = czas_zegara() - t;
    printf("\tCzas zegara: %f\n", t);
    printf("Wynik: %.6f\t[Multi-thread (4.)] \n", result);
    fprintf(file, "\tCzas zegara: %f\n", t);
    fprintf(file, "Wynik: %.6f\t[Multi-thread (4.)] \n", result);
    result = 0.0;


    // 5.

    for(i = 0; i < num_threads; i++) {
        thread_inputs[i].dx = dx;
        thread_inputs[i].id = i;
    }

    t = czas_zegara();

    for(i = 0; i < num_threads; i++) {
        pthread_create(&tids[i], NULL, thread_func2, (void*)&thread_inputs[i]);
    }

    for(i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
    }

    for(i = 0; i< num_threads; i++) {
        result += thread_inputs[i].result;
    }
    result *= 0.5 * dx;
    t = czas_zegara() - t;
    printf("\tCzas zegara: %f\n", t);
    printf("Wynik: %.6f\t[Multi-thread (5.)] \n", result);
    fprintf(file, "\tCzas zegara: %f\n", t);
    fprintf(file, "Wynik: %.6f\t[Multi-thread (5.)] \n", result);

    fprintf(file, "\n-----------------\n\n");
    fclose(file);
    exit(0);
}

void * thread_func1(void * arg_ptr) {
    float a, b, x1, x2, dx;
    float loc_result = 0;
    float f_val[2];
    int myN, i;
    int id = *(int*)arg_ptr;

    a = 0;
    b = PI;
    dx = (b-a)/N;

    myN = N/num_threads;

    x1 = id * dx * myN;
    f_val[0] = f(x1);
    for(i = 0; i < myN; i++) {
        x2 = x1 + dx;
        f_val[1] = f(x2);
        loc_result += f_val[0] + f_val[1];
        f_val[0] = f_val[1];
        x1 = x2;
    }

    pthread_mutex_lock(&mutex);
    result += loc_result;
    pthread_mutex_unlock(&mutex);

    return(NULL);
}

void * thread_func2(void * arg_ptr) {
    struct ThreadInput *t_in = (struct ThreadInput*)arg_ptr;
    float a, b, a_loc, b_loc, dx_loc, x1, x2;
    int N, i;
    float loc_result = 0.0;
    float f_val[2];

    int id = t_in->id;
    float dx = t_in->dx;

    a = 0;
    b = PI;
    N = (b-a)/dx;

    a_loc = id * (b/num_threads);
    b_loc = (id+1) * (b/num_threads);
    dx_loc = dx - 0.000000005;
    int N_loc = (b_loc-a_loc)/dx_loc;

    x1 = a_loc;
    f_val[0] = f(x1);
    for(i = 0; i < N_loc; i++) {
        x2 = x1 + dx_loc;
        f_val[1] = f(x2);
        loc_result += f_val[0] + f_val[1];
        f_val[0] = f_val[1];
        x1 = x2;
    }

    pthread_mutex_lock(&mutex);
    t_in->result = loc_result;
    pthread_mutex_unlock(&mutex);

    return(NULL);
}
