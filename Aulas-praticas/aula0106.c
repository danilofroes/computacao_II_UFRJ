/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  --
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

void ExibirCemHifens();

void ExibirCemHifens() {
    printf("\n");
    
    unsigned short i;
    for (i = 0; i < 100; i++) {
        printf("-");
    }
    printf("\n\n");
}

void ExibirTituloCentralizado(char *titulo) {
    unsigned short espacosParaCentralizar;

    printf("%s%s", UNDERLINE_WHITE, BLACK_BACKGROUND);

    if (strlen(titulo) % 2 == 0)
        espacosParaCentralizar = (TAMANHO_LINHA - strlen(titulo)) / 2;

    else
        espacosParaCentralizar = ((TAMANHO_LINHA - strlen(titulo) - 1) / 2);
        
    unsigned short i;
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
    printf("%s%s", BLUE, nomeTipo);

    unsigned short colunaTipo = COLUNA_POSICIONAMENTO - strlen(nomeTipo);

    printf("%*s", colunaTipo, " ");
    printf("%s%d%s", YELLOW, tamanhoTipo, tamanhoTipo == 1 ? " byte" : " bytes");
    printf("%s\n", RESET);
}

int main() {

    unsigned short tamanhoUnsignedShort = sizeof(unsigned short);
    unsigned short tamanhoUnsignedLong = sizeof(unsigned long);
    unsigned short tamanhoUnsignedLongLong = sizeof(unsigned long long);
    unsigned short tamanhoSignedShort = sizeof(signed short);
    unsigned short tamanhoSignedLong = sizeof(signed long);
    unsigned short tamanhoSignedLongLong = sizeof(signed long long);

    unsigned short tamanhoSignedInt = sizeof(signed int);
    unsigned short tamanhoUnsignedInt = sizeof(unsigned int);
    unsigned short tamanhoSignedChar = sizeof(signed char);
    unsigned short tamanhoUnsignedChar = sizeof(unsigned char);

    unsigned short tamanhoShortInt = sizeof(short int);
    unsigned short tamanhoLongInt = sizeof(long int);
    unsigned short tamanhoLongLongInt = sizeof(long long int);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Modificadores de Sinal combinados com Modificadores de Largura");
    printf("\n");
    ExibirMensagemTipo("unsigned short", tamanhoUnsignedShort);
    ExibirMensagemTipo("unsigned long", tamanhoUnsignedLong);
    ExibirMensagemTipo("unsigned long long", tamanhoUnsignedLongLong);
    ExibirMensagemTipo("signed short", tamanhoSignedShort);
    ExibirMensagemTipo("signed long", tamanhoSignedLong);
    ExibirMensagemTipo("signed long long", tamanhoSignedLongLong);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Tipos Basicos combinados com Modificadores de Sinal");
    printf("\n");
    ExibirMensagemTipo("signed int", tamanhoSignedInt);
    ExibirMensagemTipo("unsigned int", tamanhoUnsignedInt);
    ExibirMensagemTipo("signed char", tamanhoSignedChar);
    ExibirMensagemTipo("unsigned char", tamanhoUnsignedChar);

    ExibirCemHifens();
    ExibirTituloCentralizado("Tamanhos dos Tipos Basicos combinados com Modificadores de Largura");
    printf("\n");
    ExibirMensagemTipo("short int", tamanhoShortInt);
    ExibirMensagemTipo("long int", tamanhoLongInt);
    ExibirMensagemTipo("long long int", tamanhoLongLongInt);

    return 0;
}

 /* $RCSfile$ */