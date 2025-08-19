#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 1000000

int compareAsc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int compareDesc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

int main()
{
    int *A = (int *)malloc(SIZE * sizeof(int));
    int *B = (int *)malloc(SIZE * sizeof(int));

    // Seed for random number generation
    srand(time(NULL));

    // Generate random values for A and B
    for (int i = 0; i < SIZE; i++)
    {
        A[i] = rand() % 1000;
        B[i] = rand() % 1000;
    }

    // Sort arrays
    qsort(A, SIZE, sizeof(int), compareAsc);
    qsort(B, SIZE, sizeof(int), compareDesc);

    // Serial Dot Product
    double start_serial = omp_get_wtime();
    long long serial_result = 0;
    for (int i = 0; i < SIZE; i++)
    {
        serial_result += (long long)A[i] * B[i];
    }
    double end_serial = omp_get_wtime();

    // Parallel Dot Product
    double start_parallel = omp_get_wtime();
    long long parallel_result = 0;

#pragma omp parallel for reduction(+ : parallel_result) schedule(static)
    for (int i = 0; i < SIZE; i++)
    {
        parallel_result += (long long)A[i] * B[i];
    }
    double end_parallel = omp_get_wtime();

    // Output results
    printf("Serial Result          : %lld\n", serial_result);
    printf("Serial Time            : %.6f seconds\n", end_serial - start_serial);

    printf("Parallel Result        : %lld\n", parallel_result);
    printf("Parallel Time          : %.6f seconds\n", end_parallel - start_parallel);

    printf("Speedup (Serial/Parallel): %.2f\n",
           (end_serial - start_serial) / (end_parallel - start_parallel));

    free(A);
    free(B);
    return 0;
}
