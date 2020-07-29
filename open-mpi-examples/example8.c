#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int prcnt;
    int val = 0;
    int i;

    if(MPI_Init(NULL, NULL)) {
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    if (pridx == 0)
    {
        for(i = 1; i < prcnt; i++) {
            MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Recieved: %d\n", val);
        }
    } else {
        val = pridx;
        MPI_Send(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("processor %d send val=%d\n", pridx, val);
    }

    MPI_Finalize();
    
    return 0;
}