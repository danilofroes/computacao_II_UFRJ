# 👨‍💻 [EEL270] Computação II - Manipulação de Sistemas e Linguagem C ANSI

Este repositório contém o trabalho prático desenvolvido para a disciplina [EEL270] Computação II, ministrada pelo **Prof. Marcelo Luiz Drumond Lanza** na Universidade Federal do Rio de Janeiro (UFRJ). O material reflete a aplicação rigorosa dos padrões de codificação, controle de versão (RCS) e compilação multiplataforma (BSD/Linux) exigidas na matéria.

-----

## 👨‍🏫 Sobre a Disciplina

  * **Ementa:** Introdução aos Sistemas Operacionais da família UNIX, comandos básicos e interface gráfica. Introdução à linguagem HTML. **Linguagem C ANSI**. Ferramentas de desenvolvimento como `make`, `gcc`, `gdb`, e **RCS**. Programação para UNIX.
  * **Professor:** Prof. Marcelo Luiz Drumond Lanza
  * **Período Cursado:** Turma 2025/2
  * **Estrutura do Projeto:** O desenvolvimento segue um modelo estrito de programação multiplataforma, garantindo a compilação e linkedição sob diferentes dialetos C (ANSI, C89, C99, etc.) e compiladores (`gcc` e `clang`) em ambientes FreeBSD e Linux.

-----

## 🛠️ Ferramentas e Padrões de Conformidade

Todos os arquivos são escritos seguindo as seguintes regras obrigatórias da matéria:

  * **Padrões de Nomenclatura:** Estrito uso de *Snake Case* para macros/constantes, *Camel Case* para tipos/variáveis, e *Pascal Case* para funções, com funções começando sempre com um verbo no infinitivo.
  * **Makefiles:** Arquivos `BSDmakefile` e `GNUmakefile` separados, com suporte a seleção de compilador (`cc=CLANG || -DCLANG`) e dialeto (`dialeto=C99 || -DC99`) via linha de comando.
  * **Comentários RCS:** Inclusão obrigatória de `$Author$`, `$Date$`, `$Log$` e `$RCSfile$`.

-----

## 📂 Detalhamento das Aulas Práticas

<details>
<summary><b>Aula Prática 1: Configuração e Tipos de Dados</b></summary>

| Tópicos Abordados | Desafio Principal | Ferramentas C |
| :--- | :--- | :--- |
| Configuração de ambiente UNIX (`screen`, `ssh`). | Aplicação de cores ANSI e manipulação de `sizeof` com alinhamento dinâmico. | `printf` (incluindo cores ANSI), `strlen`, `sizeof`, Operador Ternário. |

#### Arquivos e Funções

| Arquivo | Função / Objetivo | Descrição |
| :--- | :--- | :--- |
| `aula0101.c` | `main` | Exibe as 256 cores ASCII do terminal em notação decimal. |
| `aula0102.c` | `main` | Exibe as 256 cores ASCII em notação **hexadecimal**. |
| `aula0103.c` | `ExibirCabecalho` / `ExibirHifens` | Exibe um cabeçalho de coluna (0 a 9999) com formatação e uma linha de hífens. |
| `aula0104.c` | `main` | Recebe um nome via CLI, junta os argumentos e o exibe **centralizado** em uma tela de 100 colunas. |
| `aula0105.c` | `main` | Exibe os tamanhos (`sizeof`) dos 5 tipos básicos, modificadores de sinal e largura, usando o operador ternário para concordância de "byte/bytes". |
| `aula0106.c` | `main` | Exibe os tamanhos (`sizeof`) das **combinações** válidas de tipos e modificadores. |

</details>

<details>
---
<summary><b>Aula Prática 2: Máximo Divisor Comum (MDC)</b></summary>

| Tópicos Abordados | Desafio Principal | Estruturas |
| :--- | :--- | :--- |
| Implementação do MDC com múltiplas estruturas de controle. | Criação de uma biblioteca estática (`libmatematica-recursao.a`) e seu uso na linkedição. | Recursividade, `do...while`, `for`, `while`. |

#### Arquivos e Funções

| Arquivo | Função / Objetivo | Descrição |
| :--- | :--- | :--- |
| `aula0201.h` | Protótipo `CalcularMaximoDivisorComum` | Define o tipo `ull` e o protótipo da função MDC. |
| `aula0201a.c` | `CalcularMaximoDivisorComum` | Implementação do MDC usando **Recursividade**. |
| `aula0201b.c` | `CalcularMaximoDivisorComum` | Implementação do MDC usando `do...while`. |
| `aula0201c.c` | `CalcularMaximoDivisorComum` | Implementação do MDC usando `for`. |
| `aula0201d.c` | `CalcularMaximoDivisorComum` | Implementação do MDC usando `while`. |
| `aula0202.c` | `main` | Programa de teste que recebe dois números via CLI, exibe o MDC e trata erros (ex: `MDC(0, 0) = 0` - erro). |

</details>

<details>

<summary><b>Aula Prática 3: Série de Fibonacci</b></summary>

| Tópicos Abordados | Desafio Principal | Estruturas |
| :--- | :--- | :--- |
| Implementação da Série de Fibonacci com múltiplas estruturas. | Tratamento de *Overflow* (retorno de `ULLONG_MAX` se $F(n) > \text{ULLONG\_MAX}$). | Recursividade, `do...while`, `for`, `while`. |

#### Arquivos e Funções

| Arquivo | Função / Objetivo | Descrição |
| :--- | :--- | :--- |
| `aula0301.h` | Protótipo `CalcularTermoSerieFibonacci` | Define os tipos `us`, `ull` e o protótipo da função Fibonacci. |
| `aula0301a.c` | `CalcularTermoSerieFibonacci` | Implementação da Série de Fibonacci usando **Recursividade**. |
| `aula0301b.c` | `CalcularTermoSerieFibonacci` | Implementação da Série de Fibonacci usando `do...while`. |
| `aula0301c.c` | `CalcularTermoSerieFibonacci` | Implementação da Série de Fibonacci usando `for`. |
| `aula0301d.c` | `CalcularTermoSerieFibonacci` | Implementação da Série de Fibonacci usando `while`. |
| `aula0302.c` | `main` | Programa de teste que exibe o termo Fibonacci ou mensagens de erro. |

</details>

<details>

<summary><b>Aula Prática 4: Exponencial e Série Harmônica Alternada</b></summary>

| Tópicos Abordados | Desafio Principal | Ferramentas / Estruturas |
| :--- | :--- | :--- |
| Cálculo de Exponencial ($x^n$). | Cálculo da Série Harmônica Alternada $S(n)$ com critério de parada dinâmico baseado no percentual $P$. | Recursividade, `do...while`, `for`, `while`, `strtod`, `strtof`, `fabsf`, `math.h`. |

#### Arquivos e Funções

| Arquivo | Função / Objetivo | Descrição |
| :--- | :--- | :--- |
| `aula0401.h` | Protótipos | Define `CalcularExponencial` e `CalcularSerieHarmonicaAlternada`. |
| `aula0401a.c` a `0401d.c` | `CalcularExponencial` | Implementações do exponencial para recursividade, `do...while`, `for` e `while`, respectivamente. |
| `aula0403a.c` a `0403d.c` | `CalcularSerieHarmonicaAlternada` | Implementações da Série Harmônica Alternada usando as versões correspondentes de `CalcularExponencial` (via bibliotecas estáticas). |
| `aula0403e.c` | `CalcularSerieHarmonicaAlternada` | Implementação da série usando a função `powf` da biblioteca `math.h`. |
| `aula0404.c` | `main` | Programa de teste da série. Recebe percentual $P$ e exibe a série até que $|S(N)-S(N-1)| < P \cdot S(N-1)$. |

</details>
    
<details>

<summary><b>Aula Prática 5: Manipulação e Determinante de Matrizes</b></summary>

| Tópicos Abordados | Desafio Principal | Foco do Cálculo |
| :--- | :--- | :--- |
| Representação e manipulação de Matrizes $100 \times 100$ (alocação estática). | Implementar o cálculo de determinante como um *roteador* para ordens 1, 2, 3 (Sarrus) e $\ge 4$ (Laplace/Recursão). | Determinante de matrizes de ordem 1, 2 e 3. |

#### Arquivos e Funções

| Arquivo | Função / Objetivo | Descrição |
| :--- | :--- | :--- |
| `aula0501.h` | Protótipos | Define as macros `NUMERO_MAXIMO_LINHAS` (100), `tipoErros`, e os protótipos de `ExibirMatriz`, `MultiplicarMatrizes`, `ObterMatrizTransposta`, `CalcularMenorComplementar`, `CalcularComplementoAlgebrico` e `CalcularDeterminanteMatriz`. |
| `aula0501.c` | `ExibirMatriz` | Exibe a matriz formatada com no mínimo 10 casas decimais e barras verdes/negrito. |
| `aula0501.c` | `MultiplicarMatrizes` | Calcula o produto $A \times B$ de matrizes. |
| `aula0501.c` | `ObterMatrizTransposta` | Calcula a matriz transposta. |
| `aula0501.c` | `CalcularDeterminanteMatriz` | Função principal do determinante: implementa logicamente os casos $N=1, 2, 3$ (Sarrus) e roteia para Laplace em $N \ge 4$. |
| `aula0501.c` | `CalcularMenorComplementar` / `CalcularComplementoAlgebrico` | Implementações auxiliares mínimas (apenas `return ok;` ou lógica completa) para suporte ao Teorema de Laplace. |
| `aula0502.c` | `main` | Programa de teste para `ExibirMatriz`. Lê linhas, colunas e elementos, e exibe a matriz. |
| `aula0503.c` | `main` | Programa de teste para `MultiplicarMatrizes`. Lê duas matrizes, calcula o produto e exibe as três matrizes. |
| `aula0504.c` | `main` | Programa de teste para `ObterMatrizTransposta`. Lê a matriz, calcula e exibe a transposta. |
| `aula0505.c` | `main` | Programa de teste para `CalcularDeterminanteMatriz`. Lê a ordem, elementos, exibe a matriz e o determinante (mínimo 5 casas decimais). |
| `aula0506.c` | `main` | Programa de teste para `CalcularMenorComplementar`. Lê ordem, linha/coluna e elementos, exibe a matriz e o **valor** do menor complementar. |

</details>

-----

***Danilo Davi Gomes Fróes***
***Engenharia Eletrônica e de Computação***
