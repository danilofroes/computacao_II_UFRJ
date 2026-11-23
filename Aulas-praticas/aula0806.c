/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao CodificarBase64, recebe o indicador de final de linha, o alfabeto desejado e o numero de bytes a codificar seguido pelos bytes em notacao hexadecimal.
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

#include "aula0801.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3
#define ERRO_ALOCACAO                   4

#define EOS                             '\0'

#define VALOR_MAXIMO_BYTE               255

#define NUMERO_CARACTERES_FINAL_LINHA   2

#define NUMERO_ARGUMENTOS_FIXOS         4

#define DESTAQUE                        BOLD_BLACK WHITE_BACKGROUND
#define TEXTO_GERADO                    GREEN WHITE_BACKGROUND
#define TEXTO_ERRO                      RED WHITE_BACKGROUND

int main (int argc, char *argv[]) {
    byte *bytesEntrada;
    char *stringSaida;
    char *validacao;
    tipoFinalLinha finalLinha;
    tipoAlfabeto64 alfabeto;
    unsigned long long numeroBytes;
    unsigned long long numeroCaracteres;
    unsigned long long indice;
    long valorArgumento;
    tipoErros codigoRetorno;

    if (argc < NUMERO_ARGUMENTOS_FIXOS + 1) {
        printf ("%sUso: %s <final de linha (0 - desabilitado | 1 - habilitado)> <alfabeto (0 - padrao | 1 - seguro)> <numero de bytes> <b1> <b2> ... <bn> (bytes em notacao hexadecimal)%s\n", TEXTO_ERRO, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    valorArgumento = strtol (argv[1], &validacao, 10);

    if (errno != 0 || *validacao != EOS || (valorArgumento != desabilitado && valorArgumento != habilitado)) {
        printf ("%sIndicador de final de linha invalido: %s (0 - desabilitado | 1 - habilitado)%s\n", TEXTO_ERRO, argv[1], RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    finalLinha = (tipoFinalLinha) valorArgumento;

    errno = 0;
    valorArgumento = strtol (argv[2], &validacao, 10);

    if (errno != 0 || *validacao != EOS || (valorArgumento != padrao && valorArgumento != seguro)) {
        printf ("%sAlfabeto invalido: %s (0 - padrao | 1 - seguro)%s\n", TEXTO_ERRO, argv[2], RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    alfabeto = (tipoAlfabeto64) valorArgumento;

    errno = 0;
    valorArgumento = strtol (argv[3], &validacao, 10);

    if (errno != 0 || *validacao != EOS || valorArgumento <= 0) {
        printf ("%sNumero de bytes invalido: %s%s\n", TEXTO_ERRO, argv[3], RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    numeroBytes = (unsigned long long) valorArgumento;

    if ((unsigned long long) (argc - NUMERO_ARGUMENTOS_FIXOS) != numeroBytes) {
        printf ("%sForam informados %d bytes, mas o numero de bytes declarado e %s.%s\n", TEXTO_ERRO, argc - NUMERO_ARGUMENTOS_FIXOS, argv[3], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    /* numero de caracteres da string gerada, acrescido do espaco necessario para os caracteres de final de linha */
    numeroCaracteres = (numeroBytes + NUMERO_BYTES_GRUPO_BASE_64 - 1) / NUMERO_BYTES_GRUPO_BASE_64 * NUMERO_CARACTERES_GRUPO_BASE_64;
    numeroCaracteres += (numeroCaracteres / NUMERO_CARACTERES_MAXIMO_LINHA + 1) * NUMERO_CARACTERES_FINAL_LINHA;

    bytesEntrada = (byte *) malloc ((size_t) numeroBytes);
    stringSaida = (char *) malloc ((size_t) (numeroCaracteres + 1));

    if (bytesEntrada == NULL || stringSaida == NULL) {
        printf ("%sErro na alocacao de memoria.%s\n", TEXTO_ERRO, RESET);
        exit (ERRO_ALOCACAO);
    }

    for (indice = 0; indice < numeroBytes; indice++) {
        errno = 0;
        valorArgumento = strtol (argv[indice + NUMERO_ARGUMENTOS_FIXOS], &validacao, 16);

        if (errno != 0 || *validacao != EOS || valorArgumento < 0 || valorArgumento > VALOR_MAXIMO_BYTE) {
            printf ("%sByte invalido: %s%s\n", TEXTO_ERRO, argv[indice + NUMERO_ARGUMENTOS_FIXOS], RESET);
            free (bytesEntrada);
            free (stringSaida);
            exit (ARGUMENTO_INVALIDO);
        }

        bytesEntrada[indice] = (byte) valorArgumento;
    }

    codigoRetorno = CodificarBase64 (bytesEntrada, numeroBytes, finalLinha, alfabeto, stringSaida);

    if (codigoRetorno != ok) {
        printf ("%sErro na codificacao em Base64 (codigo %d).%s\n", TEXTO_ERRO, codigoRetorno, RESET);
        free (bytesEntrada);
        free (stringSaida);
        exit (ERRO_EXECUCAO);
    }

    printf ("%s>>>>> \"%s%s%s\"%s\n", DESTAQUE, TEXTO_GERADO, stringSaida, DESTAQUE, RESET);

    free (bytesEntrada);
    free (stringSaida);

    return OK;
}

/* $RCSfile$ */
