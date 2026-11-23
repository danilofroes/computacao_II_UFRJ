/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  arquivo de definicao de tipos, de macros e de prototipos das funcoes de
 * manipulacao de um monitor (matriz de pixels) e de preenchimento de areas
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA0701_
#define _AULA0701_ "@(#)aula0701.h $Revision$"

#ifdef __linux__
  #ifndef _XOPEN_SOURCE
    #define _XOPEN_SOURCE 600
  #endif
#endif

#include <unistd.h>

#define APAGADO                   ' '
#define ACESO                     ' '
#define DEFEITUOSO                '.'

#define NUMERO_MAXIMO_LINHAS      250
#define NUMERO_MAXIMO_COLUNAS     800
#define NUMERO_MAXIMO_VERTICES    50

/* lista enumerada da utilizacao da cor desejada */
typedef enum {
    fundo,                          /* cor do fundo do caractere (0) */
    texto                           /* cor do proprio caractere (1) */
}
tipoFundoTexto;

/* lista enumerada das situacoes possiveis de cada pixel do monitor */
typedef enum {
    defeituoso = -1,                /* pixel defeituoso (-1) */
    apagado = 0,                    /* pixel apagado (0) */
    aceso = 1                       /* pixel aceso (1) */
}
tipoPixel;

/* lista enumerada dos codigos de retorno das funcoes */
typedef enum {
    ok,                             /* execucao realizada com sucesso (0) */
    numeroLinhasInvalido,           /* numero de linhas fora dos limites (1) */
    numeroColunasInvalido,          /* numero de colunas fora dos limites (2) */
    percentualDefeituososInvalido,  /* percentual de pixels defeituosos fora dos limites (3) */
    percentualApagadosInvalido,     /* percentual de pixels apagados fora dos limites (4) */
    corNaoInformada,                /* nome de cor nao informado (5) */
    coresCoincidentes,              /* cores de fundo, de aceso e de defeituoso iguais (6) */
    linhaInvalida,                  /* linha fora dos limites do monitor (7) */
    colunaInvalida,                 /* coluna fora dos limites do monitor (8) */
    numeroVerticesInvalido,         /* numero de vertices fora dos limites (9) */
    pixelDefeituosoEncontrado,      /* pixel defeituoso encontrado durante o desenho (10) */
    erroLimpezaTela                 /* erro na execucao do comando clear (11) */
}
tipoErros;

char *ObterCodigoAnsiCor(char *nomeCor,                 /* nome da cor desejada (E) */
                         tipoFundoTexto fundoTexto);    /* utilizacao da cor desejada (E) */

tipoErros MostrarMonitor(useconds_t tempoEspera,                                          /* tempo de congelamento da tela em microssegundos (E) */
                         tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],/* monitor a ser exibido (E) */
                                                                                          /* primeira dimensao - linha */
                                                                                          /* segunda dimensao - coluna */
                         unsigned numeroLinhas,                                           /* numero real de linhas do monitor (E) */
                         unsigned numeroColunas,                                          /* numero real de colunas do monitor (E) */
                         char *corFundo,                                                  /* nome da cor dos pixels apagados (E) */
                         char *corPixelAceso,                                             /* nome da cor dos pixels acesos (E) */
                         char *corPixelDefeituoso);                                       /* nome da cor dos pixels defeituosos (E) */

tipoErros GerarDistribuicaoInicial(tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser preenchido (E/S) */
                                   unsigned numeroLinhas,                                     /* numero real de linhas do monitor (E) */
                                   unsigned numeroColunas,                                    /* numero real de colunas do monitor (E) */
                                   float percentualDefeituosos,                               /* percentual de pixels defeituosos (E) */
                                   float percentualApagados);                                 /* percentual de pixels apagados (E) */

tipoErros LimparMonitor(tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS], /* monitor a ser limpo (E/S) */
                        unsigned numeroLinhas,                                            /* numero real de linhas do monitor (E) */
                        unsigned numeroColunas,                                           /* numero real de colunas do monitor (E) */
                        char *corFundo,                                                   /* nome da cor dos pixels apagados (E) */
                        char *corPixelAceso,                                              /* nome da cor dos pixels acesos (E) */
                        char *corPixelDefeituoso);                                        /* nome da cor dos pixels defeituosos (E) */

tipoErros DesenharReta(tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser alterado (E/S) */
                       unsigned numeroLinhas,                                             /* numero real de linhas do monitor (E) */
                       unsigned numeroColunas,                                            /* numero real de colunas do monitor (E) */
                       unsigned linhaA,                                                   /* linha do primeiro vertice da reta (E) */
                       unsigned colunaA,                                                  /* coluna do primeiro vertice da reta (E) */
                       unsigned linhaB,                                                   /* linha do segundo vertice da reta (E) */
                       unsigned colunaB,                                                  /* coluna do segundo vertice da reta (E) */
                       char *corFundo,                                                    /* nome da cor dos pixels apagados (E) */
                       char *corPixelAceso,                                               /* nome da cor dos pixels acesos (E) */
                       char *corPixelDefeituoso);                                         /* nome da cor dos pixels defeituosos (E) */

tipoErros DesenharPoligono(tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser alterado (E/S) */
                           unsigned numeroLinhas,                                         /* numero real de linhas do monitor (E) */
                           unsigned numeroColunas,                                        /* numero real de colunas do monitor (E) */
                           unsigned numeroVertices,                                       /* numero de vertices do poligono (E) */
                           unsigned linhasVertices [NUMERO_MAXIMO_VERTICES],              /* linhas dos vertices do poligono (E) */
                           unsigned colunasVertices [NUMERO_MAXIMO_VERTICES],             /* colunas dos vertices do poligono (E) */
                           char *corFundo,                                                /* nome da cor dos pixels apagados (E) */
                           char *corPixelAceso,                                           /* nome da cor dos pixels acesos (E) */
                           char *corPixelDefeituoso);                                     /* nome da cor dos pixels defeituosos (E) */

tipoErros PreencherPoligono(useconds_t tempoEspera,                                       /* tempo de congelamento da tela em microssegundos (E) */
                            tipoPixel monitor [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],  /* monitor a ser preenchido (E/S) */
                            unsigned numeroLinhas,                                        /* numero real de linhas do monitor (E) */
                            unsigned numeroColunas,                                       /* numero real de colunas do monitor (E) */
                            unsigned linha,                                               /* linha do ponto de partida (E) */
                            unsigned coluna,                                              /* coluna do ponto de partida (E) */
                            char *corFundo,                                               /* nome da cor dos pixels apagados (E) */
                            char *corPixelAceso,                                          /* nome da cor dos pixels acesos (E) */
                            char *corPixelDefeituoso);                                    /* nome da cor dos pixels defeituosos (E) */

#endif

 /* $RCSfile$ */
