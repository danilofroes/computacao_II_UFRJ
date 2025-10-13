/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	Codigo para exibir o tamanho dos tipos basicos do C
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cores.h"

#define TAMANHO_LINHA 100
#define COLUNA_POSICIONAMENTO 91

#define OK 0

void ExibirCemHifens();

void ExibirCemHifens() {
    unsigned short i;

    printf("\n");
    
    for (i = 0; i < 100; i++) {
        printf("-");
    }

    printf("\n\n");
}

void ExibirTituloCentralizado(char *titulo) {
    unsigned short espacosParaCentralizar;
    unsigned short i;

    printf("%s%s", UNDERLINE_WHITE, BLACK_BACKGROUND);

    if (strlen(titulo) % 2 == 0)
        espacosParaCentralizar = (TAMANHO_LINHA - strlen(titulo)) / 2;

    else
        espacosParaCentralizar = ((TAMANHO_LINHA - strlen(titulo) - 1) / 2);
        
    for (i = 0; i < espacosParaCentralizar; i++) {
        printf(" ");
    }

    printf("%s", titulo);

    for (i = 0; i < espacosParaCentralizar; i++) {
        printf(" ");
        
        if ((strlen(titulo) % 2 != 0) && (i == espacosParaCentralizar - 1))
            printf(" ");
    }

    printf("%s\n", RESET);
}

void ExibirMensagemTipo(char *nomeTipo, int tamanhoTipo) {
    unsigned short colunaTipo;

    printf("%s%s", BLUE, nomeTipo);

    colunaTipo = COLUNA_POSICIONAMENTO - strlen(nomeTipo);

    printf("%*s", colunaTipo, " ");
    printf("%s%d%s", YELLOW, tamanhoTipo, tamanhoTipo == 1 ? " byte" : " bytes");
    printf("%s\n", RESET);
}

int main() {
    unsigned short tamanhoInt = sizeof(int);
    unsigned short tamanhoFloat = sizeof(float);
    unsigned short tamanhoDouble = sizeof(double);
    unsigned short tamanhoChar = sizeof(char);
    unsigned short tamanhoVoid = sizeof(void);

    unsigned short tamanhoSigned = sizeof(signed);
    unsigned short tamanhoUnsigned = sizeof(unsigned);

    unsigned short tamanhoShort = sizeof(short);
    unsigned short tamanhoLong = sizeof(long);
    unsigned short tamanhoLongLong = sizeof(long long);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Tipos Basicos");
    printf("\n");
    ExibirMensagemTipo("int", tamanhoInt);
    ExibirMensagemTipo("float", tamanhoFloat);
    ExibirMensagemTipo("double", tamanhoDouble);
    ExibirMensagemTipo("char", tamanhoChar);
    ExibirMensagemTipo("void", tamanhoVoid);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Modificadores de Sinal");
    printf("\n");
    ExibirMensagemTipo("signed", tamanhoSigned);
    ExibirMensagemTipo("unsigned", tamanhoUnsigned);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Modificadores de Largura");
    printf("\n");
    ExibirMensagemTipo("short", tamanhoShort);
    ExibirMensagemTipo("long", tamanhoLong);
    ExibirMensagemTipo("long long", tamanhoLongLong);

    return OK;
}

 /* $RCSfile$ */