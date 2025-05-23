#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 26

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
char vdata[MAX_VERTICES];
int vsize;

// 그래프 초기화
void init_graph(int n) {
    vsize = n;
    for (int i = 0; i < vsize; i++) {
        vdata[i] = 'A' + i;
        for (int j = 0; j < vsize; j++) {
            adj[i][j] = 0;
        }
    }
}

// 연결 그래프 생성 (무작위 간선 추가)
void generate_connected_graph(float edge_density) {
    // 먼저 무조건 연결되도록 n-1개의 간선 추가
    for (int i = 1; i < vsize; i++) {
        int j = rand() % i;  // i 이전의 아무 정점과 연결
        adj[i][j] = adj[j][i] = 1;
    }

    // 추가 간선 무작위로 넣기
    for (int i = 0; i < vsize; i++) {
        for (int j = i + 1; j < vsize; j++) {
            if (adj[i][j] == 0 && ((float)rand() / RAND_MAX) < edge_density) {
                adj[i][j] = adj[j][i] = 1;
            }
        }
    }
}

// DFS 함수
void DFS(int v) {
    visited[v] = 1;
    printf("%c ", vdata[v]);

    for (int i = 0; i < vsize; i++) {
        if (adj[v][i] && !visited[i]) {
            DFS(i);
        }
    }
}

// 그래프 출력
void print_graph() {
    printf("\n[인접 행렬 출력]\n");
    for (int i = 0; i < vsize; i++) {
        for (int j = 0; j < vsize; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int n;
    float density = 0.3f;  // 간선 밀도 (0.0 ~ 1.0)

    printf("정점 수 입력 (최대 %d): ", MAX_VERTICES);
    scanf("%d", &n);

    if (n > MAX_VERTICES || n < 2) {
        printf("2 이상 %d 이하의 값을 입력하세요.\n", MAX_VERTICES);
        return 1;
    }

    init_graph(n);
    generate_connected_graph(density);

    print_graph();

    printf("\nDFS 방문 순서: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(0);  // A부터 시작

    printf("\n");

    return 0;
}

