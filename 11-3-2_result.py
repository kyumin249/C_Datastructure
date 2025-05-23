# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

# Data input
vertex_counts = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
avg_times = [0.00000700, 0.00002800, 0.00004400, 0.00005100, 0.00006900,
             0.00007700, 0.00008200, 0.00010800, 0.00011500, 0.00012000]

# Draw the graph
plt.figure(figsize=(8, 5))
plt.plot(vertex_counts, avg_times, marker='o', linestyle='-', color='b', label='Average Execution Time')

plt.title('Average DFS Execution Time by Number of Vertices')
plt.xlabel('Number of Vertices')
plt.ylabel('Average Execution Time (seconds)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
