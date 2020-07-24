#include <stdio.h>

int main(void) {
    // print 'Hello World!' #number_of_processors times.

    #pragma omp parallel
    printf("Hello world!\n");
    return 0;
}