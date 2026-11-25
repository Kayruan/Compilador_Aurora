# ============================================================================
#  Makefile - Compilação da linguagem Aurora (Linux)
# ============================================================================
#
#  make              compila tudo (gera o executável ./aurora)
#  make executar     compila e roda codigo_para_executar.txt
#  make arvore       roda o exemplo mostrando a árvore sintática
#  make testar       roda os testes automáticos
#  make limpar       apaga o executável
#  make limpar-tudo  apaga também os arquivos gerados pelo Flex/Bison
#
#  No Windows, use compilar.bat.
# ============================================================================

CC     = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -Isrc -Igerados
BISON  = bison
FLEX   = flex

EXECUTAVEL = aurora

# Arquivos escritos à mão (pasta src/)
FONTES  = src/main.c src/ast.c src/tabela.c src/semantico.c src/interpretador.c

# Arquivos gerados automaticamente pelo Bison e pelo Flex (pasta gerados/)
GERADOS = gerados/sintatico.tab.c gerados/lex.yy.c

all: $(EXECUTAVEL)

# Bison: gramática (.y) -> analisador sintático (.tab.c) + tokens (.tab.h)
gerados/sintatico.tab.c gerados/sintatico.tab.h: src/sintatico.y
	mkdir -p gerados
	$(BISON) -d -Wall -o gerados/sintatico.tab.c src/sintatico.y

# Flex: regras léxicas (.l) -> analisador léxico (lex.yy.c)
# (depende do .tab.h porque usa os códigos de token definidos pelo Bison)
gerados/lex.yy.c: src/lexico.l gerados/sintatico.tab.h
	$(FLEX) -o gerados/lex.yy.c src/lexico.l

# Compila e liga tudo em um único executável (-lm = biblioteca matemática)
$(EXECUTAVEL): $(GERADOS) $(FONTES) src/aurora.h
	$(CC) $(CFLAGS) -o $(EXECUTAVEL) $(GERADOS) $(FONTES) -lm

executar: $(EXECUTAVEL)
	./$(EXECUTAVEL) codigo_para_executar.txt

arvore: $(EXECUTAVEL)
	./$(EXECUTAVEL) --arvore codigo_para_executar.txt

testar: $(EXECUTAVEL)
	sh testes/testar.sh ./$(EXECUTAVEL)

limpar:
	rm -f $(EXECUTAVEL) $(EXECUTAVEL).exe

limpar-tudo: limpar
	rm -f $(GERADOS) gerados/sintatico.tab.h

.PHONY: all executar arvore testar limpar limpar-tudo
