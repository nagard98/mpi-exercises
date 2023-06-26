#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char subcomm;
    int colour, key;
    if (rank % 2 == 0) {
        subcomm = 'A';
        colour = 0;
        key = rank;
    }else{
        subcomm = 'B';
        colour = 1;
        key = size - rank;
    }

    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, colour, key, &new_comm);
    int new_comm_rank;
    MPI_Comm_rank(new_comm, &new_comm_rank);

    printf("[Proc %d] i'm rank %d in new subcomm %c.\n",
        rank, new_comm_rank, subcomm);


    MPI_Finalize();
}