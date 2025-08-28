#include <stdio.h>

int main() {
    int x;
    int *p = &x;

    printf("p = %d, &x = %d\n", p, &x);
}