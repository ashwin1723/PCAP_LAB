#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, number, result;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Root process (rank 0) sends a value to each slave
        for (int i = 1; i < size; i++) {
            number = i * 2;  // Example value to send
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Root sent number %d to process %d\n", number, i);
        }
    } else {
        // Slave processes receive the number
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (rank % 2 == 0) {
            result = number * number;  // Even rank computes the square
            printf("Process %d received %d, computed square: %d\n", rank, number, result);
        } else {
            result = number * number * number;  // Odd rank computes the cube
            printf("Process %d received %d, computed cube: %d\n", rank, number, result);
        }
    }

    MPI_Finalize();
    return 0;
}
