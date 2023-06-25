#include <mpi.h>

int main(int argc, char *argv[]){
    int tutti, myrank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &tutti);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    printf("Hello World! from process %d (from total of %d)\n", myrank, tutti);
    MPI_Finalize();
}