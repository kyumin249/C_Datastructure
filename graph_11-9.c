#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// 연결된 완전 가중치 그래프 생성 함수
void generate_connected_weighted_complete_graph(const char* filename, int nVtx, int minW, int maxW) {
    int adj[MAX_VTXS][MAX_VTXS] = {0};
    int used[MAX_VTXS] = {0};
    int i, j;

    srand((unsigned int)time(NULL));

    // 1. MST(임의의 트리) 간선 추가 (연결 보장)
    used[0] = 1;
    for (i = 1; i < nVtx; i++) {
        int u = rand() % i; // 이미 트리에 포함된 정점 중 하나
        int w = minW + rand() % (maxW - minW + 1);
        adj[i][u] = adj[u][i] = w;
        used[i] = 1;
    }

    // 2. 나머지 간선도 무작위로 추가 (완전 그래프)
    for (i = 0; i < nVtx; i++) {
        for (j = 0; j < nVtx; j++) {
            if (i != j && adj[i][j] == 0) {
                int w = minW + rand() % (maxW - minW + 1);
                adj[i][j] = w;
            }
        }
    }

    // 3. 파일로 저장
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    fprintf(fp, "%d\n", nVtx);
    for (i = 0; i < nVtx; i++) {
        fprintf(fp, "%c ", 'A' + i);
        for (j = 0; j < nVtx; j++) {
            if (i == j)
                fprintf(fp, "0 ");
            else
                fprintf(fp, "%d ", adj[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main() {
    int nVtx = 8; // 정점 수
    int minW = 1, maxW = 20; // 가중치 범위
    generate_connected_weighted_complete_graph("random_connected_graph.txt", nVtx, minW, maxW);
    printf("random_connected_graph.txt 파일이 생성되었습니다.\n");
    return 0;
}