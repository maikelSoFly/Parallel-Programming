#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {
    int A[NUM_THREADS], B[NUM_THREADS];

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        A[id] = big_calc1(id);

    #pragma omp barrier
        B[id] = big_calc2(id, A)

    }

    return 0;
}
