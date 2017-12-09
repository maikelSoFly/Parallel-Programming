#include <omp.h>
#include <stdio.h>

static long num_steps = 100000000;     double step;
#define NUM_THREADS 2

int main() {
    int i, nthreads;  double x, pi = 0.0, t1, t2;
    step = 1.0/(double)num_steps;

    omp_set_num_threads(NUM_THREADS);

    t1 = omp_get_wtime();
    #pragma omp parallel
    {
        int i, thread_id, nthrds;
        double x, sum;
        thread_id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        for(i = thread_id, sum = 0.0; i < num_steps; i+=nthrds) {

            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        sum *= step;
    #pragma atomic
            pi += sum;
    }
    t2 = omp_get_wtime() - t1;
    printf("%.5f\t\ttime: %.8f\n", pi, t2);

    return 0;
}
