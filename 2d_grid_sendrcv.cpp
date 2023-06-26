#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int dim[] = {4, 3};
    int period[] = {1, };

    int r_buf, s_buf = rank;

    MPI_Comm grid;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 0, &grid);
    int source, dest;
    MPI_Status status;

    for(int dm=0; dm < 2; dm++){
        for(int verso = - 1; verso < 2; verso += 2){
            MPI_Cart_shift(grid, dm, verso, &source, &dest);

            MPI_Sendrecv(&s_buf, 1, MPI_INT, dest, 0, &r_buf, 1, MPI_INT, source, 0, grid, &status);
            int coords[2];
            MPI_Cart_coords(grid, source, 2, coords);
            printf("[Process %d] received value %d from coords (%d,%d)\n", rank, r_buf, coords[0], coords[1]);
        }
    }

    MPI_Finalize();
}