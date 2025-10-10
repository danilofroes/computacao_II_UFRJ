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

#if defined (__FreeBSD__) && defined (__STRICT_ANSI__)
  #define __LONG_LONG_SUPPORTED
#endif

#ifdef __linux__
  #define _XOPEN_SOURCE 600
#endif

#include "aula0301.h"
#include <limits.h>

ull CalcularTermoSerieFibonacci(us termo) {
    ull termoMenosUm;
    ull termoMenosDois;

    if (termo <= 1)
        return termo;

    termoMenosUm = CalcularTermoSerieFibonacci(termo - 1);
    termoMenosDois = CalcularTermoSerieFibonacci(termo - 2);

    if (termoMenosUm == ULLONG_MAX || termoMenosDois == ULLONG_MAX)
        return ULLONG_MAX;

    return termoMenosUm + termoMenosDois;
}

 /* $RCSfile$ */