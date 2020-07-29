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
        MPI_Send(&val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("processor %d send val=%d\n", pridx, val);
    } else if(pridx == 1) {
        MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("processor %d receive val=%d\n", pridx, val);
    }
    
    MPI_Finalize();

    return 0;
}