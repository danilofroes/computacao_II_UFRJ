/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  script para encontrar a matriz transposta
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
    unsigned short linhas;
    unsigned short colunas;
    long double matriz[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    long double matrizTransposta[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    char *validacaoLinhas;
    char *validacaoColunas;
    char *validacaoElemento;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    tipoErros resultadoMatrizTransposta;

    if (argc < 3) {
        printf("%s\nUso: %s <linhas> <colunas> <elementos...> %s\n\n", RED, argv[0], RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO); 
    }

    errno = 0;
    linhas = strtol(argv[1], &validacaoLinhas, 10);

    if (errno == ERANGE || linhas <= 0 || linhas > NUMERO_MAXIMO_LINHAS) {
        printf("%s\nValor de linhas invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_LINHAS_INVALIDO);
    }

    if (*validacaoLinhas != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoLinhas, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    errno = 0;
    colunas = strtol(argv[2], &validacaoColunas, 10);

    if (errno == ERANGE || colunas <= 0 || colunas > NUMERO_MAXIMO_COLUNAS) {
        printf("%s\nValor de colunas invalido ou excedido.%s\n\n", RED, RESET);
        exit(VALOR_COLUNAS_INVALIDO);
    }

    if (*validacaoColunas != EOS) {
        printf("%s\nO argumento contem um caractere invalido (%c).%s\n\n", RED, *validacaoColunas, RESET);
        exit(ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if ((unsigned int)linhas * colunas != (unsigned int)(argc - 3)) {
        printf("%s\nO numero de elementos da matriz (%d) esta incorreto. Esperado: %d.%s\n\n", RED, argc - 3, linhas * colunas, RESET);
        exit(NUMERO_ELEMENTOS_INVALIDO);
    }

    k = 3;

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
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

    printf("\nMatriz Original:\n\n");

    if (ExibirMatriz(colunas, linhas, matriz) != ok) {
        printf("%s\nErro ao exibir a matriz.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    resultadoMatrizTransposta = ObterMatrizTransposta(linhas, colunas, matriz, matrizTransposta);

    if (resultadoMatrizTransposta != ok) {
        printf("%s\nErro: Matriz ultrapassou o limite de 100 colunas e 100 linhas.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    printf("\nMatriz Transposta:\n\n");

    if (ExibirMatriz(colunas, linhas, matrizTransposta) != ok) {
        printf("%s\nErro ao exibir a matriz.%s\n\n", RED, RESET);
        exit(ERRO_EXIBIR_MATRIZ);
    }

    printf("\n");

    return OK;
}

 /* $RCSfile$ */