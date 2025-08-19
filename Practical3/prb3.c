#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200
#define SCALAR 10

void vector_scalar_add_static(int chunk)
{
    int A[SIZE], B[SIZE];
    double start, end;

    for (int i = 0; i < SIZE; i++)
        A[i] = i;

    start = omp_get_wtime();

#pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < SIZE; i++)
        B[i] = A[i] + SCALAR;

    end = omp_get_wtime();

    printf("[STATIC] Chunk: %d | Time: %.8f sec\n", chunk, end - start);
}

void vector_scalar_add_dynamic(int chunk)
{
    int A[SIZE], B[SIZE];
    double start, end;

    for (int i = 0; i < SIZE; i++)
        A[i] = i;

    start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < SIZE; i++)
        B[i] = A[i] + SCALAR;

    end = omp_get_wtime();

    printf("[DYNAMIC] Chunk: %d | Time: %.8f sec\n", chunk, end - start);
}

void demonstrate_nowait_clause()
{
    int A[SIZE], B[SIZE], C[SIZE];
    double start, end;

    for (int i = 0; i < SIZE; i++)
        A[i] = i;

    start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp for nowait
        for (int i = 0; i < SIZE; i++)
            B[i] = A[i] + SCALAR;

#pragma omp for
        for (int i = 0; i < SIZE; i++)
            C[i] = A[i] * SCALAR;
    }

    end = omp_get_wtime();

    printf("[NOWAIT] Parallel Sections Time: %.8f sec\n", end - start);
}

int main()
{
    printf("---- STATIC SCHEDULE ----\n");
    vector_scalar_add_static(5);
    vector_scalar_add_static(10);
    vector_scalar_add_static(25);
    vector_scalar_add_static(50);

    printf("\n---- DYNAMIC SCHEDULE ----\n");
    vector_scalar_add_dynamic(5);
    vector_scalar_add_dynamic(10);
    vector_scalar_add_dynamic(25);
    vector_scalar_add_dynamic(50);

    printf("\n---- NOWAIT CLAUSE ----\n");
    demonstrate_nowait_clause();

    return 0;
}
