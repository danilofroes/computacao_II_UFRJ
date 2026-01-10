/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para a funcao de gerar digito verificador do cartao, recebe os digitos como um unico argumento de linha de comando.
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
#include "aula0601.h"

#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define ARGUMENTO_INVALIDO              2
#define ERRO_EXECUCAO                   3

#define EOS                           '\0'

int main (int argc, char *argv[]) {
    byte cartao[20]; 
    unsigned short indice;
    unsigned short tamanho;
    char *stringEntrada;

    if (argc != 2) {
        printf ("Uso: %s <digitos_cartao>\n", argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    stringEntrada = argv[1];
    tamanho = strlen(stringEntrada);

    if (tamanho < 12 || tamanho > 15) {
        printf ("%sErro: O numero de digitos deve ser entre 12 e 15.%s\n", RED, RESET);
        exit (ARGUMENTO_INVALIDO);
    }

    for (indice = 0; indice < tamanho; indice++) {
        if (stringEntrada[indice] < '0' || stringEntrada[indice] > '9') {
        printf ("%sErro: Caractere invalido encontrado '%c'.%s\n", RED, stringEntrada[indice], RESET);
        exit (ARGUMENTO_INVALIDO);
        }
        
        cartao[indice] = (byte) (stringEntrada[indice] - '0');
    }

    cartao[tamanho] = 255;

    if (GerarDigitoVerificadorCartaoCredito (cartao) != ok) {
        printf ("%sErro na geracao do digito verificador.%s\n", RED, RESET);
        exit (ERRO_EXECUCAO);
    }

    printf ("Cartao: ");
    for (indice = 0; indice <= tamanho; indice++) {
        printf ("%d", cartao[indice]);
        
        if ((indice + 1) % 4 == 0 && indice != tamanho)
        printf (" ");
    }
    printf ("\n");

    return OK;
}

/* $RCSfile$ */