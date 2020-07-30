#include <stdio.h>
#include <stdlib.h>
#include <openmpi/mpi.h>

void master();
void slave();
int gcd(int, int);

int main(void) {
    int pridx;

    if (MPI_Init(NULL, NULL)) {
        return 1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    if(pridx == 0) {
        master();
    } else {
        slave();
    }
    MPI_Finalize();

    return 0;
}


void master() {
    long *num, *result;
    int prcnt, n, i, j, result_cnt;

    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    scanf("%d", &n);

    num = malloc(n * sizeof(long));
    result = malloc(n * sizeof(long));

    for(i = 0; i < n; i++) {
        scanf("%ld", &num[i]);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(num, n, MPI_LONG, 0, MPI_COMM_WORLD);
    
    for(i = 1; i < prcnt; i++) {
        MPI_Recv(&result_cnt, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(result, result_cnt, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (j = 0; j < result_cnt; j++) {
            printf("%ld\n", result[j]);
        }
    }

    free(result);
    free(num);
}


void slave() {
    long *num, *result;
    int n, pridx, prcnt, i, j, result_cnt = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);
        
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    num = malloc(n * sizeof(long));
    result = malloc(n * sizeof(long));
    MPI_Bcast(num, n, MPI_LONG, 0, MPI_COMM_WORLD);

    int begin = (pridx - 1) * n / (prcnt - 1);
    int end = (pridx + 1) < prcnt ? pridx * n / (prcnt - 1) : n;

    for (i = begin; i < end; i++) {
        for (j = 0; j < n; j++) {
            if (i!=j && gcd(num[i], num[j]) != 1) {
                break;
            }
        }
        if(j == n) {
            result[result_cnt++] = num[i];
        }
    }

    MPI_Send(&result_cnt, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(result, result_cnt, MPI_LONG, 0, 0, MPI_COMM_WORLD); 

    free(num);
    free(result);
}


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}