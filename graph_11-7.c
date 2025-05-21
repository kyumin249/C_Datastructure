#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 완전 가중치 그래프를 무작위로 생성하여 파일로 저장하는 함수
void generate_weighted_complete_graph(const char* filename, int nVtx, int minW, int maxW) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    srand((unsigned int)time(NULL));
    fprintf(fp, "%d\n", nVtx);
    for (int i = 0; i < nVtx; i++) {
        fprintf(fp, "%c ", 'A' + i); // 정점 이름
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
    int nVtx = 6; // 정점 수
    int minW = 1; // 최소 가중치
    int maxW = 20; // 최대 가중치
    generate_weighted_complete_graph("random_graph.txt", nVtx, minW, maxW);
    printf("random_graph.txt 파일이 생성되었습니다.\n");
    return 0;
}