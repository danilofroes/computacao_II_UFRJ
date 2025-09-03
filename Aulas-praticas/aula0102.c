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

int main() {
	unsigned int i;

	for (i = 0; i < 256; i++) {
		printf("\e[38;5;%02Xm%3d", i, i);
	}

	printf("\e[0m\n");

	return 0;
}

/* $RCSfile$ */