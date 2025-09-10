/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  --
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

#include "aula0201.h"
#include "cores.h"

#define NUMERO_ARGUMENTOS                               2

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO        3

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    ull numeroX;
    ull numeroY;
    char *validacaoX;
    char *validacaoY;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%s\nUso: %s.\n\n", RED, argv[0]);

        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    numeroX = strtoull(argv[1], &validacaoX, 10);

    if (errno == ERANGE) {
        printf("%s\nValor maximo do tipo unsigned long long (%llu) foi excedido.\n\n", RED, ULLONG_MAX);
        exit(VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO);
    }

    if (*validacaoX != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).\n\n", RED, *validacaoX);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    numeroY = strtoull(argv[2], &validacaoY, 10);

    if (errno == ERANGE) {
        printf("%s\nValor maximo do tipo unsigned long long (%llu) foi excedido.\n\n", RED, ULLONG_MAX);
        exit(VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO);
    }

    if (*validacaoY != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).\n\n", RED, *validacaoY);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    printf("%s\nMDC (%llu, %llu) = %llu\n\n", GREEN, numeroX, numeroY, CalcularMaximoDivisorComum(numeroX, numeroY));

    return OK;
}

 /* $RCSfile$ */