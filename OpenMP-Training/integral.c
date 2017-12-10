#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000000;     double step;
#define NUM_THREADS 10

int main() {
    int i, nthreads;  double pi = 0.0, sum = 0.0, t1, t2;
    step = 1.0/(double)num_steps;

    omp_set_num_threads(NUM_THREADS);
    omp_set_schedule(omp_sched_static, 10000);

    t1 = omp_get_wtime();
    #pragma omp parallel
    {
        double x;

        #pragma omp for schedule(runtime) reduction(+:sum)
        for(i = 0; i < num_steps; i++) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
    }
    pi = sum * step;

    t2 = omp_get_wtime() - t1;
    printf("%.5f\t\ttime: %.8f\n", pi, t2);

    return 0;
}
