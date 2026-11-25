# Linguagem Aurora: como funciona

Trabalho de Compiladores. A linguagem **Aurora** foi criada com **Flex** (analisador
léxico) e **Bison** (analisador sintático). É uma linguagem estruturada, com tipos,
inspirada no português:

- tem início e fim de programa bem definidos (`programa Nome { ... }`);
- variáveis têm tipo (`inteiro`, `real`, `logico`, `texto`) e escopo de bloco;
- tem operações matemáticas, relacionais e lógicas com precedência;
- tem decisão (`se` / `senao se` / `senao`) e repetição (`enquanto`, `para`);
- tem funções com parâmetros, valor de retorno e recursão;
- tem entrada (`leia`) e saída (`escreva`);
- o compilador verifica os tipos e mostra mensagens de erro claras, com o número da linha.

---

## 1. Exemplo rápido

```
programa Exemplo {

    funcao fatorial(n: inteiro): inteiro {
        se (n <= 1) {
            retorne 1;
        }
        retorne n * fatorial(n - 1);
    }

    inicio {
        seja a: inteiro = 17;
        seja b: inteiro = 5;
        seja media: real = (a + b) / 2.0;

        escreva("a + b =", a + b);
        escreva("media =", media);
        escreva("5! =", fatorial(5));
    }
}
```

Saída:

```
a + b = 22
media = 11.0
5! = 120
```

---

## 2. Como compilar e executar

### Linux

```sh
make                 # roda bison, flex e gcc
make executar        # executa codigo_para_executar.txt
make arvore          # executa mostrando a árvore sintática
make testar          # roda os testes automáticos
```

Sem o Makefile, os comandos são estes:

```sh
bison -d -o gerados/sintatico.tab.c src/sintatico.y   # gera sintatico.tab.c e .tab.h
flex -o gerados/lex.yy.c src/lexico.l                 # gera lex.yy.c
gcc -Isrc -Igerados -o aurora gerados/*.c src/*.c -lm
./aurora codigo_para_executar.txt
```

Pacotes necessários no Ubuntu/Debian: `sudo apt install flex bison gcc make`.

### Windows

Com o WinFlexBison e o gcc (MinGW) instalados:

```
compilar.bat                 gera os arquivos, compila e roda o exemplo
compilar.bat testar          gera os arquivos, compila e roda os testes
aurora.exe <arquivo>         executa qualquer programa Aurora
```

### Sem Flex e Bison instalados

Os arquivos da pasta `gerados/` já vêm prontos. Então dá para compilar só com o gcc:

```sh
gcc -Isrc -Igerados -o aurora gerados/*.c src/*.c -lm
```

### Opções do executável

```
aurora <arquivo>             analisa e executa
aurora --arvore <arquivo>    mostra a árvore sintática antes de executar
```

---

## 3. Visão geral do compilador

O código-fonte passa por quatro etapas:

```
 código-fonte (.txt)
        │
        ▼
 ┌──────────────────────┐
 │ 1. Análise LÉXICA    │  lexico.l (Flex)
 │   texto → tokens     │  ignora espaços e comentários
 └──────────────────────┘
        │  tokens: SEJA ID ':' TIPO_INTEIRO '=' LIT_INTEIRO ';' ...
        ▼
 ┌──────────────────────┐
 │ 2. Análise SINTÁTICA │  sintatico.y (Bison)
 │   tokens → árvore    │  confere a gramática e monta a árvore
 └──────────────────────┘
        │  cada regra reconhecida chama o módulo semântico
        ▼
 ┌──────────────────────┐
 │ 3. Análise SEMÂNTICA │  semantico.c + tabela.c
 │   confere significado│  declarações, tipos, escopos, argumentos
 └──────────────────────┘
        │  árvore completa e com os tipos verificados
        ▼
 ┌──────────────────────┐
 │ 4. INTERPRETAÇÃO     │  interpretador.c
 │   executa a árvore   │  calcula expressões e executa comandos
 └──────────────────────┘
```

As etapas 2 e 3 acontecem **juntas**. Quando o Bison reconhece uma regra (por
exemplo, uma soma), a ação dessa regra chama o módulo semântico, que confere os
tipos e devolve o nó da árvore já pronto. Por isso o programa só começa a
executar depois que **todo** o código foi verificado. Um erro na linha 50
impede a execução da linha 1.

---

## 4. Organização dos arquivos

```
Trabalho_Compiladores_Aurora/
├── LEIA-ME.txt                 resumo da entrega e de como compilar
├── Documentacao_Linguagem_Aurora.pdf   esta documentação
├── codigo_para_executar.txt    programa de demonstração (comentado)
├── Makefile                    compilação no Linux
├── compilar.bat                compilação no Windows
│
├── src/                        código escrito à mão
│   ├── lexico.l                  Flex: analisador léxico
│   ├── sintatico.y               Bison: gramática e analisador sintático
│   ├── aurora.h                  declarações compartilhadas por todos os módulos
│   ├── ast.c                     árvore sintática
│   ├── tabela.c                  tabela de símbolos e escopos
│   ├── semantico.c               verificação de tipos e declarações
│   ├── interpretador.c           execução da árvore
│   └── main.c                    ponto de entrada e mensagens de erro
│
├── gerados/                    produzidos pelo Flex e pelo Bison
│   ├── lex.yy.c                  (flex)
│   ├── sintatico.tab.c           (bison)
│   └── sintatico.tab.h           (bison: códigos dos tokens)
│
└── testes/                     testes automáticos
    ├── corretos.txt              programas que devem funcionar
    ├── erros.txt                 programas com erros propositais
    ├── testar.sh                 roda os testes no Linux
    └── testar.ps1                roda os testes no Windows
```

| Arquivo | Papel |
|---|---|
| `src/lexico.l` | **Flex.** Expressões regulares que reconhecem os tokens. |
| `src/sintatico.y` | **Bison.** Tokens, precedência dos operadores, gramática e mensagens de erro sintático. |
| `src/aurora.h` | Todas as estruturas e funções compartilhadas, em seções: tipos, erros, árvore, tabela de símbolos, semântica e interpretador. |
| `src/ast.c` | **Árvore sintática**: criação dos nós e impressão (`--arvore`). |
| `src/tabela.c` | **Tabela de símbolos**: funções, parâmetros, variáveis e escopos. |
| `src/semantico.c` | **Análise semântica**: regras de tipos e de declaração. |
| `src/interpretador.c` | **Execução** da árvore. |
| `src/main.c` | Abre o arquivo, chama o analisador e depois o interpretador. Também contém as funções de erro. |
| `gerados/` | Arquivos produzidos pelo Bison (`sintatico.tab.c/.h`) e pelo Flex (`lex.yy.c`). Não devem ser editados à mão. |

Todos os arquivos de código, inclusive os programas em Aurora, estão comentados.

---

## 5. Análise léxica (`lexico.l`)

O Flex lê o texto e o quebra em **tokens**. Exemplo:

```
seja x: inteiro = 10;
```

vira

```
SEJA   ID("x")   ':'   TIPO_INTEIRO   '='   LIT_INTEIRO(10)   ';'
```

### Tokens da linguagem

| Categoria | Lexemas |
|---|---|
| Estrutura | `programa` `inicio` `funcao` `retorne` |
| Declaração e tipos | `seja` `inteiro` `real` `logico` `texto` |
| Entrada/saída | `escreva` `leia` |
| Decisão | `se` `senao` |
| Repetição | `enquanto` `para` `de` `ate` `passo` |
| Lógicos | `e` `ou` `nao` `verdadeiro` `falso` |
| Relacionais | `==` `!=` `<` `<=` `>` `>=` |
| Aritméticos | `+` `-` `*` `/` `%` `^` |
| Pontuação | `=` `(` `)` `{` `}` `,` `;` `:` |
| Número inteiro | `[0-9]+` → ex.: `42` |
| Número real | `[0-9]+.[0-9]+` → ex.: `3.14` |
| Texto | `"..."`, aceitando `\n`, `\t`, `\"` e `\\` |
| Identificador | `[a-zA-Z_][a-zA-Z0-9_]*` → ex.: `total_vendas` |

O analisador também:

- **ignora** espaços, tabulações, quebras de linha e comentários (`// linha` e `/* bloco */`);
- **conta as linhas** (`%option yylineno`) e informa a linha de cada token ao Bison
  (`yylloc`), para que as mensagens de erro apontem a linha certa;
- dá **erro léxico** para símbolo desconhecido (ex.: `@`), texto sem as aspas de
  fechamento e comentário de bloco que nunca é fechado.

> As palavras reservadas vêm **antes** da regra de identificador no arquivo. Quando
> duas regras reconhecem o mesmo texto, o Flex escolhe a primeira, e é assim que
> `se` vira o token `SE` e não um identificador.

---

## 6. Análise sintática (`sintatico.y`)

### 6.1 Gramática (BNF)

Símbolos **não terminais** em minúsculas; **terminais** em MAIÚSCULAS ou entre aspas.

```
programa            → PROGRAMA ID '{' lista_funcoes bloco_principal '}'

lista_funcoes       → ε
                    | lista_funcoes funcao

bloco_principal     → INICIO bloco

funcao              → FUNCAO ID '(' parametros_opcionais ')' retorno_opcional bloco
parametros_opcionais→ ε | lista_parametros
lista_parametros    → parametro | lista_parametros ',' parametro
parametro           → ID ':' tipo
retorno_opcional    → ε | ':' tipo
tipo                → INTEIRO | REAL | LOGICO | TEXTO

bloco               → '{' lista_comandos '}'
lista_comandos      → ε | lista_comandos comando

comando             → declaracao ';'
                    | atribuicao ';'
                    | escrita ';'
                    | leitura ';'
                    | chamada_comando ';'
                    | retorno ';'
                    | condicional
                    | repeticao_enquanto
                    | repeticao_para

declaracao          → SEJA ID ':' tipo
                    | SEJA ID ':' tipo '=' expressao
atribuicao          → ID '=' expressao
escrita             → ESCREVA '(' lista_argumentos ')'
leitura             → LEIA '(' ID ')'
chamada_comando     → ID '(' argumentos_opcionais ')'
retorno             → RETORNE expressao | RETORNE

condicional         → SE '(' expressao ')' bloco senao_opcional
senao_opcional      → ε | SENAO bloco | SENAO condicional

repeticao_enquanto  → ENQUANTO '(' expressao ')' bloco
repeticao_para      → PARA ID DE expressao ATE expressao passo_opcional bloco
passo_opcional      → ε | PASSO expressao

expressao           → LIT_INTEIRO | LIT_REAL | LIT_TEXTO | VERDADEIRO | FALSO
                    | ID
                    | chamada_expressao
                    | '(' expressao ')'
                    | expressao ('+' | '-' | '*' | '/' | '%' | '^') expressao
                    | '-' expressao
                    | expressao ('==' | '!=' | '<' | '<=' | '>' | '>=') expressao
                    | expressao (E | OU) expressao
                    | NAO expressao

chamada_expressao   → ID '(' argumentos_opcionais ')'
argumentos_opcionais→ ε | lista_argumentos
lista_argumentos    → expressao | lista_argumentos ',' expressao
```

Símbolo inicial: `programa`. A gramática é **LALR(1)** e o Bison a processa
**sem nenhum conflito** (nem shift/reduce, nem reduce/reduce).

### 6.2 Precedência dos operadores

Da **menor** para a **maior** precedência (as de baixo são calculadas primeiro):

| Nível | Operadores | Associatividade |
|---|---|---|
| 1 | `ou` | esquerda |
| 2 | `e` | esquerda |
| 3 | `nao` | (unário) |
| 4 | `==` `!=` `<` `<=` `>` `>=` | **não associativos**: `a < b < c` é erro |
| 5 | `+` `-` | esquerda |
| 6 | `*` `/` `%` | esquerda |
| 7 | `-` (negativo) | (unário) |
| 8 | `^` | **direita**: `2 ^ 3 ^ 2 = 2 ^ 9` |

Exemplos (todos em `testes/ok_precedencia.txt`):

| Expressão | Resultado | Por quê |
|---|---|---|
| `2 + 3 * 4` | `14` | `*` antes de `+` |
| `10 - 4 - 3` | `3` | `-` associa à esquerda: `(10-4)-3` |
| `2 ^ 3 ^ 2` | `512.0` | `^` associa à direita: `2^(3^2)` |
| `-2 ^ 2` | `-4.0` | `^` antes do negativo: `-(2^2)` |
| `1 < 2 e 3 > 4 ou verdadeiro` | `verdadeiro` | `e` antes de `ou` |

### 6.3 Detalhes da gramática

- **Início e fim de programa:** o programa precisa começar com `programa Nome {`,
  ter o bloco principal `inicio { ... }` e terminar com `}`.
- **Blocos sempre com chaves.** Por isso não existe o problema clássico do
  "senão pendurado" (*dangling else*). O `senao se` é só um `senao` seguido de
  outro `condicional`.
- **Ações no meio da regra.** Em `funcao`, a função é registrada logo após o
  nome, antes de ler o corpo. É isso que permite a **recursão**: dentro do corpo,
  a função já existe. Em `bloco`, a abertura `{` cria um novo escopo de variáveis.
- **Localizações (`%locations`).** Cada símbolo carrega a linha em que aparece,
  usada em todas as mensagens de erro.
- **Mensagens de erro próprias (`%define parse.error custom`).** A função
  `yyreport_syntax_error` escreve a mensagem em português, com o que foi encontrado
  e o que era esperado.

---

## 7. Árvore sintática (`ast.c`)

Durante a análise, o programa vira uma árvore. Exemplo (saída de `--arvore`):

```
programa Mini {
    inicio {
        seja x: inteiro = 2 + 3 * 4;
        seja r: real = x / 2.0;
        se (r > 5) {
            escreva("r =", r);
        }
    }
}
```

```
Inicio
  Declaracao x : inteiro
    valor inicial:
      Operacao '+' : inteiro
        Literal 2 : inteiro
        Operacao '*' : inteiro        ← a precedência aparece na forma da árvore
          Literal 3 : inteiro
          Literal 4 : inteiro
  Declaracao r : real
    valor inicial:
      Operacao '/' : real
        Conversao inteiro -> real     ← inserida pela análise semântica
          Variavel x : inteiro
        Literal 2.0 : real
  Se
    condicao:
      Operacao '>' : logico
        Variavel r : real
        Conversao inteiro -> real
          Literal 5 : inteiro
    entao:
      Escreva
        Literal "r =" : texto
        Variavel r : real
```

Cada nó guarda a sua categoria (literal, operação, declaração, ...), o tipo do
valor que produz, os filhos e a linha do código. Listas de comandos e de
argumentos são encadeadas pelo campo `prox`.

---

## 8. Análise semântica (`semantico.c` e `tabela.c`)

### 8.1 Tabela de símbolos e escopo

- Cada **função** tem a sua própria tabela de símbolos, com parâmetros e
  variáveis. **Não há variáveis globais**: uma função só enxerga o que é dela.
  O bloco `inicio` funciona como uma função sem parâmetros.
- **Escopo de bloco:** uma variável declarada dentro de `{ }` deixa de existir no
  `}` que fecha aquele bloco. Depois disso, o mesmo nome pode ser declarado de novo.
- Não é permitido declarar um nome que **já está visível** (no mesmo bloco ou em
  um bloco de fora), para evitar confusão entre variáveis com o mesmo nome.
- Cada variável recebe uma **posição fixa** na memória da função, usada pelo
  interpretador.

### 8.2 Regras de tipos

| Operação | Operandos | Resultado |
|---|---|---|
| `+ - * /` | números | `inteiro` se os dois forem inteiros, senão `real` |
| `/` entre inteiros | inteiro, inteiro | **divisão inteira** (`7 / 2 = 3`) |
| `^` | números | sempre `real` |
| `%` | inteiro, inteiro | `inteiro` |
| `< <= > >=` | números | `logico` |
| `== !=` | dois números, dois logicos ou dois textos | `logico` |
| `e ou nao` | logico | `logico` |
| `-x` | número | o mesmo tipo de `x` |

**Conversão automática:** um `inteiro` pode ser usado onde se espera um `real`
(atribuição, argumento, operação mista). Nesses casos, a análise semântica insere
um nó `Conversao inteiro -> real` na árvore. O contrário (`real` para `inteiro`)
**não** é permitido, porque perderia as casas decimais.

### 8.3 Verificações feitas

- a variável ou função foi declarada antes de ser usada;
- não há declaração repetida no mesmo escopo;
- o tipo atribuído combina com o tipo da variável;
- os operandos são do tipo aceito pelo operador;
- as condições de `se` e `enquanto` são do tipo `logico`;
- a variável de controle do `para` é numérica;
- a chamada de função tem a quantidade e os tipos certos de argumentos;
- uma função sem tipo de retorno não é usada dentro de expressões;
- `retorne` devolve o tipo declarado na função.

---

## 9. Execução (`interpretador.c`)

O interpretador percorre a árvore recursivamente:

- **`avaliar(nó)`** calcula o valor de uma expressão;
- **`executar(nó)`** realiza um comando.

**Memória:** cada chamada de função cria um **quadro**, um vetor com uma posição
para cada parâmetro e variável da função. Como cada chamada tem o seu próprio
quadro, a recursão funciona: `fatorial(5)` e `fatorial(4)` não misturam as suas
variáveis `n`.

**Retorno:** quando `retorne` é executado, o comando avisa quem o chamou
(estado `RETORNOU`). Assim, os laços e blocos são interrompidos até voltar à
função.

**Comportamentos importantes:**

| Comando | Comportamento |
|---|---|
| `seja x: tipo;` | sem valor inicial, a variável começa com `0`, `0.0`, `falso` ou `""` |
| `escreva(a, b, ...)` | escreve os valores separados por espaço e pula linha; reais sempre com ponto (`4.0`) |
| `leia(x)` | lê uma palavra do teclado e converte para o tipo de `x` (`logico` aceita `verdadeiro`/`falso`) |
| `para i de A ate B passo P` | `A`, `B` e `P` são calculados uma vez; `P` padrão = 1; `P` negativo conta para baixo |
| `e` / `ou` | curto-circuito: o lado direito só é calculado se for necessário |

---

## 10. Mensagens de erro

O compilador para no primeiro erro e mostra a etapa e a linha:

| Etapa | Exemplo de código | Mensagem |
|---|---|---|
| Léxica | `x = 10 @ 2;` | `Erro lexico na linha 5: simbolo invalido '@'` |
| Léxica | `escreva("sem fechar);` | `Erro lexico na linha 4: texto aberto com " e nao fechado na mesma linha` |
| Sintática | falta `;` | `Erro sintatico na linha 6: encontrado 'escreva', mas era esperado ';'` |
| Sintática | sem bloco `inicio` | `Erro sintatico na linha 7: encontrado '}', mas era esperado 'inicio' ou 'funcao'` |
| Semântica | `total = 1;` sem declarar | `Erro semantico na linha 5: a variavel 'total' nao foi declarada` |
| Semântica | `x = 2.5;` com `x` inteiro | `Erro semantico na linha 6: atribuicao: esperado tipo inteiro, mas foi encontrado real` |
| Semântica | `se (x)` com `x` inteiro | `Erro semantico na linha 5: a condicao do 'se' deve ser logica, mas e inteiro` |
| Semântica | `soma(1)` com 2 parâmetros | `Erro semantico na linha 7: a funcao 'soma' espera 2 argumento(s), mas recebeu 1` |
| Execução | `a / 0` | `Erro de execucao na linha 6: divisao por zero` |
| Execução | recursão sem fim | `Erro de execucao na linha 4: recursao muito profunda na funcao 'infinita'` |

As mensagens não usam acentos de propósito, para aparecerem corretamente em
qualquer terminal, inclusive no `cmd` do Windows.

---

## 11. Testes

Rodar os testes:

```
make testar                  Linux
compilar.bat testar          Windows
```

Os dois scripts (`testes/testar.sh` e `testes/testar.ps1`) fazem as mesmas
verificações, em **23 testes**:

- **`codigo_para_executar.txt`**: a saída do programa é comparada com as linhas
  `// > ...` que estão no final do próprio arquivo.
- **`testes/corretos.txt`**: 3 programas corretos (precedência dos operadores,
  recursão e escopo, leitura do teclado), conferidos do mesmo jeito. As linhas
  `// < ...` são os valores "digitados" para o comando `leia`.
- **`testes/erros.txt`**: 19 programas com erros léxicos, sintáticos, semânticos
  e de execução. A primeira linha de cada um (`// espera: ...`) diz qual mensagem
  o compilador deve mostrar, e o teste confere que o programa falha com ela.

Os arquivos `corretos.txt` e `erros.txt` guardam vários programas. Cada um começa
com uma linha `### <nome>`, e o script separa os casos antes de executá-los.

Todos os testes passaram em:

- **Linux** (Ubuntu, flex 2.6.4, bison 3.8.2, gcc), também com AddressSanitizer
  e UndefinedBehaviorSanitizer, sem erros de memória;
- **Windows** (WinFlexBison com win_flex 2.6.4 e win_bison 3.8.2, gcc MinGW).

Os arquivos gerados no Windows (`lex.yy.c`, `sintatico.tab.c`, `sintatico.tab.h`)
também compilam sem alterações no Linux.

---

## 12. Limitações conhecidas

- Não há variáveis globais nem vetores/listas.
- `texto` serve para guardar, comparar (`==`, `!=`) e escrever; não há concatenação.
- `leia` em um `texto` lê uma única palavra (até o primeiro espaço).
- A memória da árvore não é liberada no fim. O sistema operacional a recupera
  quando o programa termina.
- O limite de chamadas aninhadas é 2000, para evitar estouro de pilha.
