#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank, root, *buff;
    int sendArr[100];

    root=0;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for(int i=0; i<100; i++) sendArr[i] = rank;

    if(rank == root){
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        buff = (int*)malloc(size * 100 * sizeof(int));
    }

    MPI_Gather(sendArr, 100, MPI_INT, buff, 100, MPI_INT, root, MPI_COMM_WORLD);

    if(rank==root){
        for(int i=0; i < size*100; i++){
            printf("%d , ", buff[i]);
        }
    }

    MPI_Finalize();
}