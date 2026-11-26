# ============================================================================
#  testes/testar.ps1 - Testes automaticos da linguagem Aurora (Windows)
# ============================================================================
#
#  Uso (na pasta principal do projeto):   compilar.bat testar
#
#  Faz as mesmas verificacoes do testar.sh (versao Linux):
#   1. exemplos\codigo_para_executar.txt e testes\corretos.txt
#        -> a saida de cada programa deve ser igual as suas linhas "// > ..."
#           (linhas "// < ..." sao usadas como valores digitados no teclado)
#   2. testes\erros.txt
#        -> cada caso deve FALHAR com a mensagem da sua linha "// espera: ..."
#   3. exercicios\*.txt (se a pasta existir), igual ao item 1
#
#  Os arquivos corretos.txt e erros.txt guardam varios programas; cada um
#  comeca com uma linha "### <nome>" e e separado em um arquivo temporario.
# ============================================================================

# Vai para a pasta principal do projeto (a pasta acima de testes\)
Set-Location (Split-Path -Parent $PSScriptRoot)

$executavel = ".\aurora.exe"
$temp = Join-Path ([IO.Path]::GetTempPath()) ("aurora_testes_" + [Guid]::NewGuid())
New-Item -ItemType Directory $temp | Out-Null
$script:passou = 0
$script:falhou = 0

if (-not (Test-Path $executavel)) {
    Write-Host "aurora.exe nao encontrado. Execute compilar.bat antes."
    exit 1
}

# Registra e mostra o resultado de um teste
function Resultado([bool]$ok, [string]$nome, [string]$detalhe) {
    if ($ok) {
        $script:passou++
        Write-Host "  [ OK ]  $nome"
    } else {
        $script:falhou++
        Write-Host "  [FALHA] $nome" -ForegroundColor Red
        Write-Host $detalhe
    }
}

# Separa um arquivo com varios casos ("### nome") em arquivos temporarios.
# Devolve a lista de casos (nome e caminho), na ordem do arquivo.
function Separar([string]$arquivo) {
    $casos = @()
    $atual = $null
    foreach ($linha in Get-Content $arquivo -Encoding UTF8) {
        if ($linha -match '^### (\S+)') {
            $atual = @{ Nome = $Matches[1]; Linhas = New-Object System.Collections.ArrayList }
            $casos += $atual
        } elseif ($atual) {
            [void]$atual.Linhas.Add($linha)
        }
    }
    foreach ($caso in $casos) {
        $caso.Caminho = Join-Path $temp ($caso.Nome + ".txt")
        [IO.File]::WriteAllLines($caso.Caminho, [string[]]$caso.Linhas)
    }
    return $casos
}

# Executa um programa usando as linhas "// < ..." como teclado.
# Devolve a saida (normal + erros) e o codigo de saida.
function Rodar([string]$programa) {
    $entrada = Join-Path $temp "entrada.txt"
    $valores = Get-Content $programa -Encoding UTF8 | Where-Object { $_ -match '^// <' } |
               ForEach-Object { $_ -replace '^// < ?', '' }
    [IO.File]::WriteAllLines($entrada, [string[]]@($valores))
    $linhas = cmd /c "$executavel `"$programa`" < `"$entrada`" 2>&1"
    return @{ Saida = (@($linhas) -join "`n").TrimEnd(); Codigo = $LASTEXITCODE }
}

# Compara a saida do programa com as suas linhas "// > ..."
function TestarCorreto([string]$programa, [string]$nome) {
    $esperado = (Get-Content $programa -Encoding UTF8 | Where-Object { $_ -match '^// >' } |
                 ForEach-Object { $_ -replace '^// > ?', '' }) -join "`n"
    $obtido = (Rodar $programa).Saida
    Resultado ($obtido -ceq $esperado.TrimEnd()) $nome "--- esperado:`n$esperado`n--- obtido:`n$obtido"
}

# O programa deve falhar com a mensagem da linha "// espera: ..."
function TestarErro([string]$programa, [string]$nome) {
    $esperado = (Get-Content $programa -TotalCount 1 -Encoding UTF8) -replace '^// espera: ', ''
    $execucao = Rodar $programa
    $ok = ($execucao.Codigo -ne 0) -and $execucao.Saida.Contains($esperado)
    Resultado $ok $nome "    esperado: $esperado`n    obtido:   $($execucao.Saida)"
}

Write-Host "== Programas corretos =="
TestarCorreto "exemplos\codigo_para_executar.txt" "exemplos\codigo_para_executar.txt"
foreach ($caso in Separar "testes\corretos.txt") {
    TestarCorreto $caso.Caminho ("corretos.txt: " + $caso.Nome)
}

if (Test-Path "exercicios") {
    Write-Host "== Exercicios =="
    foreach ($arquivo in Get-ChildItem "exercicios\*.txt" | Sort-Object Name) {
        TestarCorreto ("exercicios\" + $arquivo.Name) ("exercicios\" + $arquivo.Name)
    }
}

Write-Host "== Programas com erros =="
foreach ($caso in Separar "testes\erros.txt") {
    TestarErro $caso.Caminho ("erros.txt: " + $caso.Nome)
}

Remove-Item $temp -Recurse -Force
Write-Host ""
Write-Host "Resultado: $script:passou teste(s) passaram, $script:falhou falharam."
if ($script:falhou -gt 0) { exit 1 }
