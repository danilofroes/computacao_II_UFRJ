/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
*   Codigo para centralizar uma mensagem no terminal
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cores.h"

#define TAMANHO_LINHA 100

#define OK 0
#define NUMERO_ARGUMENTOS_INVALIDO 1
#define VALOR_MAXIMO_CARACTERES_INVALIDO 2

int main(int argc, char *argv[]) {
    unsigned short quantidadeDeCaracteres;
    unsigned short espacosParaCentralizar;
    unsigned short i;
    
    if (argc == 1 || argc > 11) {
        printf("%sO numero de argumentos passado nao e aceito pela funcao%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        exit(NUMERO_ARGUMENTOS_INVALIDO);
    }

    if (argc > 2) {
        unsigned short i;

        for (i = 1; i < argc; i++)
            quantidadeDeCaracteres += strlen(argv[i]);
    }

    else 
        quantidadeDeCaracteres = strlen(argv[1]);
        
    if (quantidadeDeCaracteres > 50) {
        printf("%sO numero de caracteres passado eh maior que 50, que eh o valor aceito pela funcao%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        exit(VALOR_MAXIMO_CARACTERES_INVALIDO);
    }

    if (quantidadeDeCaracteres % 2 == 0)
        espacosParaCentralizar = (TAMANHO_LINHA - (quantidadeDeCaracteres + 2)) / 2;

    else
        espacosParaCentralizar = ((TAMANHO_LINHA - (quantidadeDeCaracteres + 2)) / 2) - 1;
        
    espacosParaCentralizar += (argc - 2);

    for (i = 0; i <= espacosParaCentralizar; i++)
        printf(" ");
        
    printf("\"");
    
    for (i = 1; i < argc; i++) {
        printf("%s", argv[i]);

        if (argc > 2 && i != (argc - 1))
            printf(" ");
    }
    
    printf("\"");

    for (i = 0; i <= espacosParaCentralizar; i++)
        printf(" ");

    printf("\n");

    return OK;
}

 /* $RCSfile$ */