/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcao para calcular serie harmonica alternada com recursividade
 *
 * $Author$
 * $Date$
 * $Log$
 */
 
#include "aula0401.h"

float CalcularSerieHarmonicaAlternada(unsigned short int termo) {
    float contaTermo;

    if (termo == 0)
        return 0.0;

    if (termo == 1)
        return 1.0;

    contaTermo = CalcularExponencial(-1, termo - 1) / CalcularExponencial(termo, termo);

    return CalcularSerieHarmonicaAlternada(termo - 1) + contaTermo;
}

 /* $RCSfile$ */