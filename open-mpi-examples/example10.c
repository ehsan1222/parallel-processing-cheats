#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    int pridx;

    if (MPI_Init(NULL, NULL)) {
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);

    if (pridx == 0){
        int A[8] = {5, 4, 1, 2, 3, 8, 7, 6};
        printf("Sending from processor %d\n", pridx);
        MPI_Send(A, 8, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        int B[8];
        MPI_Recv(B, 8, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received <%d, %d, %d, ...>\n", B[0], B[1], B[2]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}