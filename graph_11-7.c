#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���� ����ġ �׷����� �������� �����Ͽ� ���Ϸ� �����ϴ� �Լ�
void generate_weighted_complete_graph(const char* filename, int nVtx, int minW, int maxW) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d\n", nVtx);
    for (int i = 0; i < nVtx; i++) {
        fprintf(fp, "%c ", 'A' + i); // ���� �̸�
        for (int j = 0; j < nVtx; j++) {
            if (i == j)
                fprintf(fp, "0 ");
            else
                fprintf(fp, "%d ", minW + rand() % (maxW - minW + 1));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main() {
    int nVtx = 6; // ���� ��
    int minW = 1; // �ּ� ����ġ
    int maxW = 20; // �ִ� ����ġ
    generate_weighted_complete_graph("random_graph.txt", nVtx, minW, maxW);
    printf("random_graph.txt ������ �����Ǿ����ϴ�.\n");
    return 0;
}