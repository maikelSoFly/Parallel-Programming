#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {
    float res;
    int niters = 100000;

    #pragma omp parallel
    {
        float B; int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for(i = 0; i < niters; i++) {
            B = big_job(i);

    #pragma omp crictical
            res += consume(B);
        }
    }
    
    return 0;
}
