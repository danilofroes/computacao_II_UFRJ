/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  script para calcular determinante de matriz
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
#include <errno.h>

#include "aula0501.h"
#include "cores.h"

#define OK                                              0
#define NUMERO_ARGUMENTOS_INVALIDO                      1
#define ARGUMENTO_COM_CARACTERE_INVALIDO                2
#define VALOR_LINHAS_INVALIDO                           3
#define VALOR_COLUNAS_INVALIDO                          4
#define NUMERO_ELEMENTOS_INVALIDO                       5
#define VALOR_INT_EXCEDIDO                              6
#define ERRO_EXIBIR_MATRIZ                              7

#define EOS                                            '\0'

int main(int argc, char *argv[]) {
    unsigned short ordem;
    long double matriz[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    char *validacaoOrdem;
    char *validacaoElemento;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    long double determinante;
    tipoErros resultadoDeterminante;

    if (argc < 2) {
        printf("%s\nUso: %s <ordem> <elementos...> %s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO); 
    }

    errno = 0;
    ordem = strtol(argv[1], &validacaoOrdem, 10);

    if (errno == ERANGE || ordem <= 0 || ordem > NUMERO_MAXIMO_LINHAS) {
        printf("%s\nValor de ordem invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_LINHAS_INVALIDO);
    }

    if (*validacaoOrdem != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoOrdem, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if ((unsigned int)ordem * ordem != (unsigned int)(argc - 2)) {
        printf("%s\nO numero de elementos da matriz (%d) esta incorreto. Esperado: %d.%s\n\n", RED, argc - 2, ordem * ordem, RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    k = 2;

    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            errno = 0;
            matriz[i][j] = strtold(argv[k], &validacaoElemento);

            if (errno == ERANGE) {
                printf("%s\nValor do elemento %d (linha %d, coluna %d) excedido.%s\n\n", RED, k - 2, i + 1, j + 1, RESET);
                exit(VALOR_INT_EXCEDIDO);
            }

            if (*validacaoElemento != EOS) {
                printf("%s\nO elemento %d contem caractere invalido ('%c').%s\n\n", RED, k - 2, *validacaoElemento, RESET);
                exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
            }

            k++;
        }
    }

    printf("\nMatriz:\n\n");

    for (i = 0; i < ordem; i++) {
        printf("%s | %s", BOLD_GREEN, RESET);

        for (j = 0; j < ordem; j++) {
            if (j == ordem - 1)
                printf("%.5Lf", matriz[i][j]);
            else
                printf("%.5Lf   ", matriz[i][j]);
        }

        printf("%s | %s\n", BOLD_GREEN, RESET);
    }

    printf("\n");

    resultadoDeterminante = CalcularDeterminanteMatriz(ordem, matriz, &determinante);

    if (resultadoDeterminante != ok) {
        printf("%s\nErro: Houve um problema ao calcular o determinante.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    printf("%sDeterminante: %.5Lf%s\n\n", BOLD_YELLOW, determinante, RESET);

    return OK;
}

 /* $RCSfile$ */