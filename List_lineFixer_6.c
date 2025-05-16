#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENG 100
#define MAX_KOR 100

typedef struct Word {
    char eng[MAX_ENG];
    char kor[MAX_KOR];
} Word;
typedef Word Element;
typedef struct LinkedNode {
    Element data;
    struct LinkedNode* link;
}Node;
Node* head;

void init_list() { head = NULL; }
int is_empty() { return head == NULL;}
Node* get_entry(int pos) {
    Node* p = head;
    int i;
    for (i=0; i<pos; i++, p=p->link)
        if (p == NULL) return NULL;
    return p;
}
int size() {
    Node* p;
    int count = 0;
    for (p=head; p != NULL; p = p->link)
        count++;
    return count;
}

void replace(int pos, Element e) {
    Node* node = get_entry(pos);
    if (node != NULL)
        node->data = e;
}

void insert_next(Node *before, Node *node) {
    if (node != NULL) {
        node->link = before->link;
        before->link = node;
    }
}

void insert(int pos, Element e) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = e;
    new_node->link = NULL;
    if (pos == 0) {
        new_node->link = head;
        head = new_node;
    } else {
        Node* prev = get_entry(pos - 1);
        if (prev != NULL) {
            insert_next(prev, new_node);
        } else {
            free(new_node); // Free memory if position is invalid
        }
    }
}

Node* remove_next(Node* before)
{
    Node* removed = before->link;
    if (removed != NULL) {
        before->link = removed->link;
    }
    return removed;
}

void delete(int pos) {
    Node* prev, *removed;
    if (pos == 0 && !is_empty()) {
        removed = head;
        head = head->link;
        free(removed);
    }
    else {
        prev = get_entry(pos - 1);
        if (prev != NULL) {
            removed = remove_next(prev);
            free(removed);
        }
    }
}
void clear_list() {
    while (!is_empty()) {
        delete(0);
    }
}
void display(FILE *fp) {
    int i=0;
    Node* p;
    for (p = head; p != NULL; p=p->link, i++) {
        fprintf(fp, "%3d: %s - %s", i, p->data.eng, p->data.kor);
        if (fp == stdout) fprintf(fp, "\n");
    }
}

// �ܾ� �˻� �Լ�
void find_word(const char* eng) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->data.eng, eng) == 0) {
            printf("��: %s\n", p->data.kor);
            return;
        }
        p = p->link;
    }
    printf("�ܾ ã�� �� �����ϴ�.\n");
}

void my_fflush() { while (getchar() != '\n');}

int main()
{
    char command;
    int pos;
    Word word;
    FILE *fp;
    char search_eng[MAX_ENG];

    init_list();
    do{
        printf("[�޴�����] i-�Է�, d-����, r-����, p-���, l-�����б�, s-����, f-�˻�, q-����=> ");
        command = getchar();
        switch(command) {
            case 'i':
                printf("�Է��� ��ȣ: ");
                scanf("%d", &pos);
                printf("���� �ܾ�: ");
                scanf("%s", word.eng);
                printf("�ѱ� ��: ");
                my_fflush();
                fgets(word.kor, MAX_KOR, stdin);
                insert(pos, word);
                break;
            case 'd':
                printf("������ ��ȣ: ");
                scanf("%d", &pos);
                delete(pos);
                break;
            case 'r':
                printf("������ ��ȣ: ");
                scanf("%d", &pos);
                printf("���� �ܾ�: ");
                scanf("%s", word.eng);
                printf("�ѱ� ��: ");
                my_fflush();
                fgets(word.kor, MAX_KOR, stdin);
                replace(pos, word);
                break;
            case 'l':
                fp = fopen("input.txt", "r");
                if (fp != NULL) {
                    while (fscanf(fp, "%s %[^\n]", word.eng, word.kor) == 2)
                        insert(size(), word);
                    fclose(fp);
                }
                break;
            case 's':
                fp = fopen("Test.txt", "w");
                if (fp != NULL) {
                    Node* p;
                    for (p = head; p != NULL; p=p->link)
                        fprintf(fp, "%s %s", p->data.eng, p->data.kor);
                    fclose(fp);
                }
                break;
            case 'p':
                display(stdout);
                break;
            case 'f':
                printf("�˻��� ���� �ܾ�: ");
                scanf("%s", search_eng);
                find_word(search_eng);
                break;
        }
        my_fflush();
    }while(command != 'q');
}