/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  programa de testes para a funcao PreencherPoligono
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
#define VALOR_VERTICES_INVALIDO             7
#define ERRO_GERAR_DISTRIBUICAO_INICIAL     8
#define ERRO_MOSTRAR_MONITOR                9
#define ERRO_LIMPAR_MONITOR                 10
#define ERRO_DESENHAR_POLIGONO              11
#define ERRO_PREENCHER_POLIGONO             12

#define NUMERO_MINIMO_VERTICES              3
#define PRIMEIRO_ARGUMENTO_VERTICES         9
#define NUMERO_ARGUMENTOS_FIXOS             12

#define TEMPO_MAXIMO_CONGELAMENTO           999999

#define EOS                                 '\0'

int main (int argc, char *argv[]) {
    tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
    useconds_t tempoCongelamento;
    unsigned numeroLinhas;
    unsigned numeroColunas;
    float percentualDefeituosos;
    float percentualApagados;
    unsigned linhaPonto;
    unsigned colunaPonto;
    unsigned numeroVertices;
    unsigned linhasVertices[NUMERO_MAXIMO_VERTICES];
    unsigned colunasVertices[NUMERO_MAXIMO_VERTICES];
    unsigned vertice;
    char *validacao;
    long valorInteiro;
    double valorReal;
    tipoErros codigoRetorno;

    if (argc < NUMERO_ARGUMENTOS_FIXOS + 2 * NUMERO_MINIMO_VERTICES) {
        printf ("%s\nUso: %s <tempo-congelamento> <numero-linhas> <numero-colunas> <percentual-defeituosos> <percentual-apagados> <linha-ponto> <coluna-ponto> <numero-vertices> <linha-vertice-1> <coluna-vertice-1> . . . <linha-vertice-N> <coluna-vertice-N> <cor-fundo> <cor-aceso> <cor-defeituoso>%s\n\n", RED, argv[0], RESET);
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
        printf ("%s\nA linha do ponto de partida contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroLinhas) {
        printf ("%s\nValor da linha do ponto de partida invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_LINHAS_INVALIDO);
    }

    linhaPonto = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[7], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nA coluna do ponto de partida contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroColunas) {
        printf ("%s\nValor da coluna do ponto de partida invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_COLUNAS_INVALIDO);
    }

    colunaPonto = (unsigned) valorInteiro;

    errno = 0;
    valorInteiro = strtol (argv[8], &validacao, 10);

    if (*validacao != EOS) {
        printf ("%s\nO numero de vertices contem um caractere invalido (%c).%s\n\n", RED, *validacao, RESET);
        exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
    }

    if (errno == ERANGE || valorInteiro < NUMERO_MINIMO_VERTICES || valorInteiro > NUMERO_MAXIMO_VERTICES) {
        printf ("%s\nValor do numero de vertices invalido ou excedido.%s\n\n", RED, RESET);
        exit (VALOR_VERTICES_INVALIDO);
    }

    numeroVertices = (unsigned) valorInteiro;

    if (argc != NUMERO_ARGUMENTOS_FIXOS + 2 * (int) numeroVertices) {
        printf ("%s\nO numero de coordenadas informadas (%d) nao corresponde ao numero de vertices (%u).%s\n\n", RED, argc - NUMERO_ARGUMENTOS_FIXOS, numeroVertices, RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    for (vertice = 0; vertice < numeroVertices; vertice++) {
        errno = 0;
        valorInteiro = strtol (argv[PRIMEIRO_ARGUMENTO_VERTICES + 2 * vertice], &validacao, 10);

        if (*validacao != EOS) {
            printf ("%s\nA linha do vertice %u contem um caractere invalido (%c).%s\n\n", RED, vertice + 1, *validacao, RESET);
            exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
        }

        if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroLinhas) {
            printf ("%s\nValor da linha do vertice %u invalido ou excedido.%s\n\n", RED, vertice + 1, RESET);
            exit (VALOR_LINHAS_INVALIDO);
        }

        linhasVertices[vertice] = (unsigned) valorInteiro;

        errno = 0;
        valorInteiro = strtol (argv[PRIMEIRO_ARGUMENTO_VERTICES + 2 * vertice + 1], &validacao, 10);

        if (*validacao != EOS) {
            printf ("%s\nA coluna do vertice %u contem um caractere invalido (%c).%s\n\n", RED, vertice + 1, *validacao, RESET);
            exit (ARGUMENTO_COM_CARACTERE_INVALIDO);
        }

        if (errno == ERANGE || valorInteiro < 1 || valorInteiro > (long) numeroColunas) {
            printf ("%s\nValor da coluna do vertice %u invalido ou excedido.%s\n\n", RED, vertice + 1, RESET);
            exit (VALOR_COLUNAS_INVALIDO);
        }

        colunasVertices[vertice] = (unsigned) valorInteiro;
    }

    codigoRetorno = GerarDistribuicaoInicial (monitor, numeroLinhas, numeroColunas, percentualDefeituosos, percentualApagados);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na geracao da distribuicao inicial do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_GERAR_DISTRIBUICAO_INICIAL);
    }

    codigoRetorno = LimparMonitor (monitor, numeroLinhas, numeroColunas, argv[argc - 3], argv[argc - 2], argv[argc - 1]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na limpeza do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_LIMPAR_MONITOR);
    }

    codigoRetorno = DesenharPoligono (monitor, numeroLinhas, numeroColunas, numeroVertices, linhasVertices, colunasVertices, argv[argc - 3], argv[argc - 2], argv[argc - 1]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro no desenho do poligono (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_DESENHAR_POLIGONO);
    }

    codigoRetorno = MostrarMonitor (tempoCongelamento, monitor, numeroLinhas, numeroColunas, argv[argc - 3], argv[argc - 2], argv[argc - 1]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro na exibicao do monitor (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_MOSTRAR_MONITOR);
    }

    codigoRetorno = PreencherPoligono (tempoCongelamento, monitor, numeroLinhas, numeroColunas, linhaPonto, colunaPonto, argv[argc - 3], argv[argc - 2], argv[argc - 1]);

    if (codigoRetorno != ok) {
        printf ("%s\nErro no preenchimento do poligono (codigo %d).%s\n\n", RED, codigoRetorno, RESET);
        exit (ERRO_PREENCHER_POLIGONO);
    }

    return OK;
}

 /* $RCSfile$ */
