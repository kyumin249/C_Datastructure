#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10  // 정점 개수
#define MAX_EDGES 20     // 최대 간선 수

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjList[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);  // 무방향 그래프
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

int isConnected(Graph* graph, int src, int dest) {
    Node* temp = graph->adjList[src];
    while (temp != NULL) {
        if (temp->vertex == dest) return 1;
        temp = temp->next;
    }
    return 0;
}

// 최소 연결 그래프 생성 (트리 구조로)
void generateConnectedGraph(Graph* graph) {
    int connected[MAX_VERTICES] = {0};
    connected[0] = 1;

    for (int i = 1; i < graph->numVertices; i++) {
        int u = rand() % i;  // 이미 연결된 노드 중 하나 선택
        addEdge(graph, u, i);
        connected[i] = 1;
    }

    // 추가 간선 (랜덤)
    int extraEdges = rand() % (MAX_EDGES - (graph->numVertices - 1));
    for (int i = 0; i < extraEdges; i++) {
        int a = rand() % graph->numVertices;
        int b = rand() % graph->numVertices;
        if (a != b && !isConnected(graph, a, b)) {
            addEdge(graph, a, b);
        }
    }
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int v = temp->vertex;
        if (!graph->visited[v]) {
            DFS(graph, v);
        }
        temp = temp->next;
    }
}

void printGraph(Graph* graph) {
    printf("=== 그래프 인접 리스트 ===\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    srand(time(NULL)); // 시드 초기화

    Graph* graph = createGraph(MAX_VERTICES);

    generateConnectedGraph(graph);

    printGraph(graph);

    printf("\nDFS 방문 순서: ");
    DFS(graph, 0);

    printf("\n");

    return 0;
}
//11.3-1
