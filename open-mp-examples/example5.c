#include <stdio.h>
#include <omp.h>

int main(void) {
    // variable a will be private in each process
    int a = 1;

    // if a initilized before this line then variable a will be initialize with default value 
    #pragma omp parallel num_threads(4) private(a)
    printf("Thread: %d, a = %d\n", omp_get_thread_num(), a++);

    return 0;
}