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

#define NUMERO_ARGUMENTOS          1

#define OK                         0
#define NUMERO_ARGUMENTOS_INVALIDO 1
#define NUMERO_COLUNAS_INVALIDO    2

void ExibirCabecalho(unsigned short);
void ExibirHifens(unsigned short);

void ExibirCabecalho(unsigned short numeroColunas) {
    unsigned short numeroLinhas;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned short digito;

    if (numeroColunas >= 1 && numeroColunas <= 9)
        numeroLinhas = 1;

    else if (numeroColunas >= 10 && numeroColunas <= 99)
        numeroLinhas = 2;

    else if (numeroColunas >= 100 && numeroColunas <= 999)
        numeroLinhas = 3;
        
    else
        numeroLinhas = 4;

    printf("%s%s", BLACK, WHITE_BACKGROUND);

    for (i = 0; i < numeroLinhas; i++) {
        for (j = 0; j < numeroColunas; j++) {
            digito = (j / 10) % 10;
            
            printf("%u", digito);
        }
        printf("\n");
    }

    for (k = 0; k < numeroColunas; k++) {
        digito = i % 10;
        
        printf("%u", digito);
    }

    printf("\n");
    printf("%s", RESET);
}

void ExibirHifens(unsigned short numeroHifens) {
    unsigned short i;

    printf("%s%s", BLACK_BACKGROUND, WHITE);

    for (i = 0; i < numeroHifens; i++) {
        printf("-");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    unsigned short numeroColunas;

    if (argc != NUMERO_ARGUMENTOS + 1) {
        printf("%sErro: O numero de argumentos passado esta invalido.%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        printf("Deve ser passado o valor do numero de colunas.\n");
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    numeroColunas = atoi(argv[1]);

    if (numeroColunas < 1 || numeroColunas > 9999) {
        printf("%sErro: Numero de colunas invalido.%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        printf("O numero de colunas deve estar entre 1 e 9999.\n");
        exit(NUMERO_COLUNAS_INVALIDO);
    }

    ExibirCabecalho(numeroColunas);
    ExibirHifens(numeroColunas);

    return OK;
}

/* $RCSfile$ */