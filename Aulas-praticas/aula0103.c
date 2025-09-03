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
    unsigned short i;
    unsigned short numeroLinhas;

    if (numeroColunas >=1 && numeroColunas <= 9)
        numeroLinhas = 1;

    else if (numeroColunas >= 10 && numeroColunas <= 99)
        numeroLinhas = 2;

    else if (numeroColunas >=100 && numeroColunas <= 999)
        numeroLinhas = 3;
        
    else
        numeroLinhas = 4;
}

int main(int argc, char *argv[]) {

}

/* $RCSfile$ */
