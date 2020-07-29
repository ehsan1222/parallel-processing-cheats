#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;

    if(MPI_Init(NULL, NULL)) {
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);

    printf("processor %d at A\n", pridx);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("processor %d at B\n", pridx);

    MPI_Finalize();

    return 0;
}