#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {
    double X = 0.0;

    #pragma omp parallel
    {
        double tmp, B;
        B = DOIT();
        tmp = big_ugly(B);
                        // ATOMIC DOES THE SAME AS CRITICAL SECTION BUT
    #pragma omp atomic  // ITS FOR SIMPLE BINARY OPS (TO BE FASTER) !!
            X += tmp;
        }
    }

    return 0;
}
