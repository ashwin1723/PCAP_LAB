#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Root process initializes the value
        value = 10;  // Initial value
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Root process sent %d to process 1\n", value);

        // Receive the final value from the last process
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Root process received final value: %d\n", value);
    } else {
        // Other processes (rank 1 to size-2) receive, increment and send to the next process
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        value += 1;  // Increment the value
        printf("Process %d received %d, incremented it to %d\n", rank, value - 1, value);

        if (rank != size - 1) {
            // Send the incremented value to the next process
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Last process sends the value back to the root process
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
