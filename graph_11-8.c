#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// 무작위 0, 1 그래프를 파일로 저장하는 함수 (매개변수: nVtx, nEdge)
void random_graph(int nVtx, int nEdge) {
    FILE* fp = fopen("random_graph.txt", "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d %d\n", nVtx, nEdge);

    // 인접 행렬 생성 및 0으로 초기화
    int** adj = (int**)calloc(nVtx, sizeof(int*));
    for (int i = 0; i < nVtx; i++)
        adj[i] = (int*)calloc(nVtx, sizeof(int));

    int cnt = 0;
    while (cnt < nEdge) {
        int u = rand() % nVtx;
        int v = rand() % nVtx;
        if (u == v || adj[u][v]) continue;
        adj[u][v] = adj[v][u] = 1;
        cnt++;
    }

    // 파일에 인접행렬 저장
    for (int i = 0; i < nVtx; i++) {
        for (int j = 0; j < nVtx; j++) {
            fprintf(fp, "%d ", adj[i][j]);
        }
        fprintf(fp, "\n");
    }

    for (int i = 0; i < nVtx; i++)
        free(adj[i]);
    free(adj);

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
    int nEdge;
    fscanf(fp, "%d %d", &vsize, &nEdge);
    // 인접 행렬 읽기
    for (int i = 0; i < vsize; i++)
        for (int j = 0; j < vsize; j++)
            fscanf(fp, "%d", &adj[i][j]);
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
    printf("(11.1-2) 연결된 성분 개수");
    printf("그래프의 연결 성분 개수: %d\n", nComp);

    return 0;
} //(11.1-2)