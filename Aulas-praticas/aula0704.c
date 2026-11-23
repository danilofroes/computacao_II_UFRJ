/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  programa de testes para a funcao DesenharReta
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

#include "aula0701.h"
#include "cores.h"

#define OK                                  0
#define NUMERO_ARGUMENTOS_INVALIDO          1
#define ARGUMENTO_COM_CARACTERE_INVALIDO    2
#define VALOR_TEMPO_INVALIDO                3
#define VALOR_LINHAS_INVALIDO               4
#define VALOR_COLUNAS_INVALIDO              5
#define VALOR_PERCENTUAL_INVALIDO           6
#define ERRO_GERAR_DISTRIBUICAO_INICIAL     7
#define ERRO_MOSTRAR_MONITOR                8
#define ERRO_LIMPAR_MONITOR                 9
#define ERRO_DESENHAR_RETA                  10

#define TEMPO_MAXIMO_CONGELAMENTO           999999

#define EOS                                 '\0'

int main (int argc, char *argv[]) {
    tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    useconds_t tempoCongelamento;
    unsigned numeroLinhas;
    unsigned numeroColunas;
    float percentualDefeituosos;
    float percentualApagados;
    unsigned linhaPontoA;
    unsigned colunaPontoA;
    unsigned linhaPontoB;
    unsigned colunaPontoB;
    char *validacao;
    long valorInteiro;
    double valorReal;
    tipoErros codigoRetorno;

    if (argc != 13) {
        printf ("%s\nUso: %s <tempo-congelamento> <numero-linhas> <numero-colunas> <percentual-defeituosos> <percentual-apagados> <linha-ponto-1> <coluna-ponto-1> <linha-ponto-2> <coluna-ponto-2> <cor-fundo> <cor-aceso> <cor-defeituoso>%s\n\n", RED, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    errno = 0;
    valorInteiro = strtol (argv[1], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nO tempo de congelamento contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 0 || valorInteiro > TEMPO_MAXIMO_CONGELAMENTO) {
        printf ("%s\nValor do tempo de congelamento invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_TEMPO_INVALIDO);
    }

    tempoCongelamento = (useconds_t) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[2], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nO numero de linhas contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > NUMERO_MAXIMO_LINHAS) {
        printf ("%s\nValor do numero de linhas invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_LINHAS_INVALIDO);
    }

    numeroLinhas = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[3], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nO numero de colunas contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > NUMERO_MAXIMO_COLUNAS) {
        printf ("%s\nValor do numero de colunas invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_COLUNAS_INVALIDO);
    }

    numeroColunas = (unsigned) valorInteiro;

    errno = 0;
    valorReal = strtod (argv[4], &validacao);

    if (*validacao != EOS) {
        printf ("%s\nO percentual de pixels defeituosos contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorReal < 0.0 || valorReal > 100.0) {
        printf ("%s\nValor do percentual de pixels defeituosos invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_PERCENTUAL_INVALIDO);
    }

    percentualDefeituosos = (float) valorReal;

    errno = 0;
    valorReal = strtod (argv[5], &validacao);

    if (*validacao != EOS) {
        printf ("%s\nO percentual de pixels apagados contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorReal < 0.0 || valorReal > 100.0) {
        printf ("%s\nValor do percentual de pixels apagados invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_PERCENTUAL_INVALIDO);
    }

    percentualApagados = (float) valorReal;

    errno = 0;
    valorInteiro = strtol (argv[6], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nA linha do ponto 1 contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroLinhas) {
        printf ("%s\nValor da linha do ponto 1 invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_LINHAS_INVALIDO);
    }

    linhaPontoA = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[7], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nA coluna do ponto 1 contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroColunas) {
        printf ("%s\nValor da coluna do ponto 1 invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_COLUNAS_INVALIDO);
    }

    colunaPontoA = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[8], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nA linha do ponto 2 contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroLinhas) {
        printf ("%s\nValor da linha do ponto 2 invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_LINHAS_INVALIDO);
    }

    linhaPontoB = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[9], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nA coluna do ponto 2 contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroColunas) {
        printf ("%s\nValor da coluna do ponto 2 invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_COLUNAS_INVALIDO);
    }

    colunaPontoB = (unsigned) valorInteiro;

    codigoRetorno = GerarDistribuicaoInicial (monitor, numeroLinhas, numeroColunas, percentualDefeituosos, percentualApagados);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na geracao da distribuicao inicial do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_GERAR_DISTRIBUICAO_INICIAL);
    }

    codigoRetorno = MostrarMonitor (tempoCongelamento, monitor, numeroLinhas, numeroColunas, argv[10], argv[11], argv[12]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na exibicao do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_MOSTRAR_MONITOR);
    }

    codigoRetorno = LimparMonitor (monitor, numeroLinhas, numeroColunas, argv[10], argv[11], argv[12]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na limpeza do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_LIMPAR_MONITOR);
    }

    codigoRetorno = DesenharReta (monitor, numeroLinhas, numeroColunas, linhaPontoA, colunaPontoA, linhaPontoB, colunaPontoB, argv[10], argv[11], argv[12]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro no desenho da reta (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_DESENHAR_RETA);
    }

    codigoRetorno = MostrarMonitor (tempoCongelamento, monitor, numeroLinhas, numeroColunas, argv[10], argv[11], argv[12]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na exibicao do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_MOSTRAR_MONITOR);
    }

    return OK;
}

 /* $RCSfile$ */
