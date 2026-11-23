/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao DecodificarBase64, recebe o alfabeto utilizado, o nome do arquivo codificado e o nome do arquivo a ser gerado.
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
#define ERRO_ARQUIVO                    5

#define EOS                             '\0'

#define NUMERO_ARGUMENTOS_ESPERADO      4

#define DESTAQUE                        BOLD_BLACK WHITE_BACKGROUND
#define TEXTO_GERADO                    GREEN WHITE_BACKGROUND
#define TEXTO_ERRO                      RED WHITE_BACKGROUND

int main (int argc, char *argv[]) {
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    char *stringEntrada;
    byte *bytesSaida;
    char *validacao;
    tipoAlfabeto64 alfabeto;
    unsigned long long numeroCaracteres;
    unsigned long long numeroBytes;
    long comprimentoArquivo;
    long valorArgumento;
    tipoErros codigoRetorno;

    if (argc != NUMERO_ARGUMENTOS_ESPERADO) {
        printf ("%sUso: %s <alfabeto (0 - padrao | 1 - seguro)> <arquivo codificado> <arquivo a gerar>%s\n", TEXTO_ERRO, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    valorArgumento = strtol (argv[1], &validacao, 10);

    if (errno != 0 || *validacao != EOS || (valorArgumento != padrao && valorArgumento != seguro)) {
        printf ("%sAlfabeto invalido: %s (0 - padrao | 1 - seguro)%s\n", TEXTO_ERRO, argv[1], RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    alfabeto = (tipoAlfabeto64) valorArgumento;

    arquivoEntrada = fopen (argv[2], "rb");

    if (arquivoEntrada == NULL) {
        printf ("%sErro na abertura do arquivo %s.%s\n", TEXTO_ERRO, argv[2], RESET);
        exit (ERRO_ARQUIVO);
    }

    /* obtem o comprimento do arquivo codificado */
    if (fseek (arquivoEntrada, 0, SEEK_END) != 0) {
        printf ("%sErro no posicionamento no arquivo %s.%s\n", TEXTO_ERRO, argv[2], RESET);
        fclose (arquivoEntrada);
        exit (ERRO_ARQUIVO);
    }

    comprimentoArquivo = ftell (arquivoEntrada);

    if (comprimentoArquivo <= 0) {
        printf ("%sO arquivo %s esta vazio ou nao pode ser medido.%s\n", TEXTO_ERRO, argv[2], RESET);
        fclose (arquivoEntrada);
        exit (ERRO_ARQUIVO);
    }

    rewind (arquivoEntrada);

    numeroCaracteres = (unsigned long long) comprimentoArquivo;

    stringEntrada = (char *) malloc ((size_t) (numeroCaracteres + 1));
    bytesSaida = (byte *) malloc ((size_t) (numeroCaracteres * NUMERO_BYTES_GRUPO_BASE_64 / NUMERO_CARACTERES_GRUPO_BASE_64 + NUMERO_BYTES_GRUPO_BASE_64));

    if (stringEntrada == NULL || bytesSaida == NULL) {
        printf ("%sErro na alocacao de memoria.%s\n", TEXTO_ERRO, RESET);
        fclose (arquivoEntrada);
        exit (ERRO_ALOCACAO);
    }

    if (fread (stringEntrada, 1, (size_t) numeroCaracteres, arquivoEntrada) != (size_t) numeroCaracteres) {
        printf ("%sErro na leitura do arquivo %s.%s\n", TEXTO_ERRO, argv[2], RESET);
        fclose (arquivoEntrada);
        free (stringEntrada);
        free (bytesSaida);
        exit (ERRO_ARQUIVO);
    }

    fclose (arquivoEntrada);

    stringEntrada[numeroCaracteres] = EOS;

    codigoRetorno = DecodificarBase64 (stringEntrada, habilitado, alfabeto, bytesSaida, &numeroBytes);

    if (codigoRetorno != ok) {
        printf ("%sErro na decodificacao em Base64 (codigo %d).%s\n", TEXTO_ERRO, codigoRetorno, RESET);
        free (stringEntrada);
        free (bytesSaida);
        exit (ERRO_EXECUCAO);
    }

    arquivoSaida = fopen (argv[3], "wb");

    if (arquivoSaida == NULL) {
        printf ("%sErro na abertura do arquivo %s.%s\n", TEXTO_ERRO, argv[3], RESET);
        free (stringEntrada);
        free (bytesSaida);
        exit (ERRO_ARQUIVO);
    }

    if (fwrite (bytesSaida, 1, (size_t) numeroBytes, arquivoSaida) != (size_t) numeroBytes) {
        printf ("%sErro na escrita do arquivo %s.%s\n", TEXTO_ERRO, argv[3], RESET);
        fclose (arquivoSaida);
        free (stringEntrada);
        free (bytesSaida);
        exit (ERRO_ARQUIVO);
    }

    fclose (arquivoSaida);

    printf ("%s>>>>>%s %s decodificado de Base64 e gravado em %s%s\n", DESTAQUE, TEXTO_GERADO, argv[2], argv[3], RESET);

    free (stringEntrada);
    free (bytesSaida);

    return OK;
}

/* $RCSfile$ */
