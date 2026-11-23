/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao ValidarCartaoCredito.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifdef __linux__
  #define _XOPEN_SOURCE 600
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aula0601.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define EOS                          '\0'

int main (int argc, char *argv[]) {
    byte cartao[20];
    unsigned short indiceCartao = 0;
    unsigned short indiceString = 0;
    char *stringEntrada;
    tipoCodigosRetorno retorno;

    if (argc != 2) {
        printf ("Uso: %s <\"digitos do cartao\">\n", argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    stringEntrada = argv[1];

    while (stringEntrada[indiceString] != EOS) {
        if (stringEntrada[indiceString] == ' ') {
            indiceString++;
            continue;
        }

        if (stringEntrada[indiceString] < '0' || stringEntrada[indiceString] > '9') {
            printf ("Caractere invalido encontrado: '%c'\n", stringEntrada[indiceString]);
            exit (ARGUMENTO_INVALIDO);
        }

        if (indiceCartao >= 19) {
            printf ("Erro: Numero de digitos excede o limite permitido.\n");
            exit (ARGUMENTO_INVALIDO);
        }

        cartao[indiceCartao] = (byte) (stringEntrada[indiceString] - '0');
        indiceCartao++;
        indiceString++;
    }

    cartao[indiceCartao] = 255;
    retorno = ValidarCartaoCredito (cartao);

    printf ("Cartao: ");

    for (indiceString = 0; indiceString < indiceCartao; indiceString++) {
        printf ("%d", cartao[indiceString]);

        if ((indiceString + 1) % 4 == 0 && indiceString != indiceCartao - 1)
            printf (" ");
    }

    if (retorno == ok)
        printf (" - valido\n");

    else if (retorno == erroCartaoInvalido)
        printf (" - invalido\n");

    else {
        printf (" - erro (%d)\n", retorno);
        exit (ERRO_EXECUCAO);
    }

    return OK;
}

/* $RCSfile$ */