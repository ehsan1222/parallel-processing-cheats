#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {

    int pridx;
    int prcnt;

    if(MPI_Init(NULL, NULL)){
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    printf("Processor %d of %d\n", pridx, prcnt);

    MPI_Finalize();

    return 0;
} 