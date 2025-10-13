/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcao para calcular exponencial com for
 *
 * $Author$
 * $Date$
 * $Log$
 */

long double CalcularExponencial(double base, int expoente) {
    long double resultado = 1.0;
    int expoente_modulo;
    unsigned short i;

    if (expoente == 1)
        return base;
    
    if (expoente == 0)
        return 1;

    if (base == 0 && expoente == 0)
        return 1;

    if (base == 0 && expoente < 0)
        return 1.0 / 0.0;

    if (expoente < 0) {
        expoente_modulo = -expoente;
        for(i = 0; i < expoente_modulo; i++) {
            resultado *= base;
        }

        return 1.0 / resultado;
    }

    for (i = 0; i < expoente; i++) {
        resultado *= base;
    }

    return resultado;
}

 /* $RCSfile$ */