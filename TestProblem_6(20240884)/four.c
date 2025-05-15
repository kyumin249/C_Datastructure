#include <stdio.h>

void swap(int *px, int *py) {
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

int main() {
    int x, y;
    printf("x: ");
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y);
    printf("swap()È£Ãâ ÈÄ\n");
    swap(&x, &y);
    printf("x: %d\n", x);
    printf("y: %d\n", y);
}