#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size, power;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("My rank is %d\n", rank);
    power = pow(2, rank);
    printf("The pow(2, %d) is %d\n", rank, power);
    MPI_Finalize();
    return 0;
}