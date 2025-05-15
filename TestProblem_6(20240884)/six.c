#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct node {
    int data;
    struct node* next;
} Node;

// 새 노드 생성 함수
Node* node_product(int data) {
    Node* result = (Node*)malloc(sizeof(Node)); // 메모리 할당
    if (result == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    result->data = data; // 데이터 설정
    result->next = NULL; // 다음 노드 초기화
    return result;
}

// 노드 삽입 함수
void node_insert(Node** head, int data) {
    Node* new_node = node_product(data); // 새 노드 생성
    if (*head == NULL) {
        *head = new_node; // 리스트가 비어 있으면 새 노드를 헤드로 설정
    } else {
        Node* temp = *head;
        while (temp->next != NULL) { // 리스트 끝까지 이동
            temp = temp->next;
        }
        temp->next = new_node; // 새 노드를 끝에 추가
    }
}

// 연결 리스트 출력 함수
void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf("->");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int node_count, node_data;
    Node* head = NULL; // 연결 리스트의 헤드 초기화

    printf("노드의 개수: ");
    scanf("%d", &node_count);

    for (int i = 0; i < node_count; i++) {
        printf("노드 %d 데이터: ", i + 1);
        scanf("%d", &node_data);
        node_insert(&head, node_data); // 노드 삽입
    }

    printf("생성된 연결 리스트: ");
    print_list(head); // 연결 리스트 출력

    // 메모리 해제
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}