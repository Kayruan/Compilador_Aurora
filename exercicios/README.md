# Exercícios resolvidos da linguagem Aurora

Material de estudo complementar (não faz parte dos itens obrigatórios da entrega).

Os 10 exercícios estão em ordem de dificuldade. Cada arquivo traz o enunciado, a
solução comentada linha a linha e, no final, a saída esperada (linhas `// > `).
Uma boa forma de estudar é ler o enunciado, tentar resolver sozinho em um arquivo
novo e só depois comparar com a solução.

| Arquivo | Assunto | Recursos praticados |
|---|---|---|
| `01_variaveis.txt` | Nome, idade e ano de nascimento | `seja`, `texto`, `inteiro`, atribuição |
| `02_areas.txt` | Área e perímetro | `+ * /`, parênteses, divisão inteira x real |
| `03_media_aluno.txt` | Média e situação do aluno | `real`, `se / senao se / senao` |
| `04_par_ou_impar.txt` | Par ou ímpar de 1 a 6 | `para`, `%`, contador |
| `05_maior_de_tres.txt` | Maior de três números | primeira `funcao`, `retorne`, operador `e` |
| `06_tabuada.txt` | Tabuada do 7 | `para` |
| `07_soma_ate_n.txt` | Soma de 1 a 100 | `enquanto`, acumulador, valor `logico` |
| `08_temperaturas.txt` | Celsius para Fahrenheit | função com `real`, `para` com `passo` |
| `09_digitos.txt` | Inverter e somar dígitos | `%` e `/` com inteiros dentro de `enquanto` |
| `10_imc_com_leitura.txt` | Cálculo do IMC | `leia` (digite 70 e 1.75) |

Para executar (na pasta principal do projeto, depois de compilar):

```
aurora.exe exercicios\06_tabuada.txt          Windows
./aurora exercicios/06_tabuada.txt            Linux
```

Os testes automáticos (`make testar` ou `compilar.bat testar`) também conferem
todos os exercícios desta pasta. Por isso, todo arquivo `.txt` colocado aqui precisa
ter as linhas `// > ` com a saída esperada; rascunhos e programas livres ficam em
[`../exemplos/`](../exemplos/).

## Ideias para praticar sozinho

1. Altere o exercício 04 para contar também os ímpares.
2. Faça a tabuada (exercício 06) de todos os números de 1 a 5, com um `para` dentro de outro.
3. Crie uma função `eh_bissexto(ano: inteiro): logico`. Um ano é bissexto se for divisível
   por 4 e não por 100, ou se for divisível por 400.
4. Escreva uma função recursiva `potencia(base: inteiro, exp: inteiro): inteiro`.
