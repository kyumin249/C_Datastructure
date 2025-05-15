#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;
Node* node_product(int data) {
    Node* result = (Node*)malloc(sizeof(Node));
    if (result == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    result->data = data;
    result->next = NULL;
    return result;
}
void node_insert(Node** head, int data) {
    Node* new_node = node_product(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
void sum_list(Node* head) {
    int sum = 0;
    Node* temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    printf("���Ḯ��Ʈ�� ������ ��: %d\n", sum);
}
    


int main() {
    int node_1, node_2;
    Node* head = NULL;
    printf("����� ����: ");
    scanf("%d", &node_1);
    node_product(node_1);
    for (int i = 0; i < node_1; i++) {
        printf("��� %d ������: ", i + 1);
        scanf("%d", &node_2);
        node_insert(&head, node_2);
    }
    sum_list(head);
    return 0;
    
}