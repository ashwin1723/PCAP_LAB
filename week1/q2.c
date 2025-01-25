#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("My rank is %d\n", rank);
    if (rank % 2 == 0) {
        printf("Hello\n");
    } else {
        printf("World\n");
    }
    MPI_Finalize();
    return 0;
}