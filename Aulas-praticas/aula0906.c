/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Programa de teste para as funcoes de exibicao e de conversao de arquivos, recebe a opcao curta ou longa desejada atraves da funcao getopt_long.
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
#include <unistd.h>
#include <getopt.h>

#include "aula0901.h"
#include "cores.h"

#define OK                              0
#define NUMERO_ARGUMENTOS_INVALIDO      1
#define OPCAO_INVALIDA                  2
#define ERRO_EXECUCAO                   3

#define OPCOES_CURTAS                   "dDhHsSuU"

static struct option opcoesLongas[] = {
    { "dos",  no_argument, NULL, 'd' },
    { "help", no_argument, NULL, 'h' },
    { "show", no_argument, NULL, 's' },
    { "unix", no_argument, NULL, 'u' },
    { NULL,   0,           NULL, 0   }
};

static void ExibirModoUso(char *nomePrograma);          /* nome do programa em execucao (E) */

int main (int argc, char *argv[]) {
    char *nomeArquivoOriginal;
    char *nomeArquivoConvertido;
    tipoErros codigoRetorno;
    int opcao;

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

    /* as demais opcoes exigem o nome do arquivo de entrada, obtido a partir da variavel optind */
    if (optind >= argc) {
        printf ("%sA opcao -%c exige o nome do arquivo de entrada.%s\n", RED, opcao, RESET);
        ExibirModoUso (argv[0]);
        exit (NUMERO_ARGUMENTOS_INVALIDO);
    }

    nomeArquivoOriginal = argv[optind];

    if (optind + 1 < argc)
        nomeArquivoConvertido = argv[optind + 1];

    else
        nomeArquivoConvertido = NULL;

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
    printf ("Uso: %s <opcao> [arquivo de entrada] [arquivo de saida]\n\n", nomePrograma);
    printf ("Opcoes:\n");
    printf ("  -d | -D | --dos     converte um arquivo texto do formato Unix para o formato Microsoft (DOS)\n");
    printf ("  -h | -H | --help    exibe esta mensagem com as informacoes sobre o uso do programa\n");
    printf ("  -s | -S | --show    exibe o conteudo do arquivo\n");
    printf ("  -u | -U | --unix    converte um arquivo texto do formato Microsoft (DOS) para o formato Unix\n\n");
    printf ("Nas opcoes de conversao, se o arquivo de saida nao for informado, o arquivo de entrada\n");
    printf ("e convertido no proprio lugar e preservado em uma copia de backup.\n");
}

/* $RCSfile$ */
