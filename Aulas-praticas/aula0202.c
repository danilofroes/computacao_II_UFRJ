#include <stdlib.h>
#include <stdio.h>

#include "aula0201.h"

#define NUMERO_ARGUMENTOS               2
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define OK                              0

int main(int argc, char *argv[]) {

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("\nUso: %s.\n\n", argv[0]);

        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }


}