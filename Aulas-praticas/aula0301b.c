/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  Arquivo de implementacao da funcao de calculo do termo da serie de fibonacci com do...while
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
    ull termoAnterior;
    ull termoAtual;
    ull proximoTermo;
    us contador;
    ull *ptrAnterior = &termoAnterior;
    ull *ptrAtual = &termoAtual;
    ull *ptrProximo = &proximoTermo;

    if (termo <= 1)
        return termo;

    termoAnterior = 0;
    termoAtual = 1;
    contador = 1;

    do {
        if (ULLONG_MAX - *ptrAtual < *ptrAnterior)
            return ULLONG_MAX;

        *ptrProximo = *ptrAtual + *ptrAnterior;

        *ptrAnterior = *ptrAtual;
        *ptrAtual = *ptrProximo;

        contador++;
    } while (contador < termo);

    return *ptrAtual;
}

 /* $RCSfile$ */