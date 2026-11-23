/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao ConverterArquivoFormatoDosParaFormatoUnix, recebe o nome do arquivo original e, opcionalmente, o nome do arquivo a gerar.
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

#include "aula0901.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ERRO_EXECUCAO                   3

#define NUMERO_ARGUMENTOS_MINIMO        2
#define NUMERO_ARGUMENTOS_MAXIMO        3

int main (int argc, char *argv[]) {
    char *nomeArquivoConvertido;
    tipoErros codigoRetorno;

    if (argc < NUMERO_ARGUMENTOS_MINIMO || argc > NUMERO_ARGUMENTOS_MAXIMO) {
        printf ("%sUso: %s <arquivo no formato DOS> [arquivo no formato Unix]%s\n", RED, argv[0], RESET);
        printf ("%sSe o arquivo a gerar nao for informado, o arquivo original e convertido no proprio lugar e preservado em uma copia de backup.%s\n", RED, RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    if (argc == NUMERO_ARGUMENTOS_MAXIMO)
        nomeArquivoConvertido = argv[2];

    else
        nomeArquivoConvertido = NULL;

    codigoRetorno = ConverterArquivoFormatoDosParaFormatoUnix (argv[1], nomeArquivoConvertido);

    if (codigoRetorno != ok) {
        printf ("%sErro na conversao do arquivo %s para o formato Unix (codigo %d).%s\n", RED, argv[1], codigoRetorno, RESET);
        exit (ERRO_EXECUCAO);
    }

    if (nomeArquivoConvertido != NULL)
        printf ("%sArquivo %s convertido para o formato Unix em %s.%s\n", GREEN, argv[1], nomeArquivoConvertido, RESET);

    else
        printf ("%sArquivo %s convertido para o formato Unix no proprio lugar.%s\n", GREEN, argv[1], RESET);

    return OK;
}

/* $RCSfile$ */
