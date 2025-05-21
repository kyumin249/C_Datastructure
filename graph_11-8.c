#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VTXS 100

// ������ ����ġ ���� �׷��� ���� �Լ�
void generate_weighted_complete_graph(const char* filename, int nVtx, int minW, int maxW) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("������ �� �� �����ϴ�.\n");
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
        // 0�� �ƴ� ����ġ�� ������ ����� ������ ����
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
    int nVtx = 8; // ���� ��
    int minW = 1, maxW = 20; // ����ġ ����
    const char* filename = "random_graph.txt";

    // ������ ���� ����ġ �׷��� ����
    generate_weighted_complete_graph(filename, nVtx, minW, maxW);

    // �׷��� ���� �б�
    load_graph(filename);

    // ���� ���� ���� Ž��
    int nComp = count_connected_components();
    printf("�׷����� ���� ���� ����: %d\n", nComp);

    return 0;
}