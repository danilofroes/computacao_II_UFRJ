/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa para gerar o digito verificador de um numero de cartao de credito.
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
#include <errno.h>
#include "aula0601.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define EOS                             '\0'

int main (int argc, char *argv[]) {
  byte cartao[20];
    unsigned short indice;
    char *validacao;
    long temp;
    unsigned short totalDigitos;

    if (argc < 13 || argc > 17) {
        printf ("Uso: %s <d1> <d2> ... <dn> (13 < n < 17)\n", argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    totalDigitos = argc - 1;

    for (indice = 0; indice < totalDigitos; indice++) {
        errno = 0;
        temp = strtol (argv[indice + 1], &validacao, 10);

        if (errno != 0 || *validacao != EOS || temp < 0 || temp > 9) {
            printf ("Argumento invalido: %s\n", argv[indice + 1]);
            exit (ARGUMENTO_INVALIDO);
        }

        cartao[indice] = (byte) temp;
    }

    cartao[totalDigitos] = 255;

    if (GerarDigitoVerificadorCartaoCredito (cartao) != ok) {
        printf ("Erro na geracao do digito verificador.\n");
        exit (ERRO_EXECUCAO);
    }

    printf ("Cartao: ");
    for (indice = 0; indice <= totalDigitos; indice++) {
        printf ("%d", cartao[indice]);

        if ((indice + 1) % 4 == 0 && indice != totalDigitos)
            printf (" ");
    }
    printf ("\n");

    return OK;
}

/* $RCSfile$ */