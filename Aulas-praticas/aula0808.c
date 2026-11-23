/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao CodificarBase64, recebe o alfabeto desejado, o nome do arquivo a codificar e o nome do arquivo a ser gerado.
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

#define NUMERO_CARACTERES_FINAL_LINHA   2

#define NUMERO_ARGUMENTOS_ESPERADO      4

#define DESTAQUE                        BOLD_BLACK WHITE_BACKGROUND
#define TEXTO_GERADO                    GREEN WHITE_BACKGROUND
#define TEXTO_ERRO                      RED WHITE_BACKGROUND

int main (int argc, char *argv[]) {
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    byte *bytesEntrada;
    char *stringSaida;
    char *validacao;
    tipoAlfabeto64 alfabeto;
    unsigned long long numeroBytes;
    unsigned long long numeroCaracteres;
    long comprimentoArquivo;
    long valorArgumento;
    tipoErros codigoRetorno;

    if (argc != NUMERO_ARGUMENTOS_ESPERADO) {
        printf ("%sUso: %s <alfabeto (0 - padrao | 1 - seguro)> <arquivo a codificar> <arquivo a gerar>%s\n", TEXTO_ERRO, argv[0], RESET);
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

    /* obtem o comprimento do arquivo a codificar */
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

    numeroBytes = (unsigned long long) comprimentoArquivo;

    /* numero de caracteres da string gerada, acrescido do espaco necessario para os caracteres de final de linha */
    numeroCaracteres = (numeroBytes + NUMERO_BYTES_GRUPO_BASE_64 - 1) / NUMERO_BYTES_GRUPO_BASE_64 * NUMERO_CARACTERES_GRUPO_BASE_64;
    numeroCaracteres += (numeroCaracteres / NUMERO_CARACTERES_MAXIMO_LINHA + 1) * NUMERO_CARACTERES_FINAL_LINHA;

    bytesEntrada = (byte *) malloc ((size_t) numeroBytes);
    stringSaida = (char *) malloc ((size_t) (numeroCaracteres + 1));

    if (bytesEntrada == NULL || stringSaida == NULL) {
        printf ("%sErro na alocacao de memoria.%s\n", TEXTO_ERRO, RESET);
        fclose (arquivoEntrada);
        exit (ERRO_ALOCACAO);
    }

    if (fread (bytesEntrada, 1, (size_t) numeroBytes, arquivoEntrada) != (size_t) numeroBytes) {
        printf ("%sErro na leitura do arquivo %s.%s\n", TEXTO_ERRO, argv[2], RESET);
        fclose (arquivoEntrada);
        free (bytesEntrada);
        free (stringSaida);
        exit (ERRO_ARQUIVO);
    }

    fclose (arquivoEntrada);

    codigoRetorno = CodificarBase64 (bytesEntrada, numeroBytes, habilitado, alfabeto, stringSaida);

    if (codigoRetorno != ok) {
        printf ("%sErro na codificacao em Base64 (codigo %d).%s\n", TEXTO_ERRO, codigoRetorno, RESET);
        free (bytesEntrada);
        free (stringSaida);
        exit (ERRO_EXECUCAO);
    }

    arquivoSaida = fopen (argv[3], "wb");

    if (arquivoSaida == NULL) {
        printf ("%sErro na abertura do arquivo %s.%s\n", TEXTO_ERRO, argv[3], RESET);
        free (bytesEntrada);
        free (stringSaida);
        exit (ERRO_ARQUIVO);
    }

    numeroCaracteres = 0;

    while (stringSaida[numeroCaracteres] != EOS)
        numeroCaracteres++;

    if (fwrite (stringSaida, 1, (size_t) numeroCaracteres, arquivoSaida) != (size_t) numeroCaracteres) {
        printf ("%sErro na escrita do arquivo %s.%s\n", TEXTO_ERRO, argv[3], RESET);
        fclose (arquivoSaida);
        free (bytesEntrada);
        free (stringSaida);
        exit (ERRO_ARQUIVO);
    }

    fclose (arquivoSaida);

    printf ("%s>>>>>%s %s codificado em Base64 e gravado em %s%s\n", DESTAQUE, TEXTO_GERADO, argv[2], argv[3], RESET);

    free (bytesEntrada);
    free (stringSaida);

    return OK;
}

/* $RCSfile$ */
