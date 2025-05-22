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

// 인접 행렬 기반 연결 성분 탐색
int adj[MAX_VTXS][MAX_VTXS];
int visited[MAX_VTXS];
int vsize;

void load_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("그래프 파일을 열 수 없습니다.\n");
        exit(1);
    }
    fscanf(fp, "%d %*d", &vsize); // 정점 수만 읽고, 간선 수는 무시
    char u, v;
    int w;
    // 인접 행렬 초기화
    for (int i = 0; i < vsize; i++)
        for (int j = 0; j < vsize; j++)
            adj[i][j] = 0;
    while (fscanf(fp, " %c %c %d", &u, &v, &w) == 3) {
        int i = u - 'A';
        int j = v - 'A';
        adj[i][j] = w;
        adj[j][i] = w;
    }
    fclose(fp);
}

void dfs(int v) {
    visited[v] = 1;
    for (int w = 0; w < vsize; w++) {
        if (adj[v][w] != 0 && !visited[w])
            dfs(w);
    }
}

int count_connected_components() {
    int count = 0;
    for (int i = 0; i < vsize; i++) visited[i] = 0;
    for (int i = 0; i < vsize; i++) {
        if (!visited[i]) {
            dfs(i);
            count++;
        }
    }
    return count;
}

int main() {
    int nVtx = 8;   // 정점 수
    int nEdge = 12; // 간선 수
    random_graph(nVtx, nEdge);

    // 그래프 파일 읽기
    load_graph("random_graph.txt");

    // 연결 성분 개수 탐색
    int nComp = count_connected_components();
    printf("그래프의 연결 성분 개수: %d\n", nComp);

    return 0;
}