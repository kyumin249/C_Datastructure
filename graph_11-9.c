#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

int adj[MAX_VTXS][MAX_VTXS]; // ���� �������

void save_adj_matrix_to_file(int nVtx) {
    FILE* fp = fopen("adj_matrix.txt", "w");
    if (!fp) {
        printf("adj_matrix.txt ������ �� �� �����ϴ�.\n");
        return;
    }
    for (int i = 0; i < nVtx; i++) {
        for (int j = 0; j < nVtx; j++) {
            fprintf(fp, "%d ", adj[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("adj_matrix.txt ������ �����Ǿ����ϴ�.\n");
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

    printf("\n���� ���� ����: %d\n", compID);
    for (int i = 0; i < nVtx; i++) {
        printf("%c=%d ", 'A' + i, component[i]);
    }
    printf("\n");
}

void generate_random_adj_matrix(int nVtx, int nEdge) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < nVtx; i++)
        for (int j = 0; j < nVtx; j++)
            adj[i][j] = 0;

    int count = 0;
    while (count < nEdge) {
        int u = rand() % nVtx;
        int v = rand() % nVtx;
        if (u == v || adj[u][v]) continue;
        adj[u][v] = adj[v][u] = 1; // ������ �׷���
        count++;
    }
}

int main() {
    int nVtx = 8;
    int nEdge = 12;

    generate_random_adj_matrix(nVtx, nEdge);
    save_adj_matrix_to_file(nVtx);
    count_connected_components(nVtx);

    return 0;
}
//(11.1-3)
