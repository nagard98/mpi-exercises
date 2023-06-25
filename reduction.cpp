#include <mpi.h>

int main(int argc, char *argv[]){
    int i, rank;
    int root = 2;

    double ain[30], aout[30];
    int ind[30];

    struct {
        double val;
        int rank;
    } in[30], out[30];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(i = 0; i < 30; i++){
        in[i].val = i * (rank + 1);
        in[i].rank = rank;
    }

    MPI_Reduce(in, out, 30, MPI_DOUBLE_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);

    if(rank == root){
        for(i=0; i<30; ++i){
            aout[i] = out[i].val;
            ind[i] = out[i].rank;
            printf("At index %d reduction is %f from process with rank %d\n", i, aout[i], ind[i]);
        }
    }

    MPI_Finalize();
}