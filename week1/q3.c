#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, result = 0;
    int a = 5;
    int b  = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
    printf("The addition of %d and %d is %d\n",a,b, a+b);
    } else if (rank == 1) {
        printf("The subtraction of %d and %d is %d\n",a,b, a-b);
    } else if (rank == 2) {
        printf("The multiplication of %d and %d is %d\n",a,b, (a*b));
    } else {
        printf("The division of %d and %d is %d\n",a,b, (a/b));
    }
    MPI_Finalize();
    return 0;
}