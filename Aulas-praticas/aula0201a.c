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

#include "aula0201.h"

ull CalcularMaximoDivisorComum(ull x, ull y) {
    ull resto = x % y;

    if (resto != 0)
        return CalcularMaximoDivisorComum(y, resto);
    
    else if (resto == 0 || (x == 0 && y != 0))
        return y;
    
    else if (y == 0 && x != 0)
        return x;

    return 0;
}

 /* $RCSfile$ */