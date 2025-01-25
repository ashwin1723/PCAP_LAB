#include <mpi.h>
#include <stdio.h>

// Function to calculate factorial
long long calculateFactorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    
    long long factorial = 1;
    for (int i = 2; i <= n; i++) {
        factorial *= i;
    }
    return factorial;
}

// Function to calculate Fibonacci
long long calculateFibonacci(int n) {
    if (n <= 1)
        return n;
    
    long long a = 0, b = 1, fib;
    for (int i = 2; i <= n; i++) {
        fib = a + b;
        a = b;
        b = fib;
    }
    return b;
}

int main(int argc, char *argv[])
{
    int rank, size;
    
    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    
    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Perform calculations based on rank
    if (rank % 2 == 0) {
        // Even ranked processes calculate factorial
        long long factorial = calculateFactorial(rank);
        printf("Process %d (Even): Factorial of %d = %lld\n", 
               rank, rank, factorial);
    } else {
        // Odd ranked processes calculate Fibonacci
        long long fibonacci = calculateFibonacci(rank);
        printf("Process %d (Odd): Fibonacci of %d = %lld\n", 
               rank, rank, fibonacci);
    }
    
    // Finalize MPI environment
    MPI_Finalize();
    
    return 0;
}
