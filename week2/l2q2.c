#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, number;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Master process (rank 0) sends a number to each slave
        for (int i = 1; i < size; i++) {
            number = i * 10;  // Sending a different number to each slave
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master sent number %d to process %d\n", number, i);
        }
    } else {
        // Slave processes receive the number and print it
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received number: %d\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}
