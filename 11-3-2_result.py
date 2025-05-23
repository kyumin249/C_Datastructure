import matplotlib.pyplot as plt

# 데이터 입력
vertex_counts = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
avg_times = [0.00001000, 0.00002900, 0.00005200, 0.00006000, 0.00006300,
             0.00007600, 0.00008800, 0.00012800, 0.00018800, 0.00014300]

# 그래프 그리기
plt.figure(figsize=(8, 5))
plt.plot(vertex_counts, avg_times, marker='o', linestyle='-', color='b', label='평균 실행 시간')

plt.title('정점 개수에 따른 DFS 평균 실행 시간')
plt.xlabel('정점 개수')
plt.ylabel('평균 실행 시간 (초)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
