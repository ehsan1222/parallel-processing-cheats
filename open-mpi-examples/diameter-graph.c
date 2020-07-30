#include <stdio.h>
#include <stdlib.h>
#include <openmpi/mpi.h>

int dijkstra(int source, int n, int m, int arr[][m]);
void master();
void slave();

int main(void) {

    int pridx;

    if(MPI_Init(NULL, NULL))
        return 1;

    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);

    if (pridx == 0)
        master();
    else
        slave();

    MPI_Finalize();

    return 0;
}


void master() {
    // n = number of points, m = number of edges
    int n, m, i, j, prcnt, current;
    int max = 0;
    
    scanf("%d %d", &n, &m);
    
    // declare size of adjancy matrix
    int (*arr)[n] = malloc(sizeof(int[n][n])); 
    
    // initial matrix with max value
    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            arr[i][j] = n + 1;
        }
    }

    // get edges from input
    for (i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        arr[x][y] = 1;
    }

    // send adjancy matrix size
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // send adjancy matrix
    MPI_Bcast(arr, (n * n), MPI_INT, 0, MPI_COMM_WORLD);

    // get process count
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    // receive max path from other processes
    for (i = 1; i < prcnt; i++) {
        MPI_Recv(&current, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(current > max)
            max = current;
    }

    printf("Diameter= %d\n", max);
}

void slave() {
    int pridx, n;
    
    // process id
    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);

    // receive adjancy matrix size
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int (*arr)[n] = malloc(sizeof(int[n][n]));

    // receive adjancy matrix
    MPI_Bcast(arr, (n * n), MPI_INT, 0, MPI_COMM_WORLD);

    int current_index = pridx - 1;
    // calculate maximun minimum path from source node
    int max = dijkstra(current_index, n, n, arr);


    // send result to process 0
    MPI_Send(&max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

int dijkstra(int source, int n, int m, int arr[][m]) {
    int i, j, k;
    int max = 0;
    int shortest[n];

    // initial max value in shortest path array
    for(i = 0; i < n; i++) {
        shortest[i] = n + 1;
    }

    shortest[source] = 0;

    // find shortest path from source to all nodes
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                int diff = shortest[i] + arr[i][j];
                if(diff < shortest[j]) {
                    shortest[j] = diff;
                }
            }
        }
    } 

    // find maximum shortest path
    for(i = 0; i < n; i++) {
        if(shortest[i] > max) 
            max = shortest[i];
    }

    return max;
}