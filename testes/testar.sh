#!/bin/sh
# ============================================================================
#  testes/testar.sh - Testes automáticos da linguagem Aurora (Linux)
# ============================================================================
#
#  Uso (na pasta principal do projeto):   make testar
#                                    ou:  sh testes/testar.sh [executavel]
#
#  O que é testado:
#   1. codigo_para_executar.txt e testes/corretos.txt
#        -> a saída de cada programa deve ser igual às suas linhas "// > ..."
#           (linhas "// < ..." são usadas como valores digitados no teclado)
#   2. testes/erros.txt
#        -> cada caso deve FALHAR com a mensagem da sua linha "// espera: ..."
#   3. exercicios/*.txt (se a pasta existir), igual ao item 1
#
#  Os arquivos corretos.txt e erros.txt guardam vários programas; cada um
#  começa com uma linha "### <nome>" e é separado em um arquivo temporário.
# ============================================================================

# Vai para a pasta principal do projeto (a pasta acima de testes/)
cd "$(dirname "$0")/.." || exit 1

EXECUTAVEL=${1:-./aurora}
PASSOU=0
FALHOU=0
TEMP=$(mktemp -d)
trap 'rm -rf "$TEMP"' EXIT

if [ ! -x "$EXECUTAVEL" ]; then
    echo "Executavel '$EXECUTAVEL' nao encontrado. Compile antes com: make"
    exit 1
fi

# Registra o resultado de um teste
resultado() {   # $1 = 0 (passou) ou 1 (falhou), $2 = nome, $3 = detalhe
    if [ "$1" -eq 0 ]; then
        PASSOU=$((PASSOU + 1))
        echo "  [ OK ]  $2"
    else
        FALHOU=$((FALHOU + 1))
        echo "  [FALHA] $2"
        [ -n "$3" ] && printf '%s\n' "$3" | sed 's/^/          /'
    fi
}

# Separa um arquivo com vários casos ("### nome") em arquivos numerados
separar() {   # $1 = arquivo de casos, $2 = pasta de destino
    mkdir -p "$2"
    tr -d '\r' < "$1" | awk -v pasta="$2" '
        /^### / { n++; arquivo = sprintf("%s/%02d_%s.txt", pasta, n, $2); next }
        arquivo { print > arquivo }'
}

# Executa um programa usando as linhas "// < ..." como teclado
rodar() {   # $1 = programa
    tr -d '\r' < "$1" | sed -n 's|^// < \{0,1\}||p' > "$TEMP/entrada"
    "$EXECUTAVEL" "$1" < "$TEMP/entrada" 2>&1
}

# Compara a saída do programa com as suas linhas "// > ..."
# (printf em vez de echo para não interpretar barras invertidas)
testar_correto() {   # $1 = programa, $2 = nome exibido
    tr -d '\r' < "$1" | sed -n 's|^// > \{0,1\}||p' > "$TEMP/esperado"
    DIFERENCA=$(rodar "$1" | tr -d '\r' | diff "$TEMP/esperado" - 2>&1)
    [ -z "$DIFERENCA" ]
    resultado $? "$2" "$DIFERENCA"
}

# O programa deve falhar com a mensagem da linha "// espera: ..."
testar_erro() {   # $1 = programa, $2 = nome exibido
    esperado=$(sed -n '1s|^// espera: ||p' "$1")
    SAIDA=$(rodar "$1")
    CODIGO=$?
    if [ "$CODIGO" -ne 0 ] && printf '%s\n' "$SAIDA" | grep -qF "$esperado"; then
        resultado 0 "$2"
    else
        resultado 1 "$2" "esperado: $esperado (codigo != 0)
obtido:   $SAIDA (codigo $CODIGO)"
    fi
}

echo "== Programas corretos =="
testar_correto codigo_para_executar.txt "codigo_para_executar.txt"
separar testes/corretos.txt "$TEMP/corretos"
for caso in "$TEMP"/corretos/*.txt; do
    nome=$(basename "$caso" .txt)
    testar_correto "$caso" "corretos.txt: ${nome#???}"
done

if [ -d exercicios ]; then
    echo "== Exercicios =="
    for programa in exercicios/*.txt; do
        testar_correto "$programa" "$programa"
    done
fi

echo "== Programas com erros =="
separar testes/erros.txt "$TEMP/erros"
for caso in "$TEMP"/erros/*.txt; do
    nome=$(basename "$caso" .txt)
    testar_erro "$caso" "erros.txt: ${nome#???}"
done

echo
echo "Resultado: $PASSOU teste(s) passaram, $FALHOU falharam."
[ "$FALHOU" -eq 0 ]
