#include <stdio.h>
#include <omp.h>

int main()
{
    int num_cores = omp_get_num_procs();
    printf("Number of available processors: %d\n", num_cores);
    return 0;
}
