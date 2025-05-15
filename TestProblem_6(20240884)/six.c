#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct node {
    int data;
    struct node* next;
} Node;

// �� ��� ���� �Լ�
Node* node_product(int data) {
    Node* result = (Node*)malloc(sizeof(Node)); // �޸� �Ҵ�
    if (result == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    result->data = data; // ������ ����
    result->next = NULL; // ���� ��� �ʱ�ȭ
    return result;
}

// ��� ���� �Լ�
void node_insert(Node** head, int data) {
    Node* new_node = node_product(data); // �� ��� ����
    if (*head == NULL) {
        *head = new_node; // ����Ʈ�� ��� ������ �� ��带 ���� ����
    } else {
        Node* temp = *head;
        while (temp->next != NULL) { // ����Ʈ ������ �̵�
            temp = temp->next;
        }
        temp->next = new_node; // �� ��带 ���� �߰�
    }
}

// ���� ����Ʈ ��� �Լ�
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
    Node* head = NULL; // ���� ����Ʈ�� ��� �ʱ�ȭ

    printf("����� ����: ");
    scanf("%d", &node_count);

    for (int i = 0; i < node_count; i++) {
        printf("��� %d ������: ", i + 1);
        scanf("%d", &node_data);
        node_insert(&head, node_data); // ��� ����
    }

    printf("������ ���� ����Ʈ: ");
    print_list(head); // ���� ����Ʈ ���

    // �޸� ����
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}