/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcoes para manipulacao de um monitor (matriz de pixels) de no maximo
 * 250 linhas e 800 colunas
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
#include <time.h>

#include "aula0701.h"
#include "cores.h"

/* lista enumerada das operacoes realizadas sobre os pixels de uma reta */
typedef enum {
    verificarPixels,                /* somente procura por pixels defeituosos (0) */
    acenderPixels                   /* acende os pixels correspondentes a reta (1) */
}
tipoOperacaoPixels;

static tipoErros ValidarCores(char *corFundo,                   /* nome da cor dos pixels apagados (E) */
                              char *corPixelAceso,              /* nome da cor dos pixels acesos (E) */
                              char *corPixelDefeituoso);        /* nome da cor dos pixels defeituosos (E) */

static tipoErros PercorrerReta(tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser percorrido (E/S) */
                               unsigned linhaA,                                           /* linha do primeiro vertice da reta (E) */
                               unsigned colunaA,                                          /* coluna do primeiro vertice da reta (E) */
                               unsigned linhaB,                                           /* linha do segundo vertice da reta (E) */
                               unsigned colunaB,                                          /* coluna do segundo vertice da reta (E) */
                               tipoOperacaoPixels operacao);                              /* operacao a ser realizada (E) */

static tipoErros PreencherArea(useconds_t tempoEspera,                                    /* tempo de congelamento da tela em microssegundos (E) */
                               tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser preenchido (E/S) */
                               unsigned numeroLinhas,                                     /* numero real de linhas do monitor (E) */
                               unsigned numeroColunas,                                    /* numero real de colunas do monitor (E) */
                               unsigned linha,                                            /* linha do pixel analisado (E) */
                               unsigned coluna,                                           /* coluna do pixel analisado (E) */
                               char *corFundo,                                            /* nome da cor dos pixels apagados (E) */
                               char *corPixelAceso,                                       /* nome da cor dos pixels acesos (E) */
                               char *corPixelDefeituoso);                                 /* nome da cor dos pixels defeituosos (E) */

char *ObterCodigoAnsiCor (char *nomeCor /* entrada */, tipoFundoTexto fundoTexto /* entrada */) {
    if (nomeCor != NULL) {
        if (fundoTexto == fundo) {
            if (strcmp (nomeCor, "preto") == 0)
                return BLACK_BACKGROUND;

            if (strcmp (nomeCor, "vermelho") == 0)
                return RED_BACKGROUND;

            if (strcmp (nomeCor, "verde") == 0)
                return GREEN_BACKGROUND;

            if (strcmp (nomeCor, "amarelo") == 0)
                return YELLOW_BACKGROUND;

            if (strcmp (nomeCor, "azul") == 0)
                return BLUE_BACKGROUND;

            if (strcmp (nomeCor, "magenta") == 0)
                return MAGENTA_BACKGROUND;

            if (strcmp (nomeCor, "ciano") == 0)
                return CYAN_BACKGROUND;

            if (strcmp (nomeCor, "branco") == 0)
                return WHITE_BACKGROUND;
        }

        else {
            if (strcmp (nomeCor, "preto") == 0)
                return BLACK;

            if (strcmp (nomeCor, "vermelho") == 0)
                return RED;

            if (strcmp (nomeCor, "verde") == 0)
                return GREEN;

            if (strcmp (nomeCor, "amarelo") == 0)
                return YELLOW;

            if (strcmp (nomeCor, "azul") == 0)
                return BLUE;

            if (strcmp (nomeCor, "magenta") == 0)
                return MAGENTA;

            if (strcmp (nomeCor, "ciano") == 0)
                return CYAN;

            if (strcmp (nomeCor, "branco") == 0)
                return WHITE;
        }
    }

    if (fundoTexto == fundo)
        return BLACK_BACKGROUND;

    return WHITE;
}

tipoErros MostrarMonitor (useconds_t tempoEspera /* entrada */, tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    unsigned linha;
    unsigned coluna;
    unsigned contador;
    char *codigoFundoApagado;
    char *codigoFundoAceso;
    char *codigoTextoDefeituoso;
    char *codigoFundoDelimitador;
    char *codigoTextoDelimitador;
    tipoPixel pixelAnterior;
    tipoErros codigoRetorno;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    codigoRetorno = ValidarCores (corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (system ("clear") == -1)
        return erroLimpezaTela;

    codigoFundoApagado = ObterCodigoAnsiCor (corFundo, fundo);
    codigoFundoAceso = ObterCodigoAnsiCor (corPixelAceso, fundo);
    codigoTextoDefeituoso = ObterCodigoAnsiCor (corPixelDefeituoso, texto);
    codigoFundoDelimitador = ObterCodigoAnsiCor (corPixelAceso, fundo);
    codigoTextoDelimitador = ObterCodigoAnsiCor (corFundo, texto);

    printf ("%s%s", codigoTextoDelimitador, codigoFundoDelimitador);

    for (contador = 0; contador < numeroColunas + 4; contador++)
        putchar ('-');

    printf ("%s\n", RESET);

    printf ("%s%s|%s%s", codigoTextoDelimitador, codigoFundoDelimitador, RESET, codigoFundoApagado);

    for (contador = 0; contador < numeroColunas + 2; contador++)
        putchar (APAGADO);

    printf ("%s%s%s|%s\n", RESET, codigoTextoDelimitador, codigoFundoDelimitador, RESET);

    for (linha = 0; linha < numeroLinhas; linha++) {
        printf ("%s%s|%s%s", codigoTextoDelimitador, codigoFundoDelimitador, RESET, codigoFundoApagado);
        putchar (APAGADO);

        pixelAnterior = apagado;

        for (coluna = 0; coluna < numeroColunas; coluna++) {
            if (coluna == 0 || monitor[linha][coluna] != pixelAnterior) {
                if (monitor[linha][coluna] == aceso)
                    printf ("%s", codigoFundoAceso);

                else if (monitor[linha][coluna] == defeituoso)
                    printf ("%s%s", codigoTextoDefeituoso, codigoFundoApagado);

                else
                    printf ("%s", codigoFundoApagado);
            }

            if (monitor[linha][coluna] == aceso)
                putchar (ACESO);

            else if (monitor[linha][coluna] == defeituoso)
                putchar (DEFEITUOSO);

            else
                putchar (APAGADO);

            pixelAnterior = monitor[linha][coluna];
        }

        printf ("%s", codigoFundoApagado);
        putchar (APAGADO);
        printf ("%s%s%s|%s\n", RESET, codigoTextoDelimitador, codigoFundoDelimitador, RESET);
    }

    printf ("%s%s|%s%s", codigoTextoDelimitador, codigoFundoDelimitador, RESET, codigoFundoApagado);

    for (contador = 0; contador < numeroColunas + 2; contador++)
        putchar (APAGADO);

    printf ("%s%s%s|%s\n", RESET, codigoTextoDelimitador, codigoFundoDelimitador, RESET);

    printf ("%s%s", codigoTextoDelimitador, codigoFundoDelimitador);

    for (contador = 0; contador < numeroColunas + 4; contador++)
        putchar ('-');

    printf ("%s\n", RESET);

    fflush (stdout);

    usleep (tempoEspera);

    return ok;
}

tipoErros GerarDistribuicaoInicial (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, float percentualDefeituosos /* entrada */, float percentualApagados /* entrada */) {
    unsigned linha;
    unsigned coluna;
    float sorteio;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    if (percentualDefeituosos < 0.0 || percentualDefeituosos > 100.0)
        return percentualDefeituososInvalido;

    if (percentualApagados < 0.0 || percentualApagados > 100.0)
        return percentualApagadosInvalido;

    srand ((unsigned) time (NULL));

    for (linha = 0; linha < numeroLinhas; linha++) {
        for (coluna = 0; coluna < numeroColunas; coluna++) {
            sorteio = (float) (rand () / (RAND_MAX + 1.0) * 100.0);

            if (sorteio < percentualDefeituosos)
                monitor[linha][coluna] = defeituoso;

            else {
                sorteio = (float) (rand () / (RAND_MAX + 1.0) * 100.0);

                if (sorteio < percentualApagados)
                    monitor[linha][coluna] = apagado;

                else
                    monitor[linha][coluna] = aceso;
            }
        }
    }

    return ok;
}

tipoErros LimparMonitor (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    unsigned linha;
    unsigned coluna;
    tipoErros codigoRetorno;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    codigoRetorno = ValidarCores (corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    for (linha = 0; linha < numeroLinhas; linha++) {
        for (coluna = 0; coluna < numeroColunas; coluna++) {
            if (monitor[linha][coluna] != defeituoso)
                monitor[linha][coluna] = apagado;
        }
    }

    return ok;
}

tipoErros DesenharReta (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, unsigned linhaA /* entrada */, unsigned colunaA /* entrada */, unsigned linhaB /* entrada */, unsigned colunaB /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    tipoErros codigoRetorno;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    codigoRetorno = ValidarCores (corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (linhaA < 1 || linhaA > numeroLinhas || linhaB < 1 || linhaB > numeroLinhas)
        return linhaInvalida;

    if (colunaA < 1 || colunaA > numeroColunas || colunaB < 1 || colunaB > numeroColunas)
        return colunaInvalida;

    codigoRetorno = PercorrerReta (monitor, linhaA, colunaA, linhaB, colunaB, verificarPixels);

    if (codigoRetorno != ok)
        return codigoRetorno;

    return PercorrerReta (monitor, linhaA, colunaA, linhaB, colunaB, acenderPixels);
}

tipoErros DesenharPoligono (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, unsigned numeroVertices /* entrada */, unsigned linhasVertices[NUMERO_MAXIMO_VERTICES] /* entrada */, unsigned colunasVertices[NUMERO_MAXIMO_VERTICES] /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    unsigned vertice;
    unsigned proximoVertice;
    tipoErros codigoRetorno;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    codigoRetorno = ValidarCores (corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (numeroVertices < 3 || numeroVertices > NUMERO_MAXIMO_VERTICES)
        return numeroVerticesInvalido;

    for (vertice = 0; vertice < numeroVertices; vertice++) {
        if (linhasVertices[vertice] < 1 || linhasVertices[vertice] > numeroLinhas)
            return linhaInvalida;

        if (colunasVertices[vertice] < 1 || colunasVertices[vertice] > numeroColunas)
            return colunaInvalida;
    }

    for (vertice = 0; vertice < numeroVertices; vertice++) {
        proximoVertice = (vertice + 1) % numeroVertices;

        codigoRetorno = DesenharReta (monitor, numeroLinhas, numeroColunas, linhasVertices[vertice], colunasVertices[vertice], linhasVertices[proximoVertice], colunasVertices[proximoVertice], corFundo, corPixelAceso, corPixelDefeituoso);

        if (codigoRetorno != ok)
            return codigoRetorno;
    }

    return ok;
}

tipoErros PreencherPoligono (useconds_t tempoEspera /* entrada */, tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, unsigned linha /* entrada */, unsigned coluna /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    tipoErros codigoRetorno;

    if (numeroLinhas < 1 || numeroLinhas > NUMERO_MAXIMO_LINHAS)
        return numeroLinhasInvalido;

    if (numeroColunas < 1 || numeroColunas > NUMERO_MAXIMO_COLUNAS)
        return numeroColunasInvalido;

    codigoRetorno = ValidarCores (corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (linha < 1 || linha > numeroLinhas)
        return linhaInvalida;

    if (coluna < 1 || coluna > numeroColunas)
        return colunaInvalida;

    return PreencherArea (tempoEspera, monitor, numeroLinhas, numeroColunas, linha, coluna, corFundo, corPixelAceso, corPixelDefeituoso);
}

static tipoErros ValidarCores (char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    if (corFundo == NULL || corPixelAceso == NULL || corPixelDefeituoso == NULL)
        return corNaoInformada;

    if (strcmp (corFundo, corPixelAceso) == 0 || strcmp (corFundo, corPixelDefeituoso) == 0 || strcmp (corPixelAceso, corPixelDefeituoso) == 0)
        return coresCoincidentes;

    return ok;
}

static tipoErros PercorrerReta (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned linhaA /* entrada */, unsigned colunaA /* entrada */, unsigned linhaB /* entrada */, unsigned colunaB /* entrada */, tipoOperacaoPixels operacao /* entrada */) {
    int linhaAtual;
    int colunaAtual;
    int variacaoLinhas;
    int variacaoColunas;
    int incrementoLinhas;
    int incrementoColunas;
    int erro;
    int erroDobrado;

    linhaAtual = (int) linhaA;
    colunaAtual = (int) colunaA;

    variacaoLinhas = (int) linhaB - (int) linhaA;

    if (variacaoLinhas < 0)
        variacaoLinhas = -variacaoLinhas;

    variacaoColunas = (int) colunaB - (int) colunaA;

    if (variacaoColunas < 0)
        variacaoColunas = -variacaoColunas;

    if (linhaA < linhaB)
        incrementoLinhas = 1;

    else
        incrementoLinhas = -1;

    if (colunaA < colunaB)
        incrementoColunas = 1;

    else
        incrementoColunas = -1;

    erro = variacaoColunas - variacaoLinhas;

    while (1) {
        if (operacao == verificarPixels) {
            if (monitor[linhaAtual - 1][colunaAtual - 1] == defeituoso)
                return pixelDefeituosoEncontrado;
        }

        else
            monitor[linhaAtual - 1][colunaAtual - 1] = aceso;

        if (linhaAtual == (int) linhaB && colunaAtual == (int) colunaB)
            return ok;

        erroDobrado = 2 * erro;

        if (erroDobrado > -variacaoLinhas) {
            erro -= variacaoLinhas;
            colunaAtual += incrementoColunas;
        }

        if (erroDobrado < variacaoColunas) {
            erro += variacaoColunas;
            linhaAtual += incrementoLinhas;
        }
    }
}

static tipoErros PreencherArea (useconds_t tempoEspera /* entrada */, tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS] /* entrada/saida */, unsigned numeroLinhas /* entrada */, unsigned numeroColunas /* entrada */, unsigned linha /* entrada */, unsigned coluna /* entrada */, char *corFundo /* entrada */, char *corPixelAceso /* entrada */, char *corPixelDefeituoso /* entrada */) {
    tipoErros codigoRetorno;

    if (linha < 1 || linha > numeroLinhas || coluna < 1 || coluna > numeroColunas)
        return ok;

    if (monitor[linha - 1][coluna - 1] == aceso)
        return ok;

    if (monitor[linha - 1][coluna - 1] == defeituoso)
        return pixelDefeituosoEncontrado;

    monitor[linha - 1][coluna - 1] = aceso;

    codigoRetorno = MostrarMonitor (tempoEspera, monitor, numeroLinhas, numeroColunas, corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    codigoRetorno = PreencherArea (tempoEspera, monitor, numeroLinhas, numeroColunas, linha, coluna - 1, corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    codigoRetorno = PreencherArea (tempoEspera, monitor, numeroLinhas, numeroColunas, linha, coluna + 1, corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    codigoRetorno = PreencherArea (tempoEspera, monitor, numeroLinhas, numeroColunas, linha + 1, coluna, corFundo, corPixelAceso, corPixelDefeituoso);

    if (codigoRetorno != ok)
        return codigoRetorno;

    return PreencherArea (tempoEspera, monitor, numeroLinhas, numeroColunas, linha - 1, coluna, corFundo, corPixelAceso, corPixelDefeituoso);
}

 /* $RCSfile$ */
