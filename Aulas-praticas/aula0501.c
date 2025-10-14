/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcoes para manipulacao de matrizes de no maximo 100 colunas e 100 linhas
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
 
#include "aula0501.h"
#include "cores.h"

tipoErros ExibirMatriz(unsigned short numeroLinhas, unsigned short numeroColunas, long double matriz[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS]) {
    unsigned short i;
    unsigned short j;

    if (numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroMaximoLinhas;

    if (numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroMaximoColunas;

    for (i = 0; i < numeroLinhas; i++) {
        printf("%s | %s", BOLD_GREEN, RESET);

        for (j = 0; j < numeroColunas; j++) {
            if (j == numeroColunas - 1)
                printf("%.10Lf", matriz[i][j]);
            else
                printf("%.10Lf   ", matriz[i][j]);
        }

        printf("%s | %s\n", BOLD_GREEN, RESET);
    }

    return ok;
}

tipoErros MultiplicarMatrizes(unsigned short numeroLinhasMatriz1, unsigned short numeroColunasMatriz1, unsigned short numeroLinhasMatriz2, unsigned short numeroColunasMatriz2, long double matriz1[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double matriz2[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double matrizProduto[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS]) {
    unsigned short i;
    unsigned short j;
    unsigned short k;

    if (numeroLinhasMatriz1 > NUMERO_MAXIMO_LINHAS || numeroLinhasMatriz2 > NUMERO_MAXIMO_LINHAS)
        return numeroMaximoLinhas;

    if (numeroColunasMatriz1 > NUMERO_MAXIMO_COLUNAS || numeroColunasMatriz2 > NUMERO_MAXIMO_COLUNAS)
        return numeroMaximoColunas;

    if (numeroColunasMatriz1 != numeroLinhasMatriz2)
        return matrizesIncompativeis;

    for (i = 0; i < numeroLinhasMatriz1; i++) {
        for (j = 0; j < numeroColunasMatriz2; j++) {
            matrizProduto[i][j] = 0;
            for (k = 0; k < numeroColunasMatriz1; k++) {
                matrizProduto[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    return ok;
}

tipoErros ObterMatrizTransposta(unsigned short numeroLinhas, unsigned short numeroColunas, long double matrizOriginal[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double matrizTransposta[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS]) {
    unsigned short i;
    unsigned short j;

    if (numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroMaximoLinhas;

    if (numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroMaximoColunas;

    for (i = 0; i < numeroLinhas; i++) {
        for (j = 0; j < numeroColunas; j++) {
            matrizTransposta[j][i] = matrizOriginal[i][j];
        }
    }

    return ok;
}

 /* $RCSfile$ */