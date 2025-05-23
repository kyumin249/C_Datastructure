#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    for (int i = 0; i < MAX_VERTICES; i++) {
        adj[i] = NULL;
    }
}

void insert_vertex(char name) {
    vdata[vsize++] = name;
}

void insert_edge(int u, int v) {
    GNode* node = (GNode*)malloc(sizeof(GNode));
    node->id = v;
    node->link = adj[u];
    adj[u] = node;
}

void DFSBridge(int u, int parent) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (GNode* p = adj[u]; p != NULL; p = p->link) {
        int v = p->id;
        if (!visited[v]) {
            DFSBridge(v, u);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (low[v] > disc[u]) {
                printf("Bridge found: %c - %c\n", vdata[u], vdata[v]);
            }
        } else if (v != parent) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}
void print_graph(char* msg) {
    printf("%s%d\n", msg, vsize);
    for (int i = 0; i < vsize; i++) {
        printf("%c ", vdata[i]);
        for (GNode* v = adj[i]; v != NULL; v = v->link) {
            printf(" %c", vdata[v->id]);
        }
        printf("\n");
    }
}

void load_graph(char* filename) {
    int i, j, val, n;
    char str[80];
    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        init_graph();
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for (j = 0; j < n; j++) {
                fscanf(fp, "%d", &val);
                if (val != 0) {
                    insert_edge(i, j);
                }
            }
        }
        fclose(fp);
    } else {
        printf("������ �� �� �����ϴ�: %s\n", filename);
    }
}
// ? �� �Լ��� ���� �Լ����� ȣ��� ����Դϴ�
int findBridge() {
    memset(visited, 0, sizeof(visited));
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    timeCounter = 0;

    for (int i = 0; i < vsize; i++) {
        if (!visited[i]) {
            DFSBridge(i, -1);
        }
    }

    return 0;
}

int main() {
    load_graph("graph.txt");
    print_graph("�׷���(��������Ʈ)\n");

    printf("\n--- �긮�� Ž�� ��� ---\n");
    findBridge();

    return 0;
}

//11.2