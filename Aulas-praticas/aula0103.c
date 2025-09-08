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
void ExibirHifens(unsigned short);

void ExibirCabecalho(unsigned short numeroColunas) {
    unsigned short numeroLinhas;

    if (numeroColunas >= 1 && numeroColunas <= 9)
        numeroLinhas = 1;

    else if (numeroColunas >= 10 && numeroColunas <= 99)
        numeroLinhas = 2;

    else if (numeroColunas >= 100 && numeroColunas <= 999)
        numeroLinhas = 3;
        
    else
        numeroLinhas = 4;

    printf("%s%s", WHITE_BACKGROUND, BLACK);

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

void ExibirHifens(unsigned short numeroHifens) {
    unsigned short i;

    printf("%s%s", BLACK_BACKGROUND, WHITE);

    for (i = 0; i < numeroHifens; i++) {
        printf("-");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("%sErro: O numero de argumentos passado esta invalido.%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        printf("Deve ser passado o valor do numero de colunas.\n");
        return 1;
    }

    unsigned short numeroColunas = atoi(argv[1]);

    if (numeroColunas < 1 || numeroColunas > 9999) {
        printf("%sErro: Numero de colunas invalido.%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        printf("O numero de colunas deve estar entre 1 e 9999.\n");
        return 1;
    }

    ExibirCabecalho(numeroColunas);
    ExibirHifens(numeroColunas);

    return 0;
}

/* $RCSfile$ */