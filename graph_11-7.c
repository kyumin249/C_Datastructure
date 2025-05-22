#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// ������ �׷��� ������ �о�� ���簢��(�������)���� ����ϴ� �Լ�
void print_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("�׷��� ������ �� �� �����ϴ�.\n");
        return;
    }
    int nVtx, nEdge;
    if (fscanf(fp, "%d %d", &nVtx, &nEdge) != 2) {
        fclose(fp);
        return;
    }
    printf("���� ��: %d, ���� ��: %d\n", nVtx, nEdge);
    printf("(11.1-1)�������(0, 1 �׷���):\n");
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
    int nVtx = 6;   // ���� ��
    int nEdge = 10; // ���� ��
    random_graph(nVtx, nEdge);
    printf("random_graph.txt ������ �����Ǿ����ϴ�.\n");
    print_graph("random_graph.txt");
    return 0;
}