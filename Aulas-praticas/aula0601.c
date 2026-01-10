/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  Implementacao da funcao de geracao de digito verificador para cartoes de credito.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include "aula0601.h"

tipoCodigosRetorno GerarDigitoVerificadorCartaoCredito (byte cartao[] /* entrada/saida */) {
    unsigned short indice;
    unsigned short contador;
    unsigned short soma = 0;
    unsigned short digito;
    unsigned short tamanho = 0;

    while (cartao[tamanho] != 255)
        tamanho++;

    if (tamanho < 12) 
        return erroComprimentoInvalido;

    for (contador = 0; contador < tamanho; contador++) {
        indice = tamanho - 1 - contador;
        digito = cartao[indice];

        if (contador % 2 == 0) {
            digito *= 2;

            if (digito > 9)
                digito -= 9;
        }

        soma += digito;
    }

    if (soma % 10 == 0)
        cartao[tamanho] = 0;
        
    else
        cartao[tamanho] = 10 - (soma % 10);

    return ok;
}

tipoCodigosRetorno ValidarCartaoCredito (byte cartao[] /* entrada */) {
    unsigned short tamanho = 0;
    byte digitoVerificadorFornecido;
    byte digitoVerificadorCalculado;
    tipoCodigosRetorno codigoRetorno;

    while (cartao[tamanho] != 255)
        tamanho++;

    if (tamanho < 13 || tamanho > 16)
        return erroComprimentoInvalido;

    digitoVerificadorFornecido = cartao[tamanho - 1];

    cartao[tamanho - 1] = 255;

    codigoRetorno = GerarDigitoVerificadorCartaoCredito (cartao);

    if (codigoRetorno != ok)
        return codigoRetorno;

    digitoVerificadorCalculado = cartao[tamanho - 1];

    if (digitoVerificadorFornecido == digitoVerificadorCalculado) {
        cartao[tamanho] = 255; 
        return ok;
    }
    
    return erroCartaoInvalido;
}

/* $RCSfile$ */