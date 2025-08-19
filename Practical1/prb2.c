#include <stdio.h>
#include <omp.h>

int main()
{
    int num_threads;

    // Asking user to input number of threads
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    // Sequential execution
    printf("\nSequential Hello, World:\n");
    for (int i = 0; i < num_threads; i++)
    {
        printf("Hello, World\n");
    }

    // Parallel execution
    printf("\nParallel Hello, World:\n");
    omp_set_num_threads(num_threads); // Set number of threads

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, World from thread %d\n", thread_id);
    }

    return 0;
}
