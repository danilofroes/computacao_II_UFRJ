/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	Exibir as 256 cores possiveis em um terminal com o código hexadecimal.
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>

#define OK 0

int main() {
	unsigned int contador;

	for (contador = 0; contador < 256; contador++) {
		printf("\e[38;5;%dm", contador);
		printf(" %02X", contador);
	}

	printf("\e[0m\n");

	return OK;
}

/* $RCSfile$ */