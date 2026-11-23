/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao GerarNumeroCartaoCredito, exibe um numero de cartao de credito valido gerado aleatoriamente.
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
#include <time.h>

#include "aula0604.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define NUMERO_OPERADORAS               7

int main (int argc, char *argv[]) {
    char numeroCartao[COMPRIMENTO_MAXIMO_NUMERO_CARTAO];
    tipoOperadora operadora = mastercard;
    tipoCodigosRetorno codigoRetorno;

    if (argc > 2) {
        printf ("%sUso: %s [mastercard | visa13 | visa14 | visa15 | visa16 | amex | diner]%s\n", RED, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    if (argc == 2) {
        if (strcmp (argv[1], "mastercard") == 0)
            operadora = mastercard;

        else if (strcmp (argv[1], "visa13") == 0)
            operadora = visa13;

        else if (strcmp (argv[1], "visa14") == 0)
            operadora = visa14;

        else if (strcmp (argv[1], "visa15") == 0)
            operadora = visa15;

        else if (strcmp (argv[1], "visa16") == 0)
            operadora = visa16;

        else if (strcmp (argv[1], "amex") == 0)
            operadora = amex;

        else if (strcmp (argv[1], "diner") == 0)
            operadora = diner;

        else {
            printf ("%sOperadora invalida: %s%s\n", RED, argv[1], RESET);
            exit (ARGUMENTO_INVALIDO);
        }
    }

    else {
        srand ((unsigned) time (NULL));
        operadora = (tipoOperadora) (rand () % NUMERO_OPERADORAS);
    }

    codigoRetorno = GerarNumeroCartaoCredito (operadora, numeroCartao);

    if (codigoRetorno != ok) {
        printf ("%sErro na geracao do numero do cartao de credito (codigo %d).%s\n", RED, codigoRetorno, RESET);
        exit (ERRO_EXECUCAO);
    }

    printf ("Cartao: %s\n", numeroCartao);

    return OK;
}

/* $RCSfile$ */
