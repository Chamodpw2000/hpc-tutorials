#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int shared_value;

    if(rank == 0){
        shared_value = 555;
    }

    MPI_Bcast(&shared_value, 1 , MPI_INT , 0 , MPI_COMM_WORLD);
    printf("Process %d received value %d\n", rank, shared_value);
    MPI_Finalize();
    return 0;
}