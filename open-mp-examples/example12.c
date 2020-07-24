#include <stdio.h>
#include <omp.h>

int main(void) {
    
    #pragma omp parallel num_threads(4)
    {
        printf("Thread %d at A\n", omp_get_thread_num());

        // if all threads be in this line then can continute
        #pragma omp barrier
        printf("Thread %d at B\n", omp_get_thread_num());
    }

    return 0;
}