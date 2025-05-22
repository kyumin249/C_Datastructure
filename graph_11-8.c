#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// ������ 0, 1 �׷����� ���Ϸ� �����ϴ� �Լ� (�Ű�����: nVtx, nEdge)
void random_graph(int nVtx, int nEdge) {
    FILE* fp = fopen("random_graph.txt", "w");
    if (!fp) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d %d\n", nVtx, nEdge);

    // ���� ��� ���� �� 0���� �ʱ�ȭ
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

    // ���Ͽ� ������� ����
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

// ���� ��� ��� ���� ���� Ž��
int adj[MAX_VTXS][MAX_VTXS];
int visited[MAX_VTXS];
int vsize;

void load_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("�׷��� ������ �� �� �����ϴ�.\n");
        exit(1);
    }
    int nEdge;
    fscanf(fp, "%d %d", &vsize, &nEdge);
    // ���� ��� �б�
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
    int nVtx = 8;   // ���� ��
    int nEdge = 12; // ���� ��
    random_graph(nVtx, nEdge);

    // �׷��� ���� �б�
    load_graph("random_graph.txt");

    // ���� ���� ���� Ž��
    int nComp = count_connected_components();
    printf("(11.1-2) ����� ���� ����");
    printf("�׷����� ���� ���� ����: %d\n", nComp);

    return 0;
} //(11.1-2)