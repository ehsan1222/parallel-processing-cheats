#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int val = 2;
    
    if(MPI_Init(NULL, NULL)) {
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    if (pridx == 0)
    {
        val = 5;
        MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("processor %d received val=%d\n", pridx, val);
    }

    MPI_Finalize();

    return 0;
}