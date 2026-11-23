/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Codigo-fonte das funcoes de codificacao e de decodificacao em Base16, Base32 e Base64, conforme definido no RFC 4648.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aula0801.h"

#define EOS                                 '\0'

#define INDICE_NAO_ENCONTRADO               (-1)

#define MASCARA_BASE_16                     0x0F
#define MASCARA_BASE_32                     0x1F
#define MASCARA_BASE_64                     0x3F

/* numero de bits de um grupo completo de cada codificacao */
#define NUMERO_BITS_GRUPO_BASE_32           (NUMERO_BYTES_GRUPO_BASE_32 * NUMERO_BITS_BYTE)
#define NUMERO_BITS_GRUPO_BASE_64           (NUMERO_BYTES_GRUPO_BASE_64 * NUMERO_BITS_BYTE)

/* numero de bits representados por um caractere de cada codificacao */
#define NUMERO_BITS_CARACTERE_BASE_32       5
#define NUMERO_BITS_CARACTERE_BASE_64       6

static char tabelaBase16[] = "0123456789ABCDEF";

static char tabelaBase32Basico[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
static char tabelaBase32Estendido[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

static char tabelaBase64Padrao[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char tabelaBase64Seguro[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static int ObterIndiceCaractere(char caractere,                             /* caractere a procurar no alfabeto (E) */
                                char *alfabeto);                            /* alfabeto da codificacao (E) */

static char *ObterTabelaBase32(tipoAlfabetoBase32 alfabeto);                /* alfabeto desejado (E) */

static char *ObterTabelaBase64(tipoAlfabeto64 alfabeto);                    /* alfabeto desejado (E) */

static tipoErros ValidarEnchimento(char *stringEntrada,                     /* string a validar (E) */
                                   unsigned caracteresGrupo,                /* numero de caracteres de um grupo completo (E) */
                                   unsigned long long *caracteresDados);    /* numero de caracteres anteriores ao enchimento (S) */

tipoErros CodificarBase16 (byte *bytesEntrada /* entrada */, unsigned long long numeroBytes /* entrada */, char *stringSaida /* saida */) {
    unsigned long long indiceByte;
    unsigned long long indiceSaida;

    if (bytesEntrada == NULL)
        return bytesNaoInformados;

    if (stringSaida == NULL)
        return stringNaoInformada;

    if (numeroBytes == 0)
        return numeroBytesInvalido;

    indiceSaida = 0;

    for (indiceByte = 0; indiceByte < numeroBytes; indiceByte++) {
        stringSaida[indiceSaida++] = tabelaBase16[(bytesEntrada[indiceByte] >> NUMERO_BITS_BYTE / 2) & MASCARA_BASE_16];
        stringSaida[indiceSaida++] = tabelaBase16[bytesEntrada[indiceByte] & MASCARA_BASE_16];
    }

    stringSaida[indiceSaida] = EOS;

    return ok;
}

tipoErros DecodificarBase16 (char *stringEntrada /* entrada */, byte *bytesSaida /* saida */, unsigned long long *numeroBytes /* saida */) {
    unsigned long long comprimento;
    unsigned long long indiceEntrada;
    unsigned long long indiceSaida;
    int digitoMaisSignificativo;
    int digitoMenosSignificativo;

    if (stringEntrada == NULL)
        return stringNaoInformada;

    if (bytesSaida == NULL)
        return bytesNaoInformados;

    if (numeroBytes == NULL)
        return numeroBytesNaoInformado;

    comprimento = (unsigned long long) strlen (stringEntrada);

    if (comprimento == 0 || comprimento % NUMERO_CARACTERES_GRUPO_BASE_16 != 0)
        return comprimentoInvalido;

    indiceSaida = 0;

    for (indiceEntrada = 0; indiceEntrada < comprimento; indiceEntrada += NUMERO_CARACTERES_GRUPO_BASE_16) {
        digitoMaisSignificativo = ObterIndiceCaractere (stringEntrada[indiceEntrada], tabelaBase16);
        digitoMenosSignificativo = ObterIndiceCaractere (stringEntrada[indiceEntrada + 1], tabelaBase16);

        if (digitoMaisSignificativo == INDICE_NAO_ENCONTRADO || digitoMenosSignificativo == INDICE_NAO_ENCONTRADO)
            return caractereInvalido;

        bytesSaida[indiceSaida++] = (byte) ((digitoMaisSignificativo << NUMERO_BITS_BYTE / 2) | digitoMenosSignificativo);
    }

    *numeroBytes = indiceSaida;

    return ok;
}

tipoErros CodificarBase32 (byte *bytesEntrada /* entrada */, unsigned long long numeroBytes /* entrada */, tipoAlfabetoBase32 alfabeto /* entrada */, char *stringSaida /* saida */) {
    char *tabela;
    unsigned long long indiceByte;
    unsigned long long indiceSaida;
    unsigned long long acumulador;
    unsigned bytesGrupo;
    unsigned caracteresGrupo;
    unsigned indiceGrupo;

    if (bytesEntrada == NULL)
        return bytesNaoInformados;

    if (stringSaida == NULL)
        return stringNaoInformada;

    if (numeroBytes == 0)
        return numeroBytesInvalido;

    tabela = ObterTabelaBase32 (alfabeto);

    if (tabela == NULL)
        return alfabetoInvalido;

    indiceByte = 0;
    indiceSaida = 0;

    while (indiceByte < numeroBytes) {
        /* monta um grupo de ate 5 bytes (40 bits) completando com zeros os bytes ausentes */
        acumulador = 0;
        bytesGrupo = 0;

        while (bytesGrupo < NUMERO_BYTES_GRUPO_BASE_32 && indiceByte < numeroBytes) {
            acumulador |= ((unsigned long long) bytesEntrada[indiceByte]) << (NUMERO_BITS_GRUPO_BASE_32 - NUMERO_BITS_BYTE * (bytesGrupo + 1));
            bytesGrupo++;
            indiceByte++;
        }

        /* numero de caracteres do grupo que carregam informacao */
        caracteresGrupo = (bytesGrupo * NUMERO_BITS_BYTE + NUMERO_BITS_CARACTERE_BASE_32 - 1) / NUMERO_BITS_CARACTERE_BASE_32;

        for (indiceGrupo = 0; indiceGrupo < NUMERO_CARACTERES_GRUPO_BASE_32; indiceGrupo++)
            if (indiceGrupo < caracteresGrupo)
                stringSaida[indiceSaida++] = tabela[(acumulador >> (NUMERO_BITS_GRUPO_BASE_32 - NUMERO_BITS_CARACTERE_BASE_32 * (indiceGrupo + 1))) & MASCARA_BASE_32];

            else
                stringSaida[indiceSaida++] = CARACTERE_ENCHIMENTO;
    }

    stringSaida[indiceSaida] = EOS;

    return ok;
}

tipoErros DecodificarBase32 (char *stringEntrada /* entrada */, tipoAlfabetoBase32 alfabeto /* entrada */, byte *bytesSaida /* saida */, unsigned long long *numeroBytes /* saida */) {
    char *tabela;
    tipoErros codigoRetorno;
    unsigned long long caracteresDados;
    unsigned long long indiceEntrada;
    unsigned long long indiceSaida;
    unsigned long long acumulador;
    unsigned caracteresGrupo;
    unsigned bytesGrupo;
    unsigned indiceGrupo;
    int indiceCaractere;

    if (stringEntrada == NULL)
        return stringNaoInformada;

    if (bytesSaida == NULL)
        return bytesNaoInformados;

    if (numeroBytes == NULL)
        return numeroBytesNaoInformado;

    tabela = ObterTabelaBase32 (alfabeto);

    if (tabela == NULL)
        return alfabetoInvalido;

    codigoRetorno = ValidarEnchimento (stringEntrada, NUMERO_CARACTERES_GRUPO_BASE_32, &caracteresDados);

    if (codigoRetorno != ok)
        return codigoRetorno;

    /* um grupo incompleto so pode conter 2, 4, 5 ou 7 caracteres de dados */
    caracteresGrupo = (unsigned) (caracteresDados % NUMERO_CARACTERES_GRUPO_BASE_32);

    if (caracteresGrupo == 1 || caracteresGrupo == 3 || caracteresGrupo == 6)
        return comprimentoInvalido;

    indiceEntrada = 0;
    indiceSaida = 0;

    while (indiceEntrada < caracteresDados) {
        acumulador = 0;
        caracteresGrupo = 0;

        while (caracteresGrupo < NUMERO_CARACTERES_GRUPO_BASE_32 && indiceEntrada < caracteresDados) {
            indiceCaractere = ObterIndiceCaractere (stringEntrada[indiceEntrada], tabela);

            if (indiceCaractere == INDICE_NAO_ENCONTRADO)
                return caractereInvalido;

            acumulador |= ((unsigned long long) indiceCaractere) << (NUMERO_BITS_GRUPO_BASE_32 - NUMERO_BITS_CARACTERE_BASE_32 * (caracteresGrupo + 1));
            caracteresGrupo++;
            indiceEntrada++;
        }

        /* numero de bytes completos representados pelos caracteres do grupo */
        bytesGrupo = caracteresGrupo * NUMERO_BITS_CARACTERE_BASE_32 / NUMERO_BITS_BYTE;

        for (indiceGrupo = 0; indiceGrupo < bytesGrupo; indiceGrupo++)
            bytesSaida[indiceSaida++] = (byte) ((acumulador >> (NUMERO_BITS_GRUPO_BASE_32 - NUMERO_BITS_BYTE * (indiceGrupo + 1))) & 0xFF);
    }

    *numeroBytes = indiceSaida;

    return ok;
}

tipoErros CodificarBase64 (byte *bytesEntrada /* entrada */, unsigned long long numeroBytes /* entrada */, tipoFinalLinha finalLinha /* entrada */, tipoAlfabeto64 alfabeto /* entrada */, char *stringSaida /* saida */) {
    char *tabela;
    unsigned long long indiceByte;
    unsigned long long indiceSaida;
    unsigned long long acumulador;
    unsigned caracteresLinha;
    unsigned bytesGrupo;
    unsigned caracteresGrupo;
    unsigned indiceGrupo;

    if (bytesEntrada == NULL)
        return bytesNaoInformados;

    if (stringSaida == NULL)
        return stringNaoInformada;

    if (numeroBytes == 0)
        return numeroBytesInvalido;

    if (finalLinha != desabilitado && finalLinha != habilitado)
        return indicadorFinalLinhaInvalido;

    tabela = ObterTabelaBase64 (alfabeto);

    if (tabela == NULL)
        return alfabetoInvalido;

    indiceByte = 0;
    indiceSaida = 0;
    caracteresLinha = 0;

    while (indiceByte < numeroBytes) {
        /* monta um grupo de ate 3 bytes (24 bits) completando com zeros os bytes ausentes */
        acumulador = 0;
        bytesGrupo = 0;

        while (bytesGrupo < NUMERO_BYTES_GRUPO_BASE_64 && indiceByte < numeroBytes) {
            acumulador |= ((unsigned long long) bytesEntrada[indiceByte]) << (NUMERO_BITS_GRUPO_BASE_64 - NUMERO_BITS_BYTE * (bytesGrupo + 1));
            bytesGrupo++;
            indiceByte++;
        }

        /* numero de caracteres do grupo que carregam informacao */
        caracteresGrupo = (bytesGrupo * NUMERO_BITS_BYTE + NUMERO_BITS_CARACTERE_BASE_64 - 1) / NUMERO_BITS_CARACTERE_BASE_64;

        for (indiceGrupo = 0; indiceGrupo < NUMERO_CARACTERES_GRUPO_BASE_64; indiceGrupo++) {
            /* o final de linha e inserido entre as linhas, sempre que o comprimento maximo e alcancado */
            if (finalLinha == habilitado && caracteresLinha == NUMERO_CARACTERES_MAXIMO_LINHA) {
                stringSaida[indiceSaida++] = CARACTERE_RETORNO_CARRO;
                stringSaida[indiceSaida++] = CARACTERE_AVANCO_LINHA;
                caracteresLinha = 0;
            }

            if (indiceGrupo < caracteresGrupo)
                stringSaida[indiceSaida++] = tabela[(acumulador >> (NUMERO_BITS_GRUPO_BASE_64 - NUMERO_BITS_CARACTERE_BASE_64 * (indiceGrupo + 1))) & MASCARA_BASE_64];

            else
                stringSaida[indiceSaida++] = CARACTERE_ENCHIMENTO;

            caracteresLinha++;
        }
    }

    stringSaida[indiceSaida] = EOS;

    return ok;
}

tipoErros DecodificarBase64 (char *stringEntrada /* entrada */, tipoFinalLinha finalLinha /* entrada */, tipoAlfabeto64 alfabeto /* entrada */, byte *bytesSaida /* saida */, unsigned long long *numeroBytes /* saida */) {
    char *tabela;
    char *stringLimpa;
    tipoErros codigoRetorno;
    unsigned long long comprimento;
    unsigned long long caracteresDados;
    unsigned long long indiceEntrada;
    unsigned long long indiceLimpa;
    unsigned long long indiceSaida;
    unsigned long long acumulador;
    unsigned caracteresGrupo;
    unsigned bytesGrupo;
    unsigned indiceGrupo;
    int indiceCaractere;

    if (stringEntrada == NULL)
        return stringNaoInformada;

    if (bytesSaida == NULL)
        return bytesNaoInformados;

    if (numeroBytes == NULL)
        return numeroBytesNaoInformado;

    if (finalLinha != desabilitado && finalLinha != habilitado)
        return indicadorFinalLinhaInvalido;

    tabela = ObterTabelaBase64 (alfabeto);

    if (tabela == NULL)
        return alfabetoInvalido;

    comprimento = (unsigned long long) strlen (stringEntrada);

    stringLimpa = (char *) malloc ((size_t) comprimento + 1);

    if (stringLimpa == NULL)
        return erroAlocacaoMemoria;

    /* os caracteres de final de linha sao retirados antes da decodificacao */
    indiceLimpa = 0;

    for (indiceEntrada = 0; indiceEntrada < comprimento; indiceEntrada++)
        if (stringEntrada[indiceEntrada] == CARACTERE_RETORNO_CARRO || stringEntrada[indiceEntrada] == CARACTERE_AVANCO_LINHA) {
            if (finalLinha == desabilitado) {
                free (stringLimpa);

                return caractereInvalido;
            }
        }

        else
            stringLimpa[indiceLimpa++] = stringEntrada[indiceEntrada];

    stringLimpa[indiceLimpa] = EOS;

    codigoRetorno = ValidarEnchimento (stringLimpa, NUMERO_CARACTERES_GRUPO_BASE_64, &caracteresDados);

    if (codigoRetorno != ok) {
        free (stringLimpa);

        return codigoRetorno;
    }

    /* um grupo incompleto so pode conter 2 ou 3 caracteres de dados */
    if (caracteresDados % NUMERO_CARACTERES_GRUPO_BASE_64 == 1) {
        free (stringLimpa);

        return comprimentoInvalido;
    }

    indiceEntrada = 0;
    indiceSaida = 0;

    while (indiceEntrada < caracteresDados) {
        acumulador = 0;
        caracteresGrupo = 0;

        while (caracteresGrupo < NUMERO_CARACTERES_GRUPO_BASE_64 && indiceEntrada < caracteresDados) {
            indiceCaractere = ObterIndiceCaractere (stringLimpa[indiceEntrada], tabela);

            if (indiceCaractere == INDICE_NAO_ENCONTRADO) {
                free (stringLimpa);

                return caractereInvalido;
            }

            acumulador |= ((unsigned long long) indiceCaractere) << (NUMERO_BITS_GRUPO_BASE_64 - NUMERO_BITS_CARACTERE_BASE_64 * (caracteresGrupo + 1));
            caracteresGrupo++;
            indiceEntrada++;
        }

        /* numero de bytes completos representados pelos caracteres do grupo */
        bytesGrupo = caracteresGrupo * NUMERO_BITS_CARACTERE_BASE_64 / NUMERO_BITS_BYTE;

        for (indiceGrupo = 0; indiceGrupo < bytesGrupo; indiceGrupo++)
            bytesSaida[indiceSaida++] = (byte) ((acumulador >> (NUMERO_BITS_GRUPO_BASE_64 - NUMERO_BITS_BYTE * (indiceGrupo + 1))) & 0xFF);
    }

    free (stringLimpa);

    *numeroBytes = indiceSaida;

    return ok;
}

static int ObterIndiceCaractere (char caractere /* entrada */, char *alfabeto /* entrada */) {
    int indice;

    for (indice = 0; alfabeto[indice] != EOS; indice++)
        if (alfabeto[indice] == caractere)
            return indice;

    return INDICE_NAO_ENCONTRADO;
}

static char *ObterTabelaBase32 (tipoAlfabetoBase32 alfabeto /* entrada */) {
    switch (alfabeto) {
        case basico:
            return tabelaBase32Basico;

        case estendido:
            return tabelaBase32Estendido;
    }

    return NULL;
}

static char *ObterTabelaBase64 (tipoAlfabeto64 alfabeto /* entrada */) {
    switch (alfabeto) {
        case padrao:
            return tabelaBase64Padrao;

        case seguro:
            return tabelaBase64Seguro;
    }

    return NULL;
}

static tipoErros ValidarEnchimento (char *stringEntrada /* entrada */, unsigned caracteresGrupo /* entrada */, unsigned long long *caracteresDados /* saida */) {
    unsigned long long comprimento;
    unsigned long long indice;

    comprimento = (unsigned long long) strlen (stringEntrada);

    if (comprimento == 0)
        return comprimentoInvalido;

    /* localiza o primeiro caractere de enchimento */
    for (indice = 0; indice < comprimento && stringEntrada[indice] != CARACTERE_ENCHIMENTO; indice++)
        ;

    *caracteresDados = indice;

    if (*caracteresDados == 0)
        return enchimentoInvalido;

    /* a partir do primeiro caractere de enchimento todos os caracteres devem ser de enchimento */
    for (; indice < comprimento; indice++)
        if (stringEntrada[indice] != CARACTERE_ENCHIMENTO)
            return enchimentoInvalido;

    /* se houver enchimento, a string deve conter um numero inteiro de grupos completos */
    if (*caracteresDados < comprimento && comprimento % caracteresGrupo != 0)
        return enchimentoInvalido;

    return ok;
}

/* $RCSfile$ */
