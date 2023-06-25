#include <mpi.h>

int main(int argc, char *argv[]){

    MPI_Init(&argc, &argv);

    int total[2], rank[2];
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    rank[1] = 10 * rank[0];

    MPI_Scan(rank, total, 2, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("[MPI process %d] Totals = %d , %d \n", rank[0], total[0], total[1]);

    MPI_Finalize();
}