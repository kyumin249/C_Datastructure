#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 100

typedef struct GNode {
    int id;
    struct GNode* link;
} GNode;

int vsize = 0;
char vdata[MAX_VERTICES];
GNode* adj[MAX_VERTICES];

int timeCounter;
int disc[MAX_VERTICES], low[MAX_VERTICES], visited[MAX_VERTICES];

void init_graph() {
    vsize = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        adj[i] = NULL;
}

void insert_vertex(char name) {
    vdata[vsize++] = name;
}

void insert_edge(int u, int v) {
    GNode* node = (GNode*)malloc(sizeof(GNode));
    node->id = v;
    node->link = adj[u];
    adj[u] = node;

    GNode* node2 = (GNode*)malloc(sizeof(GNode));
    node2->id = u;
    node2->link = adj[v];
    adj[v] = node2;
}

void print_graph(char* msg) {
    printf("%s%d\n", msg, vsize);
    for (int i = 0; i < vsize; i++) {
        printf("%c ", vdata[i]);
        for (GNode* v = adj[i]; v != NULL; v = v->link)
            printf(" %c", vdata[v->id]);
        printf("\n");
    }
}

void DFSBridge(int u, int parent) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (GNode* p = adj[u]; p != NULL; p = p->link) {
        int v = p->id;
        if (!visited[v]) {
            DFSBridge(v, u);
            if (low[v] > disc[u])
                printf("Bridge found: %c - %c\n", vdata[u], vdata[v]);
            if (low[u] > low[v])
                low[u] = low[v];
        } else if (v != parent) {
            if (low[u] > disc[v])
                low[u] = disc[v];
        }
    }
}

int findBridge() {
    memset(visited, 0, sizeof(visited));
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    timeCounter = 0;

    for (int i = 0; i < vsize; i++) {
        if (!visited[i])
            DFSBridge(i, -1);
    }
    return 0;
}

void load_graph(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�: %s\n", filename);
        return;
    }

    init_graph();
    int n, val;
    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++)
        insert_vertex('A' + i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &val);
            if (val == 1 && j > i)
                insert_edge(i, j);
        }
    }

    fclose(fp);
}

void generate_random_connected_graph(const char* filename, int n, int maxEdges) {
    int matrix[MAX_VERTICES][MAX_VERTICES] = { 0 };
    srand((unsigned int)time(NULL));

    // ������ ���� �⺻ Ʈ�� ���� ����
    for (int i = 1; i < n; i++) {
        int j = rand() % i;
        matrix[i][j] = matrix[j][i] = 1;
    }

    int added = n - 1;
    while (added < maxEdges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && matrix[u][v] == 0) {
            matrix[u][v] = matrix[v][u] = 1;
            added++;
        }
    }

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("���� ���� ����: %s\n", filename);
        return;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(fp, "%d ", matrix[i][j]);
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("������ �׷����� �����Ǿ����ϴ�: %s\n", filename);
}

int main() {
    const char* filename = "graph.txt";
    int vertex_count = 6;
    int max_edges = 10;

    // �׷��� �ڵ� ����
    generate_random_connected_graph(filename, vertex_count, max_edges);

    // ���Ϸκ��� �׷��� �ҷ�����
    load_graph(filename);
    print_graph("�׷���(��������Ʈ)\n");

    printf("\n--- �긮�� Ž�� ��� ---\n");
    findBridge();

    return 0;
}



