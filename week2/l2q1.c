#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <ctype.h>

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    int rank, size;
    char word[MAX_LEN] = "HelloWorld";
    char recv_word[MAX_LEN];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("This program requires exactly two processes.\n");
        MPI_Finalize();
        return -1;
    }

    if (rank == 0) {
        // Process 0 (Sender) sends the word
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent: %s\n", word);

        // Process 0 receives the modified word back
        MPI_Recv(recv_word, MAX_LEN, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received: %s\n", recv_word);
    } else if (rank == 1) {
        // Process 1 (Receiver) receives the word
        MPI_Recv(recv_word, MAX_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %s\n", recv_word);

        // Toggle each letter in the word
        for (int i = 0; i < strlen(recv_word); i++) {
            if (isupper(recv_word[i])) {
                recv_word[i] = tolower(recv_word[i]);
            } else if (islower(recv_word[i])) {
                recv_word[i] = toupper(recv_word[i]);
            }
        }

        // Send the modified word back
        MPI_Ssend(recv_word, strlen(recv_word) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 sent: %s\n", recv_word);
    }

    MPI_Finalize();
    return 0;
}
