/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  --
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    
    if (argc >= 10) {
        printf("O numero de argumentos passado e maior do que o aceito pelo funcao/n")
        return 1;
    }

    if (strlen(argv[*]) > 50) {
        printf("O numero de caracteres passado e maior que 50, que é o valor aceito pela funcao")
        return 1;
    }

    
}

 /* $RCSfile$ */