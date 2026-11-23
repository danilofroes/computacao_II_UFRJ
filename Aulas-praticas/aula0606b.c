/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao ValidarCartaoCredito (versao com strings), recebe os digitos como um unico argumento de linha de comando.
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

#include "aula0604.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define EOS                           '\0'

int main (int argc, char *argv[]) {
    char *numeroCartao;
    unsigned short indice;
    unsigned short totalDigitos = 0;
    tipoCodigosRetorno codigoRetorno;

    if (argc != 2) {
        printf ("%sUso: %s <\"digitos do cartao\">%s\n", RED, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    numeroCartao = argv[1];

    codigoRetorno = ValidarCartaoCredito (numeroCartao);

    if (codigoRetorno == erroCaractereInvalido || codigoRetorno == erroFormatoInvalido || codigoRetorno == erroComprimentoInvalido) {
        printf ("%sArgumento invalido: %s (codigo %d).%s\n", RED, numeroCartao, codigoRetorno, RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    printf ("Cartao: ");

    for (indice = 0; numeroCartao[indice] != EOS; indice++) {
        if (numeroCartao[indice] == ' ')
            continue;

        if (totalDigitos > 0 && totalDigitos % TAMANHO_GRUPO_DIGITOS == 0)
            printf (" ");

        printf ("%c", numeroCartao[indice]);
        totalDigitos++;
    }

    if (codigoRetorno == ok)
        printf (" - valido\n");

    else if (codigoRetorno == erroCartaoInvalido)
        printf (" - invalido\n");

    else {
        printf (" - erro de execucao (codigo %d)\n", codigoRetorno);
        exit (ERRO_EXECUCAO);
    }

    return OK;
}

/* $RCSfile$ */
