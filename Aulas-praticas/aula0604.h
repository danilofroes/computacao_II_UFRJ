/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Definicoes de tipos, macros e prototipos para manipulacao de numeros de cartao de credito representados por strings.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA0604_
#define _AULA0604_ "@(#)aula0604.h $Revision$"

#define NUMERO_MINIMO_DIGITOS_CARTAO      13
#define NUMERO_MAXIMO_DIGITOS_CARTAO      16
#define COMPRIMENTO_MAXIMO_NUMERO_CARTAO  20
#define TAMANHO_GRUPO_DIGITOS             4

typedef unsigned char byte;

typedef enum
{
  ok,
  erroPonteiroNaoInformado,
  erroCaractereInvalido,
  erroFormatoInvalido,
  erroComprimentoInvalido,
  erroCartaoInvalido,
  erroOperadoraInvalida
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

tipoCodigosRetorno GerarDigitoVerificadorCartaoCredito(char * /* entrada */, char * /* saida */);

tipoCodigosRetorno ValidarCartaoCredito(char * /* entrada */);

tipoCodigosRetorno GerarNumeroCartaoCredito(tipoOperadora /* entrada */, char * /* saida */);

#endif

/* $RCSfile$ */
