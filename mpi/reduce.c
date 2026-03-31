#include <mpi.h>
#include <stdio.h>

int main(int argc , char** argv){

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int threshold;
    int local_value = rank * 15;
    int local_contribution = 0;
    int global_sum = 0;

    if(rank==0){
        threshold = 10;
        printf("Rank 0 broadcasting threshold: %d\n", threshold);
    }

    MPI_Bcast(&threshold,1,MPI_INT,0,MPI_COMM_WORLD);

    if(local_value> threshold){
        local_contribution = local_value;
    }

    printf("Rank %d has local_value %d -> contribution is %d\n", rank , local_value, local_contribution);

    MPI_Reduce(&local_contribution, &global_sum, 1 , MPI_INT , MPI_SUM, 0 , MPI_COMM_WORLD);

if(rank==0){
    printf("Global sum from rank 0 is %d\n", global_sum);
}

MPI_Finalize();


return 0;


}