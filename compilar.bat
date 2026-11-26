@echo off
REM ===========================================================================
REM  compilar.bat - Compila a linguagem Aurora no Windows
REM  Requisitos: WinFlexBison (win_flex / win_bison) e gcc (MinGW)
REM
REM  compilar.bat          compila e executa exemplos\codigo_para_executar.txt
REM  compilar.bat testar   compila e roda os testes automaticos
REM ===========================================================================

REM Garante que os comandos rodem na pasta deste arquivo .bat
cd /d "%~dp0"

REM Se o WinFlexBison foi instalado pelo winget, usa a pasta real do pacote
REM (o atalho criado pelo winget nao encontra a pasta "data" do Bison).
set FB=%LOCALAPPDATA%\Microsoft\WinGet\Packages\WinFlexBison.win_flex_bison_Microsoft.Winget.Source_8wekyb3d8bbwe
if exist "%FB%\win_bison.exe" (
    set BISON="%FB%\win_bison.exe"
    set FLEX="%FB%\win_flex.exe"
) else (
    set BISON=win_bison
    set FLEX=win_flex
)

if not exist gerados mkdir gerados

echo [1/3] Bison: gerando o analisador sintatico...
%BISON% -d -o gerados\sintatico.tab.c src\sintatico.y || goto erro

echo [2/3] Flex: gerando o analisador lexico...
%FLEX% -o gerados\lex.yy.c src\lexico.l || goto erro

echo [3/3] gcc: compilando...
REM -Wl,--stack aumenta a pilha do Windows (padrao de 1 MB) para 16 MB,
REM necessario para funcoes recursivas mais profundas
gcc -std=gnu11 -Wall -Isrc -Igerados -o aurora.exe gerados\sintatico.tab.c gerados\lex.yy.c src\main.c src\ast.c src\tabela.c src\semantico.c src\interpretador.c -lm -Wl,--stack,16777216 || goto erro

echo.
if /i "%~1"=="testar" (
    echo Compilado com sucesso. Rodando os testes:
    echo.
    powershell -NoProfile -ExecutionPolicy Bypass -File testes\testar.ps1
) else (
    echo Compilado com sucesso. Executando exemplos\codigo_para_executar.txt:
    echo.
    .\aurora.exe exemplos\codigo_para_executar.txt
)
REM Guarda o resultado dos testes/do exemplo para devolver no final
set RESULTADO=%ERRORLEVEL%
goto fim

:erro
echo Falha na compilacao.
set RESULTADO=1

:fim
REM Quando aberto com dois cliques, espera uma tecla antes de fechar a janela.
REM (o Explorer chama  cmd /c ""arquivo.bat" "  -> procura o trecho  " "  final;
REM  pelo terminal, PowerShell ou VS Code, nao ha pausa)
echo %cmdcmdline% | find """ """ >nul && if not defined SEM_PAUSA pause
exit /b %RESULTADO%
