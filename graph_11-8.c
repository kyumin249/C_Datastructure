#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// 무작위 가중치 완전 그래프 생성 함수
void generate_weighted_complete_graph(const char* filename, int nVtx, int minW, int maxW) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d\n", nVtx);
    for (int i = 0; i < nVtx; i++) {
        fprintf(fp, "%c ", 'A' + i);
        for (int j = 0; j < nVtx; j++) {
            if (i == j)
                fprintf(fp, "0 ");
            else
                fprintf(fp, "%d ", minW + rand() % (maxW - minW + 1));
        }
        fprintf(fp, "\n");
    }
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
    fscanf(fp, "%d", &vsize);
    char name[16];
    for (int i = 0; i < vsize; i++) {
        fscanf(fp, "%s", name);
        for (int j = 0; j < vsize; j++) {
            fscanf(fp, "%d", &adj[i][j]);
        }
    }
    fclose(fp);
}

void dfs(int v) {
    visited[v] = 1;
    for (int w = 0; w < vsize; w++) {
        // 0이 아닌 가중치가 있으면 연결된 것으로 간주
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
    int nVtx = 8; // 정점 수
    int minW = 1, maxW = 20; // 가중치 범위
    const char* filename = "random_graph.txt";

    // 무작위 완전 가중치 그래프 생성
    generate_weighted_complete_graph(filename, nVtx, minW, maxW);

    // 그래프 파일 읽기
    load_graph(filename);

    // 연결 성분 개수 탐색
    int nComp = count_connected_components();
    printf("그래프의 연결 성분 개수: %d\n", nComp);

    return 0;
}