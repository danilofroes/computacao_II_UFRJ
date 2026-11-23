/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Codigo-fonte das funcoes de exibicao do conteudo e de conversao do formato de arquivos do tipo texto.
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
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "aula0901.h"

#define EOS                             '\0'

#define CARACTERE_RETORNO_CARRO         '\r'
#define CARACTERE_AVANCO_LINHA          '\n'

#define FORMATO_DATA_HORA               "%Y%m%d_%H%M%S"

#define SEPARADOR_AREAS                 " | "

/* lista enumerada dos sentidos previstos para a conversao do formato do arquivo */
typedef enum {
    unixParaDos,                        /* substitui cada avanco de linha por um retorno de carro seguido de um avanco de linha (0) */
    dosParaUnix                         /* substitui cada retorno de carro seguido de avanco de linha por um avanco de linha (1) */
}
tipoSentidoConversao;

static tipoErros ConverterArquivo(char *nomeArquivoOriginal,            /* nome do arquivo original (E) */
                                  char *nomeArquivoConvertido,          /* nome do arquivo a gerar (E) */
                                  tipoSentidoConversao sentido);        /* sentido desejado para a conversao (E) */

static tipoErros CopiarConvertendo(FILE *arquivoOriginal,               /* arquivo original, aberto para leitura (E) */
                                   FILE *arquivoConvertido,             /* arquivo a gerar, aberto para escrita (E/S) */
                                   tipoSentidoConversao sentido);       /* sentido desejado para a conversao (E) */

static tipoErros SubstituirArquivoOriginal(char *nomeArquivoOriginal,   /* nome do arquivo original (E) */
                                           char *nomeArquivoTemporario);/* nome do arquivo temporario ja convertido (E) */

static tipoErros ObterDataHora(char *dataHora);                         /* data e hora correntes no formato AAAAMMDD_hhmmss (S) */

tipoErros ExibirConteudoArquivo (char *nomeArquivo /* entrada */) {
    FILE *arquivo;
    byte bytesLinha[NUMERO_BYTES_LINHA];
    unsigned long long offset;
    size_t bytesLidos;
    unsigned indice;

    if (nomeArquivo == NULL)
        return nomeArquivoNaoInformado;

    arquivo = fopen (nomeArquivo, "rb");

    if (arquivo == NULL)
        return erroAberturaArquivoOriginal;

    offset = 0;

    while ((bytesLidos = fread (bytesLinha, 1, NUMERO_BYTES_LINHA, arquivo)) > 0) {
        /* primeira area: offset do primeiro byte exibido na linha */
        printf ("%0*llX", NUMERO_DIGITOS_OFFSET, offset);

        /* segunda area: valores dos bytes em hexadecimal */
        printf (SEPARADOR_AREAS);

        for (indice = 0; indice < NUMERO_BYTES_LINHA; indice++) {
            if (indice > 0)
                printf (" ");

            if (indice < bytesLidos)
                printf ("%02X", bytesLinha[indice]);

            else
                printf ("  ");
        }

        /* terceira area: caracteres correspondentes aos bytes */
        printf (SEPARADOR_AREAS);

        for (indice = 0; indice < bytesLidos; indice++)
            if (bytesLinha[indice] >= PRIMEIRO_CARACTERE_EXIBIVEL && bytesLinha[indice] < ULTIMO_CARACTERE_EXIBIVEL)
                printf ("%c", bytesLinha[indice]);

            else
                printf ("%c", CARACTERE_NAO_EXIBIVEL);

        printf ("\n");

        offset += bytesLidos;
    }

    if (ferror (arquivo) != 0) {
        fclose (arquivo);

        return erroLeituraArquivo;
    }

    fclose (arquivo);

    return ok;
}

tipoErros ConverterArquivoFormatoUnixParaFormatoDos (char *nomeArquivoOriginal /* entrada */, char *nomeArquivoConvertido /* entrada */) {
    return ConverterArquivo (nomeArquivoOriginal, nomeArquivoConvertido, unixParaDos);
}

tipoErros ConverterArquivoFormatoDosParaFormatoUnix (char *nomeArquivoOriginal /* entrada */, char *nomeArquivoConvertido /* entrada */) {
    return ConverterArquivo (nomeArquivoOriginal, nomeArquivoConvertido, dosParaUnix);
}

static tipoErros ConverterArquivo (char *nomeArquivoOriginal /* entrada */, char *nomeArquivoConvertido /* entrada */, tipoSentidoConversao sentido /* entrada */) {
    FILE *arquivoOriginal;
    FILE *arquivoConvertido;
    char *nomeArquivoTemporario;
    tipoErros codigoRetorno;
    int descritorArquivoTemporario;

    if (nomeArquivoOriginal == NULL)
        return nomeArquivoNaoInformado;

    arquivoOriginal = fopen (nomeArquivoOriginal, "rb");

    if (arquivoOriginal == NULL)
        return erroAberturaArquivoOriginal;

    /* o nome do arquivo convertido foi informado: a conversao e gravada diretamente neste arquivo */
    if (nomeArquivoConvertido != NULL) {
        arquivoConvertido = fopen (nomeArquivoConvertido, "wb");

        if (arquivoConvertido == NULL) {
            fclose (arquivoOriginal);

            return erroAberturaArquivoConvertido;
        }

        codigoRetorno = CopiarConvertendo (arquivoOriginal, arquivoConvertido, sentido);

        fclose (arquivoOriginal);

        if (fclose (arquivoConvertido) != 0 && codigoRetorno == ok)
            codigoRetorno = erroEscritaArquivo;

        return codigoRetorno;
    }

    /* o nome do arquivo convertido nao foi informado: a conversao e gravada em um arquivo temporario */
    nomeArquivoTemporario = (char *) malloc (strlen (nomeArquivoOriginal) + strlen (SUFIXO_ARQUIVO_TEMPORARIO) + 1);

    if (nomeArquivoTemporario == NULL) {
        fclose (arquivoOriginal);

        return erroAlocacaoMemoria;
    }

    strcpy (nomeArquivoTemporario, nomeArquivoOriginal);
    strcat (nomeArquivoTemporario, SUFIXO_ARQUIVO_TEMPORARIO);

    descritorArquivoTemporario = mkstemp (nomeArquivoTemporario);

    if (descritorArquivoTemporario == -1) {
        fclose (arquivoOriginal);
        free (nomeArquivoTemporario);

        return erroCriacaoArquivoTemporario;
    }

    arquivoConvertido = fdopen (descritorArquivoTemporario, "wb");

    if (arquivoConvertido == NULL) {
        close (descritorArquivoTemporario);
        remove (nomeArquivoTemporario);
        fclose (arquivoOriginal);
        free (nomeArquivoTemporario);

        return erroCriacaoArquivoTemporario;
    }

    codigoRetorno = CopiarConvertendo (arquivoOriginal, arquivoConvertido, sentido);

    fclose (arquivoOriginal);

    if (fclose (arquivoConvertido) != 0 && codigoRetorno == ok)
        codigoRetorno = erroEscritaArquivo;

    if (codigoRetorno == ok)
        codigoRetorno = SubstituirArquivoOriginal (nomeArquivoOriginal, nomeArquivoTemporario);

    if (codigoRetorno != ok)
        remove (nomeArquivoTemporario);

    free (nomeArquivoTemporario);

    return codigoRetorno;
}

static tipoErros CopiarConvertendo (FILE *arquivoOriginal /* entrada */, FILE *arquivoConvertido /* entrada/saida */, tipoSentidoConversao sentido /* entrada */) {
    int caractereAtual;
    int caractereAnterior;
    int caractereSeguinte;

    caractereAnterior = EOF;

    while ((caractereAtual = getc (arquivoOriginal)) != EOF) {
        if (sentido == unixParaDos) {
            /* o retorno de carro e acrescentado somente se ainda nao estiver presente */
            if (caractereAtual == CARACTERE_AVANCO_LINHA && caractereAnterior != CARACTERE_RETORNO_CARRO)
                if (putc (CARACTERE_RETORNO_CARRO, arquivoConvertido) == EOF)
                    return erroEscritaArquivo;
        }

        else if (caractereAtual == CARACTERE_RETORNO_CARRO) {
            caractereSeguinte = getc (arquivoOriginal);

            /* o retorno de carro e descartado somente quando seguido por um avanco de linha */
            if (caractereSeguinte == CARACTERE_AVANCO_LINHA) {
                if (putc (CARACTERE_AVANCO_LINHA, arquivoConvertido) == EOF)
                    return erroEscritaArquivo;

                caractereAnterior = CARACTERE_AVANCO_LINHA;

                continue;
            }

            if (caractereSeguinte != EOF)
                ungetc (caractereSeguinte, arquivoOriginal);
        }

        if (putc (caractereAtual, arquivoConvertido) == EOF)
            return erroEscritaArquivo;

        caractereAnterior = caractereAtual;
    }

    if (ferror (arquivoOriginal) != 0)
        return erroLeituraArquivo;

    return ok;
}

static tipoErros SubstituirArquivoOriginal (char *nomeArquivoOriginal /* entrada */, char *nomeArquivoTemporario /* entrada */) {
    char *nomeArquivoBackup;
    char dataHora[COMPRIMENTO_DATA_HORA];
    tipoErros codigoRetorno;

    codigoRetorno = ObterDataHora (dataHora);

    if (codigoRetorno != ok)
        return codigoRetorno;

    nomeArquivoBackup = (char *) malloc (strlen (nomeArquivoOriginal) + strlen (SUFIXO_ARQUIVO_BACKUP) + strlen (dataHora) + 1);

    if (nomeArquivoBackup == NULL)
        return erroAlocacaoMemoria;

    strcpy (nomeArquivoBackup, nomeArquivoOriginal);
    strcat (nomeArquivoBackup, SUFIXO_ARQUIVO_BACKUP);
    strcat (nomeArquivoBackup, dataHora);

    remove (nomeArquivoBackup);

    /* o arquivo original e preservado sob o nome de backup */
    if (rename (nomeArquivoOriginal, nomeArquivoBackup) != 0) {
        free (nomeArquivoBackup);

        return erroRenomeacaoArquivo;
    }

    /* o arquivo convertido passa a ocupar o nome do arquivo original */
    if (rename (nomeArquivoTemporario, nomeArquivoOriginal) != 0) {
        rename (nomeArquivoBackup, nomeArquivoOriginal);
        free (nomeArquivoBackup);

        return erroRenomeacaoArquivo;
    }

    free (nomeArquivoBackup);

    return ok;
}

static tipoErros ObterDataHora (char *dataHora /* saida */) {
    time_t instanteAtual;
    struct tm *instanteLocal;

    instanteAtual = time (NULL);

    if (instanteAtual == (time_t) -1)
        return erroObtencaoDataHora;

    instanteLocal = localtime (&instanteAtual);

    if (instanteLocal == NULL)
        return erroObtencaoDataHora;

    if (strftime (dataHora, COMPRIMENTO_DATA_HORA, FORMATO_DATA_HORA, instanteLocal) == 0)
        return erroObtencaoDataHora;

    return ok;
}

/* $RCSfile$ */
