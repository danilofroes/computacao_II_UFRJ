/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao DecodificarBase32, recebe o alfabeto utilizado e a string a decodificar e exibe os bytes gerados em notacao hexadecimal.
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
#include <errno.h>

#include "aula0801.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3
#define ERRO_ALOCACAO                   4

#define EOS                             '\0'

#define NUMERO_ARGUMENTOS_ESPERADO      3

#define DESTAQUE                        BOLD_BLACK WHITE_BACKGROUND
#define TEXTO_GERADO                    GREEN WHITE_BACKGROUND
#define TEXTO_ERRO                      RED WHITE_BACKGROUND

int main (int argc, char *argv[]) {
    byte *bytesSaida;
    char *validacao;
    tipoAlfabetoBase32 alfabeto;
    unsigned long long numeroBytes;
    unsigned long long indice;
    unsigned long long comprimentoEntrada;
    long valorArgumento;
    tipoErros codigoRetorno;

    if (argc != NUMERO_ARGUMENTOS_ESPERADO) {
        printf ("%sUso: %s <alfabeto (0 - basico | 1 - estendido)> <string codificada em Base32>%s\n", TEXTO_ERRO, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    valorArgumento = strtol (argv[1], &validacao, 10);

    if (errno != 0 || *validacao != EOS || (valorArgumento != basico && valorArgumento != estendido)) {
        printf ("%sAlfabeto invalido: %s (0 - basico | 1 - estendido)%s\n", TEXTO_ERRO, argv[1], RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    alfabeto = (tipoAlfabetoBase32) valorArgumento;

    comprimentoEntrada = (unsigned long long) strlen (argv[2]);

    bytesSaida = (byte *) malloc ((size_t) (comprimentoEntrada * NUMERO_BYTES_GRUPO_BASE_32 / NUMERO_CARACTERES_GRUPO_BASE_32 + NUMERO_BYTES_GRUPO_BASE_32));

    if (bytesSaida == NULL) {
        printf ("%sErro na alocacao de memoria.%s\n", TEXTO_ERRO, RESET);
        exit (ERRO_ALOCACAO);
    }

    codigoRetorno = DecodificarBase32 (argv[2], alfabeto, bytesSaida, &numeroBytes);

    if (codigoRetorno != ok) {
        printf ("%sErro na decodificacao em Base32 (codigo %d).%s\n", TEXTO_ERRO, codigoRetorno, RESET);
        free (bytesSaida);
        exit (ERRO_EXECUCAO);
    }

    printf ("%s>>>>>%s", DESTAQUE, TEXTO_GERADO);

    for (indice = 0; indice < numeroBytes; indice++)
        printf (" %02X", bytesSaida[indice]);

    printf ("%s\n", RESET);

    free (bytesSaida);

    return OK;
}

/* $RCSfile$ */
