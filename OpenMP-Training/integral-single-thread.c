#include <omp.h>
#include <stdio.h>

static long num_steps = 100000000;     double step;

int main() {
    int i;  double x, pi, sum, t1, t2;
    step = 1.0/(double)num_steps;

    t1 = omp_get_wtime();
    for(i = 0; i < num_steps; i++) {
        x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x);
    }

    pi += sum * step;
    t2 = omp_get_wtime() - t1;
    printf("%.5f\t\ttime: %.8f\n", pi, t2);

    return 0;
}
