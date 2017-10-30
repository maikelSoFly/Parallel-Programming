#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<stdbool.h>
#include<math.h>
#include"pomiar_czasu.h"

#define PI 3.14159265358979323846
float result = 0.0;
int num_threads = 2;
int N = 1000;

float f(float x) {
    return sin(x);
}

void * thread_func(void * arg_ptr);
pthread_mutex_t mutex;


main() {
    float a, b, x1, x2, dx, f_val[2];
    int i;
    double t1, t2;
    pthread_t tids[num_threads];
    int ids[num_threads];
    for(i = 0; i < num_threads; i++) ids[i] = i;

    if(pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex init error\n");
    }

    printf("N: %d, num_threads: %d\n\n", N, num_threads);

    t1 = czas_zegara();

    a = 0;
    b = PI;
    dx = (b-a)/N;
    result = 0.0;
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
    t1 = czas_zegara() - t1;
    printf("\tCzas zegara: %f\n", t1);

    printf("\nResult = %.6f\t[One thread]\n\n", result);

    result = 0.0;

    t1 = czas_zegara();
    for(i = 0; i < num_threads; i++) {
        pthread_create(&tids[i], NULL, thread_func, (void*)&ids[i]);
    }

    for(i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
        printf("%lu joined\n", tids[i]);
    }

    result *= 0.5 * dx;
    t1 = czas_zegara() - t1;
    printf("\tCzas zegara: %f\n", t1);
    printf("\nResult = %.6f\t[Multi thread]\n\n", result);


    exit(0);
}

void * thread_func(void * arg_ptr) {
    int id = *(int*)arg_ptr;

    float a, b, x1, x2, myResult, dx, f_val[2];
    int i;
    myResult = 0.0;

    a = 0;
    b = PI;
    dx = (b-a)/N;

    int myN = N/num_threads;

    x1 = id * dx * myN;
    f_val[0] = f(x1);
    for(i = 0; i < myN; i++) {
        x2 = x1 + dx;
        f_val[1] = f(x2);
        myResult += f_val[0] + f_val[1];
        f_val[0] = f_val[1];
        x1 = x2;
    }
    float test = x2 /dx;
    printf("dx: %.6f x2: %.6f, x2/dx: %.6f\n", dx, x2, test );

    pthread_mutex_lock(&mutex);
    result += myResult;
    pthread_mutex_unlock(&mutex);

    return(NULL);
}

// int id = *(int*)arg_ptr;
// double a, b, x1, x2, myResult, dx;
// int i;
// myResult = 0.0;
// int myN = N/num_threads;
//
// a = id * (PI/num_threads);
// b = (id+1) * (PI/num_threads);
// dx = (b-a)/myN;
//
// x1 = a;
//
// for(i = 0; i < myN; i++) {
//     x2 = x1 + dx;
//     myResult += 0.5 * (f(x1) + f(x2)) * dx;
//     x1 = x2;
// }
//
// pthread_mutex_lock(&mutex);
// result += myResult;
// pthread_mutex_unlock(&mutex);
//
// return(NULL);
