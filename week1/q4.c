#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    int rank, size;
    char str[] = "HELLO";
    int len = sizeof(str) /sizeof(str[0])-1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank < len) {
        str[rank] = tolower(str[rank]);
    }
    printf("The string at rank %d is %s\n", rank, &str);
    MPI_Finalize();
    return 0;
}

