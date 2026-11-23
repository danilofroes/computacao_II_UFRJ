/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao ValidarCartaoCredito (versao com strings), recebe cada digito como um argumento de linha de comando.
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

#include "aula0604.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define EOS                           '\0'

int main (int argc, char *argv[]) {
    char numeroCartao[NUMERO_MAXIMO_DIGITOS_CARTAO + 1];
    unsigned short totalDigitos;
    unsigned short indice;
    char *validacao;
    long valorDigito;
    tipoCodigosRetorno codigoRetorno;

    totalDigitos = argc - 1;

    if (totalDigitos < NUMERO_MINIMO_DIGITOS_CARTAO || totalDigitos > NUMERO_MAXIMO_DIGITOS_CARTAO) {
        printf ("%sUso: %s <d1> <d2> ... <dn> (n variando de %d a %d)%s\n", RED, argv[0], NUMERO_MINIMO_DIGITOS_CARTAO, NUMERO_MAXIMO_DIGITOS_CARTAO, RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    for (indice = 0; indice < totalDigitos; indice++) {
        errno = 0;
        valorDigito = strtol (argv[indice + 1], &validacao, 10);

        if (errno != 0 || *validacao != EOS || valorDigito < 0 || valorDigito > 9) {
            printf ("%sArgumento invalido: %s%s\n", RED, argv[indice + 1], RESET);
            exit (ARGUMENTO_INVALIDO);
        }

        numeroCartao[indice] = (char) ('0' + valorDigito);
    }

    numeroCartao[totalDigitos] = EOS;

    codigoRetorno = ValidarCartaoCredito (numeroCartao);

    printf ("Cartao: ");

    for (indice = 0; indice < totalDigitos; indice++) {
        if (indice > 0 && indice % TAMANHO_GRUPO_DIGITOS == 0)
            printf (" ");

        printf ("%c", numeroCartao[indice]);
    }

    if (codigoRetorno == ok)
        printf (" - valido\n");

    else if (codigoRetorno == erroCartaoInvalido)
        printf (" - invalido\n");

    else {
        printf (" - erro de execucao (codigo %d)\n", codigoRetorno);
        exit (ERRO_EXECUCAO);
    }

    return OK;
}

/* $RCSfile$ */
