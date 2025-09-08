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

int main(int argc, char *argv[]) {
    
    if (argc == 1 || argc > 11) {
        printf("%sO numero de argumentos passado nao e aceito pela funcao%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        return 1;
    }

    unsigned short quantidadeDeCaracteres;

    if (argc > 2) {
        unsigned short i;

        for (i = 1; i < argc; i++)
            quantidadeDeCaracteres += strlen(argv[i]);
    }

    else 
        quantidadeDeCaracteres = strlen(argv[1]);
        
    if (quantidadeDeCaracteres > 50) {
        printf("%sO numero de caracteres passado eh maior que 50, que eh o valor aceito pela funcao%s\n", BOLD_HIGH_INTENSITY_RED, COLOR_RESET);
        return 1;
    }

    unsigned short espacosParaCentralizar;

    if (quantidadeDeCaracteres % 2 == 0)
        espacosParaCentralizar = (TAMANHO_LINHA - (quantidadeDeCaracteres + 2)) / 2;

    else
        espacosParaCentralizar = ((TAMANHO_LINHA - (quantidadeDeCaracteres + 2)) / 2) - 1;
        
    espacosParaCentralizar += (argc - 2);

    unsigned short i;

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

    return 0;
}

 /* $RCSfile$ */