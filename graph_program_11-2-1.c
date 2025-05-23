#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 20

int adj[MAX_VERTICES][MAX_VERTICES];
int vsize = 0;
char vdata[MAX_VERTICES];

int timeCounter;
int disc[MAX_VERTICES], low[MAX_VERTICES], visited[MAX_VERTICES];

void init_graph(int size) {
    vsize = size;
    for (int i = 0; i < vsize; i++) {
        vdata[i] = 'A' + i;  // 이름 부여 (A, B, C, ...)
        for (int j = 0; j < vsize; j++) {
            adj[i][j] = 0;
        }
    }
}

void generate_random_binary_matrix(float edge_probability) {
    for (int i = 0; i < vsize; i++) {
        for (int j = i + 1; j < vsize; j++) {
            if (((float)rand() / RAND_MAX) < edge_probability) {
                adj[i][j] = adj[j][i] = 1;  // 무방향
            }
        }
    }
}

void print_graph(char* msg) {
    printf("%s%d\n", msg, vsize);
    for (int i = 0; i < vsize; i++) {
        printf("%c ", vdata[i]);
        for (int j = 0; j < vsize; j++) {
            if (adj[i][j]) {
                printf(" %c", vdata[j]);
            }
        }
        printf("\n");
    }

    printf("\n[인접 행렬 출력]\n");
    for (int i = 0; i < vsize; i++) {
        for (int j = 0; j < vsize; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

void DFSBridge(int u, int parent) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < vsize; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                DFSBridge(v, u);
                if (low[v] > disc[u]) {
                    printf("Bridge found: %c - %c\n", vdata[u], vdata[v]);
                }
                if (low[u] > low[v]) low[u] = low[v];
            } else if (v != parent) {
                if (low[u] > disc[v]) low[u] = disc[v];
            }
        }
    }
}

int findBridge() {
    memset(visited, 0, sizeof(visited));
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    timeCounter = 0;

    for (int i = 0; i < vsize; i++) {
        if (!visited[i]) {
            DFSBridge(i, -1);
        }
    }

    return 0;
}

int main() {
    srand((unsigned int)time(NULL));

    int size = 6;              // 정점 수
    float density = 0.4f;      // 간선이 있을 확률

    init_graph(size);
    generate_random_binary_matrix(density);

    print_graph("0과 1로 구성된 무작위 인접 행렬 그래프\n");

    printf("\n--- 브리지 탐색 결과 ---\n");
    findBridge();

    return 0;
}
