/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  codigo para gerar o maximo divisor comum (mdc) de dois numeros
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

#include "aula0201.h"
#include "cores.h"

#define NUMERO_ARGUMENTOS                               2

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO        3
#define MDC_DE_ZERO_E_ZERO_E_INDEFINIDO                 4

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    ull numeroX;
    ull numeroY;
    char *validacaoX;
    char *validacaoY;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%s\nUso: %s <numero-1> <numero-2>.\n\n%s", RED, argv[0], RESET);

        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    numeroX = strtoull(argv[1], &validacaoX, 10);

    if (errno == ERANGE) {
        printf("%s\nValor maximo do tipo unsigned long long (%llu) foi excedido.\n\n%s", RED, ULLONG_MAX, RESET);
        exit(VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO);
    }

    if (*validacaoX != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).\n\n%s", RED, *validacaoX, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    numeroY = strtoull(argv[2], &validacaoY, 10);

    if (errno == ERANGE) {
        printf("%s\nValor maximo do tipo unsigned long long (%llu) foi excedido.\n\n%s", RED, ULLONG_MAX, RESET);
        exit(VALOR_MAXIMO_UNSIGNED_LONG_LONG_EXCEDIDO);
    }

    if (*validacaoY != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).\n\n%s", RED, *validacaoY, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (numeroX == 0 && numeroY == 0) {
        printf("%s\nErro: MDC(0,0) e indefinido.\n\n%s", RED, RESET);
        exit(MDC_DE_ZERO_E_ZERO_E_INDEFINIDO);
    }

    printf("%s\nMDC (%llu, %llu) = %llu\n\n%s", GREEN, numeroX, numeroY, CalcularMaximoDivisorComum(numeroX, numeroY), RESET);

    return OK;
}

 /* $RCSfile$ */