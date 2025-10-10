/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  codigo principal para calcular o termo na serie de fibonacci
 *
 * $Author$
 * $Date$
 * $Log$
 */

#if defined (__FreeBSD__) && defined (__STRICT_ANSI__)
  #define __LONG_LONG_SUPPORTED
#endif

#ifdef __linux__
  #define _XOPEN_SOURCE 600
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

#include "aula0301.h"
#include "cores.h"

#define NUMERO_ARGUMENTOS                               1

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_MAXIMO_UNSIGNED_SHORT_EXCEDIDO            3
#define VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO        4

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    us termo;
    ull resultado;
    char *validacaoTermo;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%s\nUso: %s <numero-1>.%s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    termo = (us)strtoul(argv[1], &validacaoTermo, 10);

    if (errno == ERANGE || termo == USHRT_MAX) {
        printf("%s\nValor maximo do tipo unsigned short (%hu) foi excedido.%s\n\n", RED, USHRT_MAX, RESET);
        exit(VALOR_MAXIMO_UNSIGNED_SHORT_EXCEDIDO);
    }

    if (*validacaoTermo != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoTermo, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    resultado = CalcularTermoSerieFibonacci(termo);

    if (resultado == ULLONG_MAX) {
        printf("%s\nValor maximo do tipo unsigned long long (%llu) foi excedido.%s\n\n", RED, ULLONG_MAX, RESET);
        exit(VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO);
    }

    printf("%s%s\nF (%hu) = %llu%s\n\n", BLACK, WHITE_BACKGROUND, termo, resultado, RESET);

    return OK;
}

 /* $RCSfile$ */