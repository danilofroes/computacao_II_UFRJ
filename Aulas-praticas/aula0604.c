/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Implementacao das funcoes de geracao de digito verificador, de validacao e de geracao de numeros de cartao de credito representados por strings.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifdef __linux__
  #define _XOPEN_SOURCE 600
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aula0604.h"

#define EOS                           '\0'

static tipoCodigosRetorno ExtrairDigitosCartaoCredito(char * /* entrada */, byte [] /* saida */, unsigned short * /* saida */);

tipoCodigosRetorno GerarDigitoVerificadorCartaoCredito (char *numeroCartao /* entrada */, char *digitoVerificador /* saida */) {
    byte digitos[NUMERO_MAXIMO_DIGITOS_CARTAO];
    unsigned short quantidadeDigitos = 0;
    unsigned short contador;
    unsigned short indice;
    unsigned short valorDigito;
    unsigned short soma = 0;
    tipoCodigosRetorno codigoRetorno;

    if (digitoVerificador == NULL)
        return erroPonteiroNaoInformado;

    codigoRetorno = ExtrairDigitosCartaoCredito (numeroCartao, digitos, &quantidadeDigitos);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (quantidadeDigitos < NUMERO_MINIMO_DIGITOS_CARTAO - 1 || quantidadeDigitos > NUMERO_MAXIMO_DIGITOS_CARTAO - 1)
        return erroComprimentoInvalido;

    for (contador = 0; contador < quantidadeDigitos; contador++) {
        indice = quantidadeDigitos - 1 - contador;
        valorDigito = digitos[indice];

        if (contador % 2 == 0) {
            valorDigito *= 2;

            if (valorDigito > 9)
                valorDigito -= 9;
        }

        soma += valorDigito;
    }

    if (soma % 10 == 0)
        digitoVerificador[0] = '0';

    else
        digitoVerificador[0] = (char) ('0' + 10 - (soma % 10));

    digitoVerificador[1] = EOS;

    return ok;
}

tipoCodigosRetorno ValidarCartaoCredito (char *numeroCartao /* entrada */) {
    byte digitos[NUMERO_MAXIMO_DIGITOS_CARTAO];
    char numeroSemDigitoVerificador[NUMERO_MAXIMO_DIGITOS_CARTAO];
    char digitoVerificadorCalculado[2];
    unsigned short quantidadeDigitos = 0;
    unsigned short indice;
    tipoCodigosRetorno codigoRetorno;

    codigoRetorno = ExtrairDigitosCartaoCredito (numeroCartao, digitos, &quantidadeDigitos);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (quantidadeDigitos < NUMERO_MINIMO_DIGITOS_CARTAO || quantidadeDigitos > NUMERO_MAXIMO_DIGITOS_CARTAO)
        return erroComprimentoInvalido;

    for (indice = 0; indice < quantidadeDigitos - 1; indice++)
        numeroSemDigitoVerificador[indice] = (char) ('0' + digitos[indice]);

    numeroSemDigitoVerificador[quantidadeDigitos - 1] = EOS;

    codigoRetorno = GerarDigitoVerificadorCartaoCredito (numeroSemDigitoVerificador, digitoVerificadorCalculado);

    if (codigoRetorno != ok)
        return codigoRetorno;

    if (digitoVerificadorCalculado[0] != (char) ('0' + digitos[quantidadeDigitos - 1]))
        return erroCartaoInvalido;

    return ok;
}

tipoCodigosRetorno GerarNumeroCartaoCredito (tipoOperadora operadora /* entrada */, char *numeroCartao /* saida */) {
    char digitos[NUMERO_MAXIMO_DIGITOS_CARTAO + 1];
    char digitoVerificador[2];
    unsigned short quantidadeDigitos = 0;
    unsigned short quantidadeDigitosPrefixo = 0;
    unsigned short indice;
    unsigned short indiceSaida;
    tipoCodigosRetorno codigoRetorno;

    if (numeroCartao == NULL)
        return erroPonteiroNaoInformado;

    srand ((unsigned) time (NULL));

    switch (operadora) {
        case mastercard:
            quantidadeDigitos = 16;
            quantidadeDigitosPrefixo = 2;
            digitos[0] = '5';
            digitos[1] = (char) ('1' + rand () % 5);
            break;

        case visa13:
            quantidadeDigitos = 13;
            quantidadeDigitosPrefixo = 1;
            digitos[0] = '4';
            break;

        case visa14:
            quantidadeDigitos = 14;
            quantidadeDigitosPrefixo = 1;
            digitos[0] = '4';
            break;

        case visa15:
            quantidadeDigitos = 15;
            quantidadeDigitosPrefixo = 1;
            digitos[0] = '4';
            break;

        case visa16:
            quantidadeDigitos = 16;
            quantidadeDigitosPrefixo = 1;
            digitos[0] = '4';
            break;

        case amex:
            quantidadeDigitos = 15;
            quantidadeDigitosPrefixo = 2;
            digitos[0] = '3';

            if (rand () % 2 == 0)
                digitos[1] = '4';

            else
                digitos[1] = '7';

            break;

        case diner:
            quantidadeDigitos = 14;
            quantidadeDigitosPrefixo = 2;
            digitos[0] = '3';

            if (rand () % 2 == 0)
                digitos[1] = '0';

            else
                digitos[1] = '6';

            break;

        default:
            return erroOperadoraInvalida;
    }

    for (indice = quantidadeDigitosPrefixo; indice < quantidadeDigitos - 1; indice++)
        digitos[indice] = (char) ('0' + rand () % 10);

    digitos[quantidadeDigitos - 1] = EOS;

    codigoRetorno = GerarDigitoVerificadorCartaoCredito (digitos, digitoVerificador);

    if (codigoRetorno != ok)
        return codigoRetorno;

    digitos[quantidadeDigitos - 1] = digitoVerificador[0];
    digitos[quantidadeDigitos] = EOS;

    indiceSaida = 0;

    for (indice = 0; indice < quantidadeDigitos; indice++) {
        if (indice > 0 && indice % TAMANHO_GRUPO_DIGITOS == 0) {
            numeroCartao[indiceSaida] = ' ';
            indiceSaida++;
        }

        numeroCartao[indiceSaida] = digitos[indice];
        indiceSaida++;
    }

    numeroCartao[indiceSaida] = EOS;

    return ok;
}

static tipoCodigosRetorno ExtrairDigitosCartaoCredito (char *numeroCartao /* entrada */, byte digitos[] /* saida */, unsigned short *quantidadeDigitos /* saida */) {
    unsigned short indice = 0;
    unsigned short quantidade = 0;
    unsigned short digitosNoGrupo = 0;

    if (numeroCartao == NULL)
        return erroPonteiroNaoInformado;

    while (numeroCartao[indice] != EOS) {
        if (numeroCartao[indice] == ' ') {
            if (digitosNoGrupo != TAMANHO_GRUPO_DIGITOS)
                return erroFormatoInvalido;

            digitosNoGrupo = 0;
            indice++;
            continue;
        }

        if (numeroCartao[indice] < '0' || numeroCartao[indice] > '9')
            return erroCaractereInvalido;

        if (quantidade >= NUMERO_MAXIMO_DIGITOS_CARTAO)
            return erroComprimentoInvalido;

        digitos[quantidade] = (byte) (numeroCartao[indice] - '0');
        quantidade++;
        digitosNoGrupo++;
        indice++;
    }

    if (digitosNoGrupo == 0)
        return erroFormatoInvalido;

    *quantidadeDigitos = quantidade;

    return ok;
}

/* $RCSfile$ */
