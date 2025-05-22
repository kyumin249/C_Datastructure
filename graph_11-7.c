#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ������ ����ġ �׷����� ���Ϸ� �����ϴ� �Լ� (�Ű�����: nVtx, nEdge)
void random_graph(int nVtx, int nEdge) {
    int minW = 1, maxW = 20;
    FILE* fp = fopen("random_graph.txt", "w");
    if (!fp) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d %d\n", nVtx, nEdge);

    // ���� �ߺ� ������ �迭
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

// ������ �׷��� ������ �о�� ����ϴ� �Լ�
void print_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("�׷��� ������ �� �� �����ϴ�.\n");
        return;
    }
    int nVtx, nEdge;
    printf("������ �׷���:\n");
    if (fscanf(fp, "%d %d", &nVtx, &nEdge) == 2) {
        printf("���� ��: %d, ���� ��: %d\n", nVtx, nEdge);
        char u, v;
        int w;
        while (fscanf(fp, " %c %c %d", &u, &v, &w) == 3) {
            printf("%c - %c : %d\n", u, v, w);
        }
    }
    fclose(fp);
}

int main() {
    int nVtx = 6;   // ���� ��
    int nEdge = 10; // ���� ��
    random_graph(nVtx, nEdge);
    printf("random_graph.txt ������ �����Ǿ����ϴ�.\n");
    print_graph("random_graph.txt");
    return 0;
}