#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// 무작위 가중치 그래프를 파일로 저장하는 함수 (매개변수: nVtx, nEdge)
void random_graph(int nVtx, int nEdge) {
    int minW = 1, maxW = 20;
    FILE* fp = fopen("random_graph.txt", "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d %d\n", nVtx, nEdge);

    // 간선 중복 방지용 배열
    int** edge = (int**)calloc(nVtx, sizeof(int*));
    for (int i = 0; i < nVtx; i++)
        edge[i] = (int*)calloc(nVtx, sizeof(int));

    int cnt = 0;
    while (cnt < nEdge) {
        int u = rand() % nVtx;
        int v = rand() % nVtx;
        if (u == v || edge[u][v]) continue;
        int w = minW + rand() % (maxW - minW + 1);
        fprintf(fp, "%c %c %d\n", 'A' + u, 'A' + v, w);
        edge[u][v] = edge[v][u] = 1;
        cnt++;
    }

    for (int i = 0; i < nVtx; i++)
        free(edge[i]);
    free(edge);

    fclose(fp);
}

int main() {
    int nVtx = 8;   // 정점 수
    int nEdge = 12; // 간선 수
    random_graph(nVtx, nEdge);
    printf("random_graph.txt 파일이 생성되었습니다.\n");
    return 0;
}