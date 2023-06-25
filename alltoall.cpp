#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if( size != 3){
        printf("ERROR::Need to launch 3 MPI processes\n ");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int my_values[3];
    for(int i=0; i<3; i++){
        my_values[i] = rank * 300 + i * 100;
    }

    printf("Process %d, values: %d, %d, %d\n", rank, my_values[0], my_values[1], my_values[2]);

    int buffer_recv[3];
    MPI_Alltoall(&my_values, 1, MPI_INT, buffer_recv, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Values received by processes %d: %d, %d, %d\n", rank, buffer_recv[0],buffer_recv[1], buffer_recv[2]);

    MPI_Finalize();
}