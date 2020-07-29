#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int prcnt;
    int val;
    int i;
    if (MPI_Init(NULL, NULL)){
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    if (pridx == 0)
    {
        val = 3;
        for(i = 1; i < prcnt; i++) {
            MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("processor %d received val=%d\n", pridx, val);
    }
    
    MPI_Finalize();

    return 0;
}