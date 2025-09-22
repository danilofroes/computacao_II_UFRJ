/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  Arquivo de implementacao da funcao de calculo do termo da seria de fibonacci com recursao
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include "aula0301.h"

ull CalcularTermoSerieFibonacci(us termo) {
    if (termo <= 1)
        return termo;

    return CalcularTermoSerieFibonacci(termo - 1) + CalcularTermoSerieFibonacci(termo - 2);
}

 /* $RCSfile$ */