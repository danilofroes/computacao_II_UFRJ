/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Definicoes de tipos e prototipos das funcoes de codificacao e de decodificacao em Base16, Base32 e Base64, conforme definido no RFC 4648.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA08_
#define _AULA08_ "@(#)aula0801.h $Revision$"

#define NUMERO_BITS_BYTE                    8

#define NUMERO_BYTES_GRUPO_BASE_16          1
#define NUMERO_BYTES_GRUPO_BASE_32          5
#define NUMERO_BYTES_GRUPO_BASE_64          3

#define NUMERO_CARACTERES_GRUPO_BASE_16     2
#define NUMERO_CARACTERES_GRUPO_BASE_32     8
#define NUMERO_CARACTERES_GRUPO_BASE_64     4

#define NUMERO_CARACTERES_MAXIMO_LINHA      76

#define CARACTERE_ENCHIMENTO                '='

#define CARACTERE_RETORNO_CARRO             '\r'
#define CARACTERE_AVANCO_LINHA              '\n'

typedef unsigned char byte;

/* lista enumerada dos codigos de retorno das funcoes */
typedef enum {
    ok,                             /* execucao realizada com sucesso (0) */
    bytesNaoInformados,             /* ponteiro para o conjunto de bytes nao informado (1) */
    stringNaoInformada,             /* ponteiro para a string nao informado (2) */
    numeroBytesNaoInformado,        /* ponteiro para o numero de bytes nao informado (3) */
    numeroBytesInvalido,            /* numero de bytes igual a zero (4) */
    alfabetoInvalido,               /* alfabeto desconhecido (5) */
    indicadorFinalLinhaInvalido,    /* indicador de final de linha desconhecido (6) */
    caractereInvalido,              /* caractere fora do alfabeto da codificacao (7) */
    comprimentoInvalido,            /* comprimento da string incompativel com a codificacao (8) */
    enchimentoInvalido,             /* caracteres de enchimento em quantidade ou posicao invalidas (9) */
    nomeArquivoNaoInformado,        /* nome de arquivo nao informado (10) */
    erroAberturaArquivo,            /* erro na abertura de um dos arquivos (11) */
    erroLeituraArquivo,             /* erro na leitura do arquivo de entrada (12) */
    erroEscritaArquivo,             /* erro na escrita do arquivo de saida (13) */
    erroAlocacaoMemoria             /* erro na alocacao dinamica de memoria (14) */
}
tipoErros;

/* lista enumerada dos alfabetos previstos para a codificacao em Base32 */
typedef enum {
    basico,                         /* alfabeto basico, definido na secao 6 do RFC 4648 (0) */
    estendido                       /* alfabeto estendido (base32hex), definido na secao 7 do RFC 4648 (1) */
}
tipoAlfabetoBase32;

/* lista enumerada da utilizacao dos caracteres de final de linha */
typedef enum {
    desabilitado,                   /* string gerada em uma unica linha (0) */
    habilitado                      /* string gerada com caracteres de final de linha (1) */
}
tipoFinalLinha;

/* lista enumerada dos alfabetos previstos para a codificacao em Base64 */
typedef enum {
    padrao,                         /* alfabeto padrao, definido na secao 4 do RFC 4648 (0) */
    seguro                          /* alfabeto seguro para URLs e para nomes de arquivos, definido na secao 5 do RFC 4648 (1) */
}
tipoAlfabeto64;

typedef tipoAlfabeto64 tipoAlfabetoBase64;

tipoErros CodificarBase16(byte *bytesEntrada,                   /* conjunto de bytes a codificar (E) */
                          unsigned long long numeroBytes,       /* numero de bytes a codificar (E) */
                          char *stringSaida);                   /* string gerada pela codificacao (S) */

tipoErros DecodificarBase16(char *stringEntrada,                /* string a decodificar (E) */
                            byte *bytesSaida,                   /* conjunto de bytes gerado pela decodificacao (S) */
                            unsigned long long *numeroBytes);   /* numero de bytes gerados pela decodificacao (S) */

tipoErros CodificarBase32(byte *bytesEntrada,                   /* conjunto de bytes a codificar (E) */
                          unsigned long long numeroBytes,       /* numero de bytes a codificar (E) */
                          tipoAlfabetoBase32 alfabeto,          /* alfabeto desejado para a codificacao (E) */
                          char *stringSaida);                   /* string gerada pela codificacao (S) */

tipoErros DecodificarBase32(char *stringEntrada,                /* string a decodificar (E) */
                            tipoAlfabetoBase32 alfabeto,        /* alfabeto utilizado na codificacao (E) */
                            byte *bytesSaida,                   /* conjunto de bytes gerado pela decodificacao (S) */
                            unsigned long long *numeroBytes);   /* numero de bytes gerados pela decodificacao (S) */

tipoErros CodificarBase64(byte *bytesEntrada,                   /* conjunto de bytes a codificar (E) */
                          unsigned long long numeroBytes,       /* numero de bytes a codificar (E) */
                          tipoFinalLinha finalLinha,            /* utilizacao dos caracteres de final de linha (E) */
                          tipoAlfabeto64 alfabeto,              /* alfabeto desejado para a codificacao (E) */
                          char *stringSaida);                   /* string gerada pela codificacao (S) */

tipoErros DecodificarBase64(char *stringEntrada,                /* string a decodificar (E) */
                            tipoFinalLinha finalLinha,          /* utilizacao dos caracteres de final de linha (E) */
                            tipoAlfabeto64 alfabeto,            /* alfabeto utilizado na codificacao (E) */
                            byte *bytesSaida,                   /* conjunto de bytes gerado pela decodificacao (S) */
                            unsigned long long *numeroBytes);   /* numero de bytes gerados pela decodificacao (S) */

#endif

/* $RCSfile$ */
