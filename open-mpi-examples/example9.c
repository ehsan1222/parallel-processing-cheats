#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int prcnt;
    int val = 0;
    int i;
    if (MPI_Init(NULL, NULL)){
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    if (pridx == 1){
        for (i = 1; i < prcnt; i++){
            MPI_Status status;
            MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Received val=%d from %d\n", val, status.MPI_SOURCE);
        }
    }
    else{
        val = 5;
        printf("Sending from processor %d\n", pridx);
        MPI_Send(&val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}