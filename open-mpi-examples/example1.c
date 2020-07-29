#include <stdio.h>
#include <openmpi/mpi.h>

int main(void) {
    if(MPI_Init(NULL, NULL)) {
        return 1;
    }
    printf("Hello world\n");
    MPI_Finalize();
    return 0;
}