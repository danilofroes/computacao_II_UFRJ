/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  arquivo de definicao de funcoes para manipulacao de matrizes de no maximo 100 colunas e 100 linhas
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA0501_
#define _AULA0501_ "@(#)aula0501.h $Revision$"

#define NUMERO_MAXIMO_LINHAS  100
#define NUMERO_MAXIMO_COLUNAS 100

/* lista enumerada de erros */
typedef enum {
    ok,                     /* sem erros (0) */
    numeroMaximoLinhas,     /* erro do numero maximo de linhas (1) */
    numeroMaximoColunas,    /* erro do numero maximo de colunas (2) */
    matrizesIncompativeis   /* erro de matrizes incompatíveis (3) */
} 
tipoErros;

tipoErros ExibirMatriz(unsigned short,                                               /* numero de linhas da matriz (E) */
                       unsigned short,                                               /* numero de colunas da matriz 1 (E) */
                       long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS]);  /* matriz a ser exibida (E) */
                                                                                     /* primeira dimensao - linha */
                                                                                     /* segunda dimensao - coluna */

tipoErros MultiplicarMatrizes(unsigned short,                                               /* numero de linhas da matriz 1 (E) */
                              unsigned short,                                               /* numero de colunas da matriz 1 (E) */
                              unsigned short,                                               /* numero de linhas da matriz 2 (E) */
                              unsigned short,                                               /* numero de colunas da matriz 2 (E) */
                              long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],   /* matriz 1 a ser multiplicada (E) */
                              long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],   /* matriz 2 a ser multiplicada (E) */
                              long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS]);  /* matriz produto (S) */

tipoErros ObterMatrizTransposta(unsigned short,                                               /* numero de linhas da matriz (E) */
                                unsigned short,                                               /* numero de colunas da matriz (E) */
                                long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS],   /* matriz original (E) */
                                long double [NUMERO_MAXIMO_LINHAS] [NUMERO_MAXIMO_COLUNAS]);  /* matriz transposta (S) */

#endif

 /* $RCSfile$ */