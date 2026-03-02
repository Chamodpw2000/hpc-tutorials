/******************************************************************************
 * FILE: omp_workshare2.c
 * DESCRIPTION:
 *   OpenMP Example - Sections Work-sharing - C Version
 *   In this example, the OpenMP SECTION directive is used to assign
 *   different array operations to each thread that executes a SECTION.
 * AUTHOR: Blaise Barney  5/99
 * LAST REVISED: 07/16/07
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int main(int argc, char *argv[])
{
    int i, nthreads, tid;
    float a[N], b[N], c[N];

    /* Some initializations */
    for (i = 0; i < N; i++)
    {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
        c[i] = 0.0;
    }

#pragma omp parallel shared(a, b, c, nthreads) private(i, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

#pragma omp sections nowait
        {
#pragma omp section
            {
                printf("Thread %d doing section 1 (addition)\n", tid);
                for (i = 0; i < N/2; i++)
                {
                    c[i] = a[i] + b[i];
                    printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
                }
            }

#pragma omp section
            {
                printf("Thread %d doing section 2 (multiplication)\n", tid);
                for (i = N/2; i < N; i++)
                {
                    c[i] = a[i] * b[i];
                    printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
                }
            }

        } /* end of sections */

        printf("Thread %d done.\n", tid);

    } /* end of parallel section */
}