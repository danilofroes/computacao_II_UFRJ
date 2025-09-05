/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	Código que exibe um cabeçalho com um número de colunas desejado
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>

#include "cores.h"

void ExibirCabecalho(unsigned short);

void ExibirCabecalho(unsigned short numeroColunas) {
    unsigned short numeroLinhas;

    if (numeroColunas >=1 && numeroColunas <= 9)
        numeroLinhas = 1;

    else if (numeroColunas >= 10 && numeroColunas <= 99)
        numeroLinhas = 2;

    else if (numeroColunas >=100 && numeroColunas <= 999)
        numeroLinhas = 3;
        
    else
        numeroLinhas = 4;

    printf("%dm%dm", WHITE_BACKGROUND, BLACK);

    unsigned short i;
    for (i = 0; i < numeroLinhas; i++) {
        unsigned short j;
        for (j = 0; j < numeroColunas; j++) {
            unsigned short digito = (j / 10) % 10;
            printf("%u", digito);
        }
        printf("\n");
    }

    for (i = 0; i < numeroColunas; i++) {
        unsigned short digito = i % 10;
        printf("%u", digito);
    }

    printf("\n");

    printf("%s", RESET);
}

int main(int argc, char *argv[]) {
    unsigned short numeroColunas;

    if(argc != 2) {
        printf("%dmErro: Uso incorreto.%s\n", BOLD_RED, RESET);
        printf("Uso: %s <numero_colunas>\n", argv[0]);
        return 1;
    }

    numeroColunas = (unsigned short)atoi(argv[1]);

    if(numeroColunas < 1 || numeroColunas > 200) {
        printf("%dmErro: Numero de colunas invalido.%s\n", BOLD_RED, RESET);
        printf("O numero de colunas deve estar entre 1 e 200.\n");
        return 1;
    }

    ExibirCabecalho(numeroColunas);

    return 0;
}

/* $RCSfile$ */
