#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int prcnt;
    int val = 0;

    if(MPI_Init(NULL, NULL)){
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);

    if (pridx == 2)
    {
        val = 5;
    }

    printf("Processor %d, val=%d\n", pridx, val);
    MPI_Finalize();

    return 0;
}