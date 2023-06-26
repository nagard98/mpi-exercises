#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int dim[1], period[1];
    dim[0] = size;
    period[0] = 1;
    MPI_Comm ring;

    int r_buf = 44, s_buf = rank;

    MPI_Cart_create(MPI_COMM_WORLD, 1, dim, period, 0, &ring);

    int source, dest;
    MPI_Request s_req, r_req;
    MPI_Status status;
    MPI_Cart_shift(ring, 0, 1, &source, &dest);
    printf("[Process %d] with source %d and dest %d\n", rank, source, dest);

    MPI_Sendrecv(&s_buf, 1, MPI_INT, dest, 0, &r_buf, 1, MPI_INT, source, 0, ring, &status );
    printf("[Process %d] received %d\n", rank, r_buf);
    
    MPI_Finalize();
}