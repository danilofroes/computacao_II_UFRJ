/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Definicoes de tipos e prototipos para manipulacao de numeros de cartao de credito.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA0601_
#define _AULA0601_ "@(#)aula0601.h $Revision$"

typedef unsigned char byte;

typedef enum
{
  ok,
  erroComprimentoInvalido
} tipoCodigosRetorno;

typedef enum
{
  mastercard,
  visa13,
  visa14,
  visa15,
  visa16,
  amex,
  diner
} tipoOperadora;

tipoCodigosRetorno GerarDigitoVerificadorCartaoCredito(byte [] /* entrada/saida */);

#endif

/* $RCSfile$ */