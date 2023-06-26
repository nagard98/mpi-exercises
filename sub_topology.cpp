#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 6) MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);

    int dims[2] = {2,3};
    int periods[2] = {0,0};
    int reorder = 1;

    MPI_Comm cart2d;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cart2d);

    MPI_Comm_rank(cart2d, &rank);

    int coords[2];
    MPI_Cart_coords(cart2d, rank, 2, coords);
    printf("[Proc %d] coord: (%d,%d) in cart2D\n", rank, coords[0], coords[1]);

    int remain_dims[2] = {0, 1};
    MPI_Comm subgrid;
    MPI_Cart_sub(cart2d, remain_dims, &subgrid);

    int subgrid_ranks[3];
    MPI_Allgather(&rank, 1, MPI_INT, subgrid_ranks, 1, MPI_INT, subgrid);

    printf("[Proc %d] in subgrid with %d, %d, %d\n", rank, subgrid_ranks[0], subgrid_ranks[1], subgrid_ranks[2]);

    MPI_Finalize();
}