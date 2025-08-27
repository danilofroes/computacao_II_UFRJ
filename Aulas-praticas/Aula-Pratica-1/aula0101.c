#include <stdio.h>

int main() {
    unsigned int i;

    for (i = 0; i < 255; i++) {
        printf("\e[38,5,%dm", i);
        printf("\e[0m");
    }
}