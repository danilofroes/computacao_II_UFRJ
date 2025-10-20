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

tipoErros CalcularDeterminanteMatriz(unsigned short ordemMatriz, long double matrizOriginal[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double *determinante) {
    unsigned short i;
    long double resultado;
    long double complementoAlgebrico;
    tipoErros calculoComplemento;

    if (ordemMatriz > NUMERO_MAXIMO_LINHAS)
        return numeroMaximoLinhas;

    if (ordemMatriz > NUMERO_MAXIMO_COLUNAS)
        return numeroMaximoColunas;

    if (ordemMatriz == 0)
        return matrizIndeterminada;

    if (ordemMatriz == 1) {
        *determinante = matrizOriginal[0][0];
        return ok;
    }

    if (ordemMatriz == 2) {
        *determinante = (matrizOriginal[0][0] * matrizOriginal[1][1]) - (matrizOriginal[0][1] * matrizOriginal[1][0]);
        return ok;
    }

    if (ordemMatriz == 3) {
        long double somaDiagonalPrincipal = 
        (matrizOriginal[0][0] * matrizOriginal[1][1] * matrizOriginal[2][2]) +
        (matrizOriginal[0][1] * matrizOriginal[1][2] * matrizOriginal[2][0]) +
        (matrizOriginal[0][2] * matrizOriginal[1][0] * matrizOriginal[2][1]);

        long double somaDiagonalSecundaria = 
        (matrizOriginal[0][2] * matrizOriginal[1][1] * matrizOriginal[2][0]) +
        (matrizOriginal[0][0] * matrizOriginal[1][2] * matrizOriginal[2][1]) +
        (matrizOriginal[0][1] * matrizOriginal[1][0] * matrizOriginal[2][2]);

        resultado = somaDiagonalPrincipal - somaDiagonalSecundaria;
        *determinante = resultado;

        return ok;
    }

    resultado = 0;

    for (i = 0; i < ordemMatriz; i++) {
        calculoComplemento = CalcularComplementoAlgebrico(ordemMatriz, 0, i, matrizOriginal, &complementoAlgebrico);
        if (calculoComplemento != ok)
            return erroCalculoFuncao;

        resultado += matrizOriginal[0][i] * complementoAlgebrico;
    }

    *determinante = resultado;

    return ok;
}

tipoErros CalcularMenorComplementar(unsigned short ordemMatriz, unsigned short linha, unsigned short coluna, long double matrizOriginal[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double *menorComplementar) {
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned short l;
    long double matrizMenorComplementar[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    tipoErros calculoDeterminante;

    if (ordemMatriz > NUMERO_MAXIMO_LINHAS)
        return numeroMaximoLinhas;

    if (ordemMatriz > NUMERO_MAXIMO_COLUNAS)
        return numeroMaximoColunas;

    if (linha >= ordemMatriz || coluna >= ordemMatriz)
        return matrizIndeterminada;

    k = 0;
    l = 0;

    for (i = 0; i < ordemMatriz; i++) {
        if (i != linha) {
            l = 0;

            for (j = 0; j < ordemMatriz; j++) {
                if (j != coluna) {
                    matrizMenorComplementar[k][l] = matrizOriginal[i][j];
                    l++;
                }
            }
            k++;
        }
    }

    calculoDeterminante = CalcularDeterminanteMatriz(ordemMatriz - 1, matrizMenorComplementar, menorComplementar);
    if (calculoDeterminante != ok)
        return erroCalculoFuncao;

    return ok;
}

tipoErros CalcularComplementoAlgebrico (unsigned short ordemMatriz, unsigned short linha, unsigned short coluna, long double matrizOriginal[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], long double *complementoAlgebrico) {
    long double determinanteMenor;
    tipoErros calculoMenorComplementar;
    long double sinal;

    calculoMenorComplementar = CalcularMenorComplementar(ordemMatriz, linha, coluna, matrizOriginal, &determinanteMenor);
    if (calculoMenorComplementar != ok)
        return erroCalculoFuncao;

    sinal = ((linha + coluna) % 2 == 0) ? 1.0L : -1.0L;

    *complementoAlgebrico = sinal * determinanteMenor;

    return ok;
}

 /* $RCSfile$ */