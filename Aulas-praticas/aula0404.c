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

#ifdef __linux__
  #define _XOPEN_SOURCE 600
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

#include "aula0401.h"
#include "cores.h"

#define NUMERO_ARGUMENTOS                               1

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_FLOAT_EXCEDIDO                            3
#define PERCENTUAL_INVALIDO                             4

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    float percentual;
    char *validacaoPercentual;
    unsigned short N;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%s\nUso: %s <percentual>.%s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    percentual = strtof(argv[1], &validacaoPercentual);

    if (errno == ERANGE) {
        printf("%s\nValor do tipo float foi excedido.%s\n\n", RED, RESET);
        exit(VALOR_FLOAT_EXCEDIDO);
    }

    if (*validacaoPercentual != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoPercentual, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (percentual < 0 || percentual > 1) {
        printf("%s\nO argumento percentual deve estar entre 0 e 1.%s\n\n", RED, RESET);
        exit(PERCENTUAL_INVALIDO);
    }

    printf("%s%s\nS(%d): %.10f%s\n", BLACK, WHITE_BACKGROUND, 0, CalcularSerieHarmonicaAlternada(0), RESET);

    N = 1;

    while (fabsf(CalcularSerieHarmonicaAlternada(N) - CalcularSerieHarmonicaAlternada(N - 1)) >= (percentual * CalcularSerieHarmonicaAlternada(N - 1))) {
        if (N % 2 == 0)
            printf("%s%s\nS(%d): %.10f%s\n", BLACK, WHITE_BACKGROUND, N, CalcularSerieHarmonicaAlternada(N), RESET);
        
        else
            printf("%s%s\nS(%d): %.10f%s\n", WHITE, BLACK_BACKGROUND, N, CalcularSerieHarmonicaAlternada(N), RESET);

        N++;
    }

    printf("\n");

    return OK;
}

 /* $RCSfile$ */