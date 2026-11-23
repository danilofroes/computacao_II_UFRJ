/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * Definicoes de tipos e prototipos das funcoes de exibicao do conteudo e de conversao do formato de arquivos do tipo texto.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef _AULA0901_
#define _AULA0901_ "@(#)aula0901.h $Revision$"

#define NUMERO_BYTES_LINHA              16

#define NUMERO_DIGITOS_OFFSET           16

#define PRIMEIRO_CARACTERE_EXIBIVEL     0x20
#define ULTIMO_CARACTERE_EXIBIVEL       0x7F

#define CARACTERE_NAO_EXIBIVEL          '.'

#define SUFIXO_ARQUIVO_BACKUP           ".backup-"
#define SUFIXO_ARQUIVO_TEMPORARIO       ".XXXXXX"

#define COMPRIMENTO_DATA_HORA           16

typedef unsigned char byte;

/* lista enumerada dos codigos de retorno das funcoes */
typedef enum {
    ok,                                 /* execucao realizada com sucesso (0) */
    nomeArquivoNaoInformado,            /* nome do arquivo original nao informado (1) */
    erroAberturaArquivoOriginal,        /* erro na abertura do arquivo original (2) */
    erroAberturaArquivoConvertido,      /* erro na abertura ou na criacao do arquivo convertido (3) */
    erroLeituraArquivo,                 /* erro na leitura do arquivo original (4) */
    erroEscritaArquivo,                 /* erro na escrita do arquivo convertido (5) */
    erroCriacaoArquivoTemporario,       /* erro na criacao do arquivo temporario (6) */
    erroRenomeacaoArquivo,              /* erro na renomeacao do arquivo original ou do temporario (7) */
    erroObtencaoDataHora,               /* erro na obtencao da data e da hora correntes (8) */
    erroAlocacaoMemoria                 /* erro na alocacao dinamica de memoria (9) */
}
tipoErros;

tipoErros ExibirConteudoArquivo(char *nomeArquivo);                                      /* nome do arquivo a exibir (E) */

tipoErros ConverterArquivoFormatoUnixParaFormatoDos(char *nomeArquivoOriginal,          /* nome do arquivo original, no formato Unix (E) */
                                                    char *nomeArquivoConvertido);       /* nome do arquivo a gerar, no formato DOS (E) */

tipoErros ConverterArquivoFormatoDosParaFormatoUnix(char *nomeArquivoOriginal,          /* nome do arquivo original, no formato DOS (E) */
                                                    char *nomeArquivoConvertido);       /* nome do arquivo a gerar, no formato Unix (E) */

#endif

/* $RCSfile$ */
