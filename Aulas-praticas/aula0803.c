/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao DecodificarBase16, recebe a string a decodificar e exibe os bytes gerados em notacao decimal.
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

#include "aula0801.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ERRO_EXECUCAO                   3
#define ERRO_ALOCACAO                   4

#define NUMERO_ARGUMENTOS_ESPERADO      2

#define DESTAQUE                        BOLD_BLACK WHITE_BACKGROUND
#define TEXTO_GERADO                    GREEN WHITE_BACKGROUND
#define TEXTO_ERRO                      RED WHITE_BACKGROUND

int main (int argc, char *argv[]) {
    byte *bytesSaida;
    unsigned long long numeroBytes;
    unsigned long long indice;
    unsigned long long comprimentoEntrada;
    tipoErros codigoRetorno;

    if (argc != NUMERO_ARGUMENTOS_ESPERADO) {
        printf ("%sUso: %s <string codificada em Base16>%s\n", TEXTO_ERRO, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    comprimentoEntrada = (unsigned long long) strlen (argv[1]);

    bytesSaida = (byte *) malloc ((size_t) (comprimentoEntrada / NUMERO_CARACTERES_GRUPO_BASE_16 + 1));

    if (bytesSaida == NULL) {
        printf ("%sErro na alocacao de memoria.%s\n", TEXTO_ERRO, RESET);
        exit (ERRO_ALOCACAO);
    }

    codigoRetorno = DecodificarBase16 (argv[1], bytesSaida, &numeroBytes);

    if (codigoRetorno != ok) {
        printf ("%sErro na decodificacao em Base16 (codigo %d).%s\n", TEXTO_ERRO, codigoRetorno, RESET);
        free (bytesSaida);
        exit (ERRO_EXECUCAO);
    }

    printf ("%s>>>>>%s", DESTAQUE, TEXTO_GERADO);

    for (indice = 0; indice < numeroBytes; indice++)
        printf (" %03u", bytesSaida[indice]);

    printf ("%s\n", RESET);

    free (bytesSaida);

    return OK;
}

/* $RCSfile$ */
