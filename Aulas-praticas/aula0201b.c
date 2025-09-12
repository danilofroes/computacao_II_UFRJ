/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  Arquivo de implementacao da funcao de calculo do maximo divisor comum (mdc) com laço de repetição do while
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include "aula0201.h"

ull CalcularMaximoDivisorComum(ull x, ull y) {
    ull resto;

    if (y == 0)
        return x;

    else if (x == 0)
        return y;

    do {
        resto = x % y;

        x = y;
        y = resto;
    } 
    while (y != 0);

    return x;
}

 /* $RCSfile$ */