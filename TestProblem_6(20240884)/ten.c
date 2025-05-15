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

int look_list(Node* head, int data) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}
int main() {
    int node_1, node_2, node_3;
    Node* head = NULL;
    printf("����� ����: ");
    scanf("%d", &node_1);
    node_product(node_1);
    for (int i = 0; i < node_1; i++) {
        printf("��� %d ������: ", i + 1);
        scanf("%d", &node_2);
        node_insert(&head, node_2);
    }
    printf("Ž���� ���� �Է��ϼ���: ");
    scanf("%d", &node_3);
    printf("%d�� ���� ����Ʈ���� %d�� ��Ÿ���ϴ�.\n", node_3, look_list(head, node_3));
    return 0;
}