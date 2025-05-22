#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

int adj[MAX_VTXS][MAX_VTXS]; // 전역 인접행렬

void save_adj_matrix_to_file(int nVtx) {
    FILE* fp = fopen("adj_matrix.txt", "w");
    if (!fp) {
        printf("adj_matrix.txt 파일을 열 수 없습니다.\n");
        return;
    }
    for (int i = 0; i < nVtx; i++) {
        for (int j = 0; j < nVtx; j++) {
            fprintf(fp, "%d ", adj[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void count_connected_components(int nVtx) {
    int visited[MAX_VTXS] = {0};
    int component[MAX_VTXS] = {0};
    int compID = 0;

    for (int i = 0; i < nVtx; i++) {
        if (!visited[i]) {
            compID++;
            int stack[MAX_VTXS], top = -1;
            stack[++top] = i;
            while (top >= 0) {
                int cur = stack[top--];
                if (visited[cur]) continue;
                visited[cur] = 1;
                component[cur] = compID;
                for (int j = 0; j < nVtx; j++) {
                    if (adj[cur][j] && !visited[j]) {
                        stack[++top] = j;
                    }
                }
            }
        }
    }

    printf("\n연결 성분 개수: %d\n", compID);
    for (int i = 0; i < nVtx; i++) {
        printf("%c=%d ", 'A' + i, component[i]);
    }
    printf("\n");
}

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
    for (int i = 0; i < nVtx; i++) {
        edge[i] = (int*)calloc(nVtx, sizeof(int));
        for (int j = 0; j < nVtx; j++)
            adj[i][j] = 0;  // 인접행렬 초기화
    }

    int cnt = 0;
    while (cnt < nEdge) {
        int u = rand() % nVtx;
        int v = rand() % nVtx;
        if (u == v || edge[u][v]) continue;
        int w = minW + rand() % (maxW - minW + 1);
        fprintf(fp, "%c %c %d\n", 'A' + u, 'A' + v, w);
        edge[u][v] = edge[v][u] = 1;
        adj[u][v] = adj[v][u] = 1;
        cnt++;
    }

    for (int i = 0; i < nVtx; i++)
        free(edge[i]);
    free(edge);
    fclose(fp);
}

void random_connected_graph(int nVtx) {
    int minW = 1, maxW = 20;
    int nEdge = nVtx - 1;
    FILE* fp = fopen("random_connected_graph.txt", "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d %d\n", nVtx, nEdge);

    int** edge = (int**)calloc(nVtx, sizeof(int*));
    for (int i = 0; i < nVtx; i++) {
        edge[i] = (int*)calloc(nVtx, sizeof(int));
    }

    for (int i = 1; i < nVtx; i++) {
        int u = i;
        int v = rand() % i;
        int w = minW + rand() % (maxW - minW + 1);
        fprintf(fp, "%c %c %d\n", 'A' + u, 'A' + v, w);
        edge[u][v] = edge[v][u] = 1;
    }

    for (int i = 0; i < nVtx; i++)
        free(edge[i]);
    free(edge);
    fclose(fp);
}

int main() {
    int nVtx = 8;
    int nEdge = 12;

    random_graph(nVtx, nEdge);
    printf("random_graph.txt 파일이 생성되었습니다.\n");

    save_adj_matrix_to_file(nVtx);
    printf("adj_matrix.txt 파일이 생성되었습니다.\n");

    count_connected_components(nVtx);

    random_connected_graph(nVtx);
    printf("random_connected_graph.txt 파일이 생성되었습니다.\n");

    return 0;
}//(11.1-3)
