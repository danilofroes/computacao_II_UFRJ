/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2025/2
 * Prof. Marcelo Luiz Drumond Lanza
 * Autor: Danilo Davi Gomes Froes
 *
 * Descricao:
 * 	  funcao para calcular exponencial com do...while
 *
 * $Author$
 * $Date$
 * $Log$
 */

long double CalcularExponencial(double base, int expoente) {
    long double resultado = 1.0;
    int expoente_modulo;

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
        do {
            resultado *= base;
            expoente_modulo--;
        } while (expoente_modulo > 0);

        return 1.0 / resultado;
    }

    do {
        resultado *= base;
        expoente--;
    } while (expoente > 0);

    return resultado;
}

 /* $RCSfile$ */