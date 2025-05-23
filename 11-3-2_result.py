# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

# 데이터 입력
vertex_counts = [
     5,  10,  15,  20,  25,  30,  35,  40,  45,  50,
    55,  60,  65,  70,  75,  80,  85,  90,  95, 100,
   105, 110, 115, 120, 125, 130, 135, 140, 145, 150,
   155, 160, 165, 170, 175, 180, 185, 190, 195, 200,
   205, 210, 215, 220, 225, 230, 235, 240, 245, 250, 255
]
total_times = [
    0.002, 0.005, 0.003, 0.003, 0.002, 0.007, 0.006, 0.005, 0.011, 0.011,
    0.005, 0.008, 0.007, 0.008, 0.002, 0.012, 0.006, 0.015, 0.001, 0.017,
    0.016, 0.000, 0.023, 0.014, 0.014, 0.003, 0.013, 0.015, 0.025, 0.017,
    0.018, 0.017, 0.013, 0.025, 0.019, 0.019, 0.012, 0.039, 0.027, 0.025,
    0.024, 0.020, 0.027, 0.022, 0.030, 0.024, 0.024, 0.024, 0.028, 0.028, 0.031
]

plt.figure(figsize=(10, 6))
plt.plot(vertex_counts, total_times, marker='o', linestyle='-', color='b', label='Total Execution Time (1000 runs)')

plt.title('Total DFS Execution Time vs Number of Vertices')
plt.xlabel('Number of Vertices')
plt.ylabel('Total Execution Time (seconds)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
