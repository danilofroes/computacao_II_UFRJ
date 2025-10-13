/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  script para calcular exponencial
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

#include "aula0401.h"
#include "cores.h"

#define NUMERO_ARGUMENTOS                               2

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_DOUBLE_EXCEDIDO                           3
#define VALOR_INTEIRO_EXCEDIDO                          4

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    double base;
    int expoente;
    char *validacaoBase;
    char *validacaoExpoente;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%s\nUso: %s <base> <expoente>.%s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    base = strtod(argv[1], &validacaoBase);

    if (errno == ERANGE) {
        printf("%s\nValor do tipo double foi excedido.%s\n\n", RED, RESET);
        exit(VALOR_DOUBLE_EXCEDIDO);
    }

    if (*validacaoBase != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoBase, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    expoente = strtol(argv[2], &validacaoExpoente, 10);

    if (errno == ERANGE) {
        printf("%s\nValor do tipo int foi excedido.%s\n\n", RED, RESET);
        exit(VALOR_INTEIRO_EXCEDIDO);
    }

    if (*validacaoExpoente != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoExpoente, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    printf("%s%s\n%F ^ %d:%s%s %LF%s\n\n", YELLOW, BLUE_BACKGROUND, base, expoente, RESET, RED, CalcularExponencial(base, expoente), RESET);

    return OK;
}

 /* $RCSfile$ */