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

// 단어 검색 함수
void find_word(const char* eng) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->data.eng, eng) == 0) {
            printf("뜻: %s\n", p->data.kor);
            return;
        }
        p = p->link;
    }
    printf("단어를 찾을 수 없습니다.\n");
}

void my_fflush() { while (getchar() != '\n');}
void sort_wordlist() {
    if (head == NULL || head->link == NULL) return;
    Node *i, *j;
    Element temp;
    for (i = head; i->link != NULL; i = i->link) {
        for (j = i->link; j != NULL; j = j->link) {
            if (strcmp(i->data.eng, j->data.eng) > 0) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("단어장이 영어 알파벳순으로 정렬되었습니다.\n");
}
void search_partial(const char* keyword) {
    Node* p = head;
    int found = 0;
    while (p != NULL) {
        if (strstr(p->data.eng, keyword) != NULL) {
            printf("%s - %s", p->data.eng, p->data.kor);
            found = 1;
        }
        p = p->link;
    }
    if (!found) printf("해당 단어(부분)를 찾을 수 없습니다.\n");
}
void wordlist_stats() {
    int count = 0, maxlen = 0, minlen = 1000;
    char longest[MAX_ENG] = "", shortest[MAX_ENG] = "";
    Node* p = head;
    while (p != NULL) {
        int len = strlen(p->data.eng);
        if (len > maxlen) {
            maxlen = len;
            strcpy(longest, p->data.eng);
        }
        if (len < minlen) {
            minlen = len;
            strcpy(shortest, p->data.eng);
        }
        count++;
        p = p->link;
    }
    printf("총 단어 수: %d\n", count);
    if (count > 0) {
        printf("가장 긴 단어: %s (%d글자)\n", longest, maxlen);
        printf("가장 짧은 단어: %s (%d글자)\n", shortest, minlen);
    }
}
int main()
{
    char command;
    int pos;
    Word word;
    FILE *fp;
    char search_eng[MAX_ENG];

    init_list();
    do{
        printf("[메뉴선택] i-입력, d-삭제, r-변경, p-출력, l-파일읽기, s-저장, f-검색, q-종료,t-정렬,g-부분검색, m-통계 => ");
        command = getchar();
        switch(command) {
	  case 't': sort_wordlist(); break;
	  case 'm': wordlist_stats(); break;
	  case 'g':
    	printf("검색할 영어 단어(부분): ");
    	scanf("%s", search_eng);
    	search_partial(search_eng);
    	break;
            case 'i':
                printf("입력행 번호: ");
                scanf("%d", &pos);
                printf("영어 단어: ");
                scanf("%s", word.eng);
                printf("한글 뜻: ");
                my_fflush();
                fgets(word.kor, MAX_KOR, stdin);
                insert(pos, word);
                break;
            case 'd':
                printf("삭제행 번호: ");
                scanf("%d", &pos);
                delete(pos);
                break;
            case 'r':
                printf("변경행 번호: ");
                scanf("%d", &pos);
                printf("영어 단어: ");
                scanf("%s", word.eng);
                printf("한글 뜻: ");
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
                printf("검색할 영어 단어: ");
                scanf("%s", search_eng);
                find_word(search_eng);
                break;
        }
        my_fflush();
    }while(command != 'q');
}
