#include <mpi.h>

int main(int argc, char *argv[]){
    int numtasks, rank, next, prev;
    int buf[2], tag1=1, tag2=2;
    MPI_Request reqs[4];
    MPI_Status stats[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    prev = (rank + numtasks - 1 ) % numtasks;
    next = (rank + 1) % numtasks;
    MPI_Waitall(4, reqs, stats);

    printf("Task %d communicated with tasks %d & %d\n", rank, prev, next);
    MPI_Finalize();
}