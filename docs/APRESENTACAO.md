# Roteiro de apresentação

Guia curto para apresentar o compilador da linguagem Aurora.

## Resumo em uma frase

> O Flex divide o código em tokens. O Bison confere se esses tokens seguem a
> gramática e, a cada regra reconhecida, chama a análise semântica, que verifica
> tipos e nomes usando a tabela de símbolos e monta a árvore sintática. Se não
> houver nenhum erro, o interpretador percorre essa árvore e executa o programa,
> criando um quadro de memória para cada chamada de função, o que permite a
> recursão.

## Demonstração ao vivo

1. **Compilar e rodar os testes** — mostra que tudo funciona:

   ```
   compilar.bat testar
   ```

2. **Mostrar a árvore sintática** — funções, precedência e conversões de tipo
   aparecem na forma da árvore:

   ```
   aurora.exe --arvore exercicios\05_maior_de_tres.txt
   ```

3. **Provocar um erro de cada fase** em uma cópia do exemplo:

   | Fase | O que alterar | Mensagem esperada |
   |---|---|---|
   | Léxica | inserir `@` em uma expressão | `Erro lexico ... simbolo invalido '@'` |
   | Sintática | apagar um `;` | `Erro sintatico ... era esperado ';'` |
   | Semântica | atribuir `2.5` a uma variável `inteiro` | `Erro semantico ... esperado tipo inteiro, mas foi encontrado real` |
   | Execução | dividir por zero | `Erro de execucao ... divisao por zero` |

## Perguntas prováveis

- **Por que a análise semântica acontece junto com a sintática?** As ações das
  regras do Bison chamam o módulo semântico, que confere os tipos e devolve o nó
  da árvore pronto. Assim, nada é executado antes de todo o código ser validado.
- **Como a recursão funciona?** A função é registrada na tabela de símbolos logo
  após o nome (ação no meio da regra), e cada chamada cria o seu próprio quadro
  de memória no interpretador.
- **A gramática tem conflitos?** Não. Ela é LALR(1) e o Bison a processa sem
  conflitos shift/reduce nem reduce/reduce.
