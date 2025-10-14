/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcao para exibir matriz de no maximo 100 colunas e 100 linhas
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
 
#include "aula0501.h"
#include "cores.h"

tipoErros ExibirMatriz(unsigned short int numeroLinhas, unsigned short int numeroColunas, long double matriz[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS]) {
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

 /* $RCSfile$ */