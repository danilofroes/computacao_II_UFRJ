/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcao para calcular serie harmonica alternada com for
 *
 * $Author$
 * $Date$
 * $Log$
 */
 
#include "aula0401.h"

float CalcularSerieHarmonicaAlternada(unsigned short int termo) {
    float somaTotal;
    float termoAtual;
    unsigned short contador;

    if (termo == 0)
        return 0.0;

    if (termo == 1)
        return 1.0;

    somaTotal = 0.0;

    for (contador = 1; contador <= termo; contador++) {
        termoAtual = powf(-1, contador - 1) / powf(contador, contador);
        
        somaTotal += termoAtual;
    }

    return somaTotal;
}

 /* $RCSfile$ */