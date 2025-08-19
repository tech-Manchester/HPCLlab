#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int size, int num_threads)
{
    int **A, **B, **C;
    double start, end;

    // Allocate memory
    A = (int **)malloc(size * sizeof(int *));
    B = (int **)malloc(size * sizeof(int *));
    C = (int **)malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++)
    {
        A[i] = (int *)malloc(size * sizeof(int));
        B[i] = (int *)malloc(size * sizeof(int));
        C[i] = (int *)malloc(size * sizeof(int));
    }

    // Initialize matrices
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }

    omp_set_num_threads(num_threads);
    start = omp_get_wtime();

// Parallel matrix addition
#pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];

    end = omp_get_wtime();

    printf("Matrix Size: %d x %d, Threads: %d, Time: %.6f sec\n", size, size, num_threads, end - start);

    // Free memory
    for (int i = 0; i < size; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main()
{
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};

    for (int s = 0; s < 5; s++)
    {
        for (int t = 0; t < 4; t++)
        {
            matrix_addition(sizes[s], threads[t]);
        }
        printf("--------------------------------------------------\n");
    }
    return 0;
}
