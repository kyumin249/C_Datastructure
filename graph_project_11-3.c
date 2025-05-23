#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 26

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
char vdata[MAX_VERTICES];
int vsize;

// �׷��� �ʱ�ȭ
void init_graph(int n) {
    vsize = n;
    for (int i = 0; i < vsize; i++) {
        vdata[i] = 'A' + i;
        for (int j = 0; j < vsize; j++) {
            adj[i][j] = 0;
        }
    }
}

// ���� �׷��� ���� (������ ���� �߰�)
void generate_connected_graph(float edge_density) {
    // ���� ������ ����ǵ��� n-1���� ���� �߰�
    for (int i = 1; i < vsize; i++) {
        int j = rand() % i;  // i ������ �ƹ� ������ ����
        adj[i][j] = adj[j][i] = 1;
    }

    // �߰� ���� �������� �ֱ�
    for (int i = 0; i < vsize; i++) {
        for (int j = i + 1; j < vsize; j++) {
            if (adj[i][j] == 0 && ((float)rand() / RAND_MAX) < edge_density) {
                adj[i][j] = adj[j][i] = 1;
            }
        }
    }
}

// DFS �Լ�
void DFS(int v) {
    visited[v] = 1;
    printf("%c ", vdata[v]);

    for (int i = 0; i < vsize; i++) {
        if (adj[v][i] && !visited[i]) {
            DFS(i);
        }
    }
}

// �׷��� ���
void print_graph() {
    printf("\n[���� ��� ���]\n");
    for (int i = 0; i < vsize; i++) {
        for (int j = 0; j < vsize; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int n;
    float density = 0.3f;  // ���� �е� (0.0 ~ 1.0)

    printf("���� �� �Է� (�ִ� %d): ", MAX_VERTICES);
    scanf("%d", &n);

    if (n > MAX_VERTICES || n < 2) {
        printf("2 �̻� %d ������ ���� �Է��ϼ���.\n", MAX_VERTICES);
        return 1;
    }

    init_graph(n);
    generate_connected_graph(density);

    print_graph();

    printf("\nDFS �湮 ����: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(0);  // A���� ����

    printf("\n");

    return 0;
}

