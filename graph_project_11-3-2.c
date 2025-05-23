#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node** create_graph(int n) {
    Node** graph = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }
    return graph;
}

void free_graph(Node** graph, int n) {
    for (int i = 0; i < n; i++) {
        Node* current = graph[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

void add_edge(Node** graph, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = graph[v];
    graph[v] = newNode;
}

void generate_connected_graph(Node** graph, int n) {
    int** edges = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        edges[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 1; i < n; i++) {
        int parent = rand() % i;
        add_edge(graph, i, parent);
        edges[i][parent] = edges[parent][i] = 1;
    }

    int extra_edges = n / 2;
    for (int i = 0; i < extra_edges; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && edges[u][v] == 0) {
            add_edge(graph, u, v);
            edges[u][v] = edges[v][u] = 1;
        }
    }

    for (int i = 0; i < n; i++) free(edges[i]);
    free(edges);
}

void iterative_DFS(Node** graph, int start, int n, int* visit_order) {
    int* stack = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    int top = -1, idx = 0;

    stack[++top] = start;
    visited[start] = 1;

    while (top >= 0) {
        int curr = stack[top--];
        visit_order[idx++] = curr;

        Node* adj = graph[curr];
        int* temp = (int*)malloc(n * sizeof(int));
        int count = 0;
        while (adj != NULL) {
            temp[count++] = adj->vertex;
            adj = adj->next;
        }
        for (int i = count - 1; i >= 0; i--) {
            int next = temp[i];
            if (!visited[next]) {
                visited[next] = 1;
                stack[++top] = next;
            }
        }
        free(temp);
    }
    free(stack);
    free(visited);
}

double measure_execution_time(Node** graph, int n, int repeat) {
    clock_t start_time, end_time;
    int* visit_order = (int*)malloc(n * sizeof(int));
    
    start_time = clock();
    for (int i = 0; i < repeat; i++) {
        iterative_DFS(graph, 0, n, visit_order);
    }
    end_time = clock();
    
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC / repeat;
    printf("정점 개수 = %4d, 실행 시간: %.8f 초\n", n, elapsed);
    
    free(visit_order);
    return elapsed;
}

int main() {
    srand((unsigned int)time(NULL));
    
    int repeat = 1000;
    double elapsed = 0.0;

    printf("각 정점 개수별 실행 시간 (0.0015초를 넘으면 종료):\n");
    for (int size = 5; ; size += 5) {
        Node** graph = create_graph(size);
        generate_connected_graph(graph, size);
        elapsed = measure_execution_time(graph, size, repeat);
        free_graph(graph, size);
        if (elapsed > 0.00015) break;
    }

    return 0;
}
