#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

int main() {
    int n = 15;
    vector<long long> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;

    double start = omp_get_wtime();

    // Sequential computation
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    double mid = omp_get_wtime();

    cout << "Fibonacci Computation Time (Sequential): " << (mid - start) << "s\n";

    // Parallel print with synchronization
    #pragma omp parallel for
    for (int i = 0; i <= n; i++) {
        #pragma omp critical
        {
            cout << "F(" << i << ") = " << fib[i] << endl;
        }
    }

    double end = omp_get_wtime();

    cout << "Parallel Print Time: " << (end - mid) << "s\n";

    return 0;
}