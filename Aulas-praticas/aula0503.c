/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  script para exibir uma matriz
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
    unsigned short linhasMatriz1;
    unsigned short colunasMatriz1;
    long double matriz1[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    char *validacaoLinhasMatriz1;
    char *validacaoColunasMatriz1;
    unsigned short linhasMatriz2;
    unsigned short colunasMatriz2;
    long double matriz2[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    char *validacaoLinhasMatriz2;
    char *validacaoColunasMatriz2;
    long double matrizProduto[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    char *validacaoElemento;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    tipoErros resultadoMultiplicacao;

    if (argc < 5) {
        printf("%s\nUso: %s <linhas> <colunas> <elementos...> %s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO); 
    }

    errno = 0;
    linhasMatriz1 = strtol(argv[1], &validacaoLinhasMatriz1, 10);

    if (errno == ERANGE || linhasMatriz1 <= 0 || linhasMatriz1 > NUMERO_MAXIMO_LINHAS) {
        printf("%s\nValor de linhas da matriz 1 invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_LINHAS_INVALIDO);
    }

    if (*validacaoLinhasMatriz1 != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoLinhasMatriz1, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    colunasMatriz1 = strtol(argv[2], &validacaoColunasMatriz1, 10);

    if (errno == ERANGE || colunasMatriz1 <= 0 || colunasMatriz1 > NUMERO_MAXIMO_COLUNAS) {
        printf("%s\nValor de colunas da matriz 1 invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_COLUNAS_INVALIDO);
    }

    if (*validacaoColunasMatriz1 != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoColunasMatriz1, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    linhasMatriz2 = strtol(argv[3], &validacaoLinhasMatriz2, 10);

    if (errno == ERANGE || linhasMatriz2 <= 0 || linhasMatriz2 > NUMERO_MAXIMO_LINHAS) {
        printf("%s\nValor de linhas da matriz 2 invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_LINHAS_INVALIDO);
    }

    if (*validacaoLinhasMatriz2 != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoLinhasMatriz2, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    colunasMatriz2 = strtol(argv[4], &validacaoColunasMatriz2, 10);

    if (errno == ERANGE || colunasMatriz2 <= 0 || colunasMatriz2 > NUMERO_MAXIMO_COLUNAS) {
        printf("%s\nValor de colunas da matriz 2 invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_COLUNAS_INVALIDO);
    }

    if (*validacaoColunasMatriz2 != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoColunasMatriz2, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if ((unsigned int)linhasMatriz1 * colunasMatriz1 != (unsigned int)((argc - 5 - (linhasMatriz2 * colunasMatriz2)))) {
        printf("%s\nO numero de elementos da matriz 1 (%d) esta incorreto. Esperado: %d.%s\n\n", RED, argc - 5 - (linhasMatriz2 * colunasMatriz2), linhasMatriz1 * colunasMatriz1, RESET);
        exit(NUMERO_ELEMENTOS_INVALIDO);
    }

    if ((unsigned int)linhasMatriz2 * colunasMatriz2 != (unsigned int)((argc - 5 - (linhasMatriz1 * colunasMatriz1)))) {
        printf("%s\nO numero de elementos da matriz 2 (%d) esta incorreto. Esperado: %d.%s\n\n", RED, argc - 5 - (linhasMatriz1 * colunasMatriz1), linhasMatriz2 * colunasMatriz2, RESET);
        exit(NUMERO_ELEMENTOS_INVALIDO);
    }

    k = 5;

    for (i = 0; i < linhasMatriz1; i++) {
        for (j = 0; j < colunasMatriz1; j++) {
            errno = 0;
            matriz1[i][j] = strtold(argv[k], &validacaoElemento);

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

    k = 5 + (linhasMatriz1 * colunasMatriz1);

    for (i = 0; i < linhasMatriz2; i++) {
        for (j = 0; j < colunasMatriz2; j++) {
            errno = 0;
            matriz2[i][j] = strtold(argv[k], &validacaoElemento);

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

    printf("\nMatriz 1:\n\n");

    if (ExibirMatriz(linhasMatriz1, colunasMatriz1, matriz1) != ok) {
        printf("%s\nErro ao exibir a matriz 1.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    printf("\nMatriz 2:\n\n");

    if (ExibirMatriz(linhasMatriz2, colunasMatriz2, matriz2) != ok) {
        printf("%s\nErro ao exibir a matriz 2.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    resultadoMultiplicacao = MultiplicarMatrizes(linhasMatriz1, colunasMatriz1, linhasMatriz2, colunasMatriz2, matriz1, matriz2, matrizProduto);

    if (resultadoMultiplicacao != ok) {
        if (resultadoMultiplicacao == matrizesIncompativeis)
            printf("%s\nErro: Matrizes incompativeis para multiplicacao.%s\n\n", RED, RESET);

        else
            printf("%s\nErro ao multiplicar as matrizes.%s\n\n", RED, RESET);

        exit(ERRO_EXIBIR_MATRIZ);
}

    printf("\nMatriz Produto:\n\n");

    if (ExibirMatriz(linhasMatriz1, colunasMatriz2, matrizProduto) != ok) {
        printf("%s\nErro ao exibir a matriz.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    printf("\n");

    return OK;
}

 /* $RCSfile$ */