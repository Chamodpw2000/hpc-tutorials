/******************************************************************************
* FILE: omp_reduction.c
* DESCRIPTION:
*   OpenMP Example - Combined Parallel Loop Reduction - C/C++ Version
*   This example demonstrates a sum reduction within a combined parallel loop
*   construct.  Notice that default data element scoping is assumed - there
*   are no clauses specifying shared or private variables.  OpenMP will 
*   automatically make loop index variables private within team threads, and
*   global variables shared.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int   i, n, tid, nthreads;
float a[100], b[100], sum; 

/* Some initializations */
n = 100;
for (i=0; i < n; i++)
  a[i] = b[i] = i * 1.0;
sum = 0.0;

#pragma omp parallel private(tid) reduction(+:sum)
  {
  tid = omp_get_thread_num();
  
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  
  #pragma omp for
  for (i=0; i < n; i++)
    {
    printf("Thread %d computing: a[%d] * b[%d] = %f * %f = %f\n", 
           tid, i, i, a[i], b[i], a[i] * b[i]);
    sum = sum + (a[i] * b[i]);
    }
  }

printf("   Sum = %f\n",sum);

}