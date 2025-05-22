#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// 생성된 그래프 파일을 읽어와 직사각형(인접행렬)으로 출력하는 함수
void print_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("그래프 파일을 열 수 없습니다.\n");
        return;
    }
    int nVtx, nEdge;
    if (fscanf(fp, "%d %d", &nVtx, &nEdge) != 2) {
        fclose(fp);
        return;
    }
    printf("정점 수: %d, 간선 수: %d\n", nVtx, nEdge);
    printf("(11.1-1)인접행렬(0, 1 그래프):\n");
    int val;
    for (int i = 0; i < nVtx; i++) {
        for (int j = 0; j < nVtx; j++) {
            fscanf(fp, "%d", &val);
            printf("%d ", val);
        }
        printf("\n");
    }
    fclose(fp);
}

int main() {
    int nVtx = 6;   // 정점 수
    int nEdge = 10; // 간선 수
    random_graph(nVtx, nEdge);
    printf("random_graph.txt 파일이 생성되었습니다.\n");
    print_graph("random_graph.txt");
    return 0;
}