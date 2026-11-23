/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao ExibirConteudoArquivo, recebe o nome do arquivo cujo conteudo sera exibido.
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

#define NUMERO_ARGUMENTOS_ESPERADO      2

int main (int argc, char *argv[]) {
    tipoErros codigoRetorno;

    if (argc != NUMERO_ARGUMENTOS_ESPERADO) {
        printf ("%sUso: %s <nome do arquivo>%s\n", RED, argv[0], RESET);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    codigoRetorno = ExibirConteudoArquivo (argv[1]);

    if (codigoRetorno != ok) {
        printf ("%sErro na exibicao do conteudo do arquivo %s (codigo %d).%s\n", RED, argv[1], codigoRetorno, RESET);
        exit (ERRO_EXECUCAO);
    }

    printf ("%sConteudo do arquivo %s exibido com sucesso.%s\n", GREEN, argv[1], RESET);

    return OK;
}

/* $RCSfile$ */
