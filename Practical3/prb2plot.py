import matplotlib.pyplot as plt

# Threads used in the experiment
threads = [1, 2, 4, 8]

# Replace with actual cleaned timings
execution_times = {
    250: [0.001, 0.001, 0.001, 0.001],
    500: [0.001, 0.001, 0.001, 0.001],
    750: [0.003, 0.002, 0.002, 0.001],
    1000: [0.005, 0.004, 0.002, 0.002],
    2000: [0.020, 0.018, 0.008, 0.008]
}

plt.figure(figsize=(10, 6))

# Plot speedup for each matrix size
for size, times in execution_times.items():
    speedup = [times[0] / t if t != 0 else 0 for t in times]
    plt.plot(threads, speedup, marker='o', label=f'{size}x{size}')

plt.title('Speedup vs Number of Threads for Matrix Addition')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.xticks(threads)
plt.yticks(range(0, 9))
plt.grid(True)
plt.legend(title='Matrix Size')
plt.tight_layout()
plt.show()
