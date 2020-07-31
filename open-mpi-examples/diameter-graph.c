#include <stdio.h>
#include <stdlib.h>
#include <openmpi/mpi.h>

int bfs(int source, int n, int arr[][n]);
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

    // get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    // receive max path from other processes
    for (i = 1; i < prcnt; i++) {
        MPI_Recv(&current, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(current > max)
            max = current;
    }

    printf("Diameter= %d\n", max);

    free(arr);
}

void slave() {
    int pridx, prcnt, n, i;
    int max = 0;

    // process id
    MPI_Comm_rank(MPI_COMM_WORLD, &pridx);
    MPI_Comm_size(MPI_COMM_WORLD, &prcnt);

    // receive adjancy matrix size
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int (*arr)[n] = malloc(sizeof(int[n][n]));

    int start_index = ((pridx - 1) * n) / (prcnt - 1);
    int finish_index = (pridx * n) / (prcnt - 1);

    // printf("process %d, min=%d max=%d\n", pridx, start_index, finish_index);

    // receive adjancy matrix
    MPI_Bcast(arr, (n * n), MPI_INT, 0, MPI_COMM_WORLD);

    // run dijkstra in multiple source node
    for(i = start_index; i < finish_index; i++){
        // calculate maximun minimum path from source node
        int current_max = bfs(i, n, arr);
        if (current_max > max)
            max = current_max;
    }

    // send result to process 0
    MPI_Send(&max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    free(arr);
}

int bfs(int source, int n, int arr[][n]) {
    int i, j, k;
    int max = 0;
    int distance[n];
    int flag[n];
    int queue[n];

    // initial max value in shortest path array
    for(i = 0; i < n; i++) {
        distance[i] = 0;
        flag[i] = 0;
    }

    i = 0;
    j = 1;
    distance[source] = 0;
    flag[source] = 1;
    queue[i] = source;

    while (i < j){
        int current = queue[i];
        for(k = 0; k < n; k++) {
            if ((arr[current][k] != n + 1) && (flag[k] == 0)){
                flag[k] = 1;
                distance[k] = distance[current] + 1;
                queue[j] = k;
                j++;
            }
        }
        i++;
    }

    // find maximum shortest path
    for(i = 0; i < n; i++) {
        if(distance[i] > max) 
            max = distance[i];
    }

    return max;
}