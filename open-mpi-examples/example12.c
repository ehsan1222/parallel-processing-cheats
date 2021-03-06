#include <stdio.h>
#include <unistd.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;
    int val = 0;
    if (MPI_Init(NULL, NULL)) {
        return 1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    if (pridx == 0){
        val = 5;
        sleep(2);
        printf("Sending...\n");
        MPI_Send(&val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Request request;
        printf("Before Receiving.....\n");
        MPI_Irecv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        printf("After MPI_Irecv(), val=%d\n", val);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("After MPI_Wait(), val=%d\n", val);
    }
    MPI_Finalize();
    
    return 0;
}