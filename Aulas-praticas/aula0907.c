/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para as funcoes de exibicao e de conversao de arquivos, recebe a opcao curta ou longa desejada atraves da funcao getopt_long e os
 * nomes dos arquivos atraves da funcao getsubopt.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifdef __linux__
  /* a funcao getsubopt somente e declarada a partir da versao 700 do X/Open */
  #define _XOPEN_SOURCE 700
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "aula0901.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define OPCAO_INVALIDA                  2
#define ARGUMENTO_INVALIDO              3
#define ERRO_EXECUCAO                   4

#define EOS                             '\0'

#define OPCOES_CURTAS                   "dDhHsSuU"

#define PALAVRA_CHAVE_ENTRADA           0
#define PALAVRA_CHAVE_SAIDA             1

static struct option opcoesLongas[] = {
    { "dos",  no_argument, NULL, 'd' },
    { "help", no_argument, NULL, 'h' },
    { "show", no_argument, NULL, 's' },
    { "unix", no_argument, NULL, 'u' },
    { NULL,   0,           NULL, 0   }
};

static char *palavrasChave[] = {
    "input",
    "output",
    NULL
};

static void ExibirModoUso(char *nomePrograma);          /* nome do programa em execucao (E) */

int main (int argc, char *argv[]) {
    char *nomeArquivoOriginal;
    char *nomeArquivoConvertido;
    char *subopcoes;
    char *valorSubopcao;
    tipoErros codigoRetorno;
    int opcao;
    int indice;

    /* as mensagens de erro referentes as opcoes sao exibidas pelo proprio programa */
    opterr = 0;

    opcao = getopt_long (argc, argv, OPCOES_CURTAS, opcoesLongas, NULL);

    if (opcao == -1) {
        printf ("%sNenhuma opcao informada.%s\n", RED, RESET);
        ExibirModoUso (argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    if (opcao == '?') {
        printf ("%sOpcao invalida.%s\n", RED, RESET);
        ExibirModoUso (argv[0]);
        exit (OPCAO_INVALIDA);
    }

    if (opcao == 'h' || opcao == 'H') {
        ExibirModoUso (argv[0]);

        return OK;
    }

    nomeArquivoOriginal = NULL;
    nomeArquivoConvertido = NULL;

    /* os nomes dos arquivos sao obtidos, a partir da variavel optind, com a funcao getsubopt */
    for (indice = optind; indice < argc; indice++) {
        subopcoes = argv[indice];

        while (*subopcoes != EOS)
            switch (getsubopt (&subopcoes, palavrasChave, &valorSubopcao)) {
                case PALAVRA_CHAVE_ENTRADA:
                    if (valorSubopcao == NULL) {
                        printf ("%sA palavra-chave input exige o nome do arquivo de entrada.%s\n", RED, RESET);
                        ExibirModoUso (argv[0]);
                        exit (ARGUMENTO_INVALIDO);
                    }

                    nomeArquivoOriginal = valorSubopcao;
                    break;

                case PALAVRA_CHAVE_SAIDA:
                    if (valorSubopcao == NULL) {
                        printf ("%sA palavra-chave output exige o nome do arquivo de saida.%s\n", RED, RESET);
                        ExibirModoUso (argv[0]);
                        exit (ARGUMENTO_INVALIDO);
                    }

                    nomeArquivoConvertido = valorSubopcao;
                    break;

                default:
                    printf ("%sArgumento invalido: %s%s\n", RED, valorSubopcao, RESET);
                    ExibirModoUso (argv[0]);
                    exit (ARGUMENTO_INVALIDO);
            }
    }

    if (nomeArquivoOriginal == NULL) {
        printf ("%sA opcao -%c exige o nome do arquivo de entrada (input=<arquivo>).%s\n", RED, opcao, RESET);
        ExibirModoUso (argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    switch (opcao) {
        case 's':
        case 'S':
            codigoRetorno = ExibirConteudoArquivo (nomeArquivoOriginal);
            break;

        case 'd':
        case 'D':
            codigoRetorno = ConverterArquivoFormatoUnixParaFormatoDos (nomeArquivoOriginal, nomeArquivoConvertido);
            break;

        case 'u':
        case 'U':
            codigoRetorno = ConverterArquivoFormatoDosParaFormatoUnix (nomeArquivoOriginal, nomeArquivoConvertido);
            break;

        default:
            printf ("%sOpcao nao prevista: -%c%s\n", RED, opcao, RESET);
            ExibirModoUso (argv[0]);
            exit (OPCAO_INVALIDA);
    }

    if (codigoRetorno != ok) {
        printf ("%sErro na execucao da opcao -%c sobre o arquivo %s (codigo %d).%s\n", RED, opcao, nomeArquivoOriginal, codigoRetorno, RESET);
        exit (ERRO_EXECUCAO);
    }

    printf ("%sOpcao -%c executada com sucesso sobre o arquivo %s.%s\n", GREEN, opcao, nomeArquivoOriginal, RESET);

    return OK;
}

static void ExibirModoUso (char *nomePrograma /* entrada */) {
    printf ("Uso: %s <opcao> input=<arquivo de entrada> [output=<arquivo de saida>]\n\n", nomePrograma);
    printf ("Opcoes:\n");
    printf ("  -d | -D | --dos     converte um arquivo texto do formato Unix para o formato Microsoft (DOS)\n");
    printf ("  -h | -H | --help    exibe esta mensagem com as informacoes sobre o uso do programa\n");
    printf ("  -s | -S | --show    exibe o conteudo do arquivo\n");
    printf ("  -u | -U | --unix    converte um arquivo texto do formato Microsoft (DOS) para o formato Unix\n\n");
    printf ("Palavras-chave:\n");
    printf ("  input=<arquivo>     nome do arquivo de entrada\n");
    printf ("  output=<arquivo>    nome do arquivo de saida\n\n");
    printf ("Nas opcoes de conversao, se a palavra-chave output nao for informada, o arquivo de entrada\n");
    printf ("e convertido no proprio lugar e preservado em uma copia de backup.\n");
}

/* $RCSfile$ */
