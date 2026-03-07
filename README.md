-> Calculadora Científica em C

Este projeto consiste em uma calculadora científica desenvolvida em C que permite ao usuário calcular expressões matemáticas diretamente pelo terminal.

A calculadora suporta operações aritméticas, fatoriais, potências, funções trigonométricas, parênteses e cálculo de Fibonacci, além de registrar um histórico das operações realizadas.

# Funcionalidades

A calculadora suporta as seguintes operações:

### Operações aritméticas

* Adição: `+`
* Subtração: `-`
* Multiplicação: `*`
* Divisão: `/`

### Operações matemáticas avançadas

* Potência: `^`
* Fatorial: `!`
* Parênteses para controle de precedência: `( )`

### Funções trigonométricas

* Seno: `sin(x)` ou `sen(x)`
* Cosseno: `cos(x)`
* Tangente: `tan(x)`

As funções trigonométricas utilizam graus como entrada.

# Outras funcionalidades

### Cálculo de Fibonacci

O usuário pode calcular números da sequência de Fibonacci.

### Histórico de operações

Todas as expressões calculadas são salvas automaticamente em um arquivo.

O usuário pode visualizar o histórico pelo menu da aplicação.

### Estruturas de Dados

A calculadora utiliza uma lista duplamente encadeada para armazenar números e operadores.

### Processamento de Expressões

O cálculo das expressões envolve as seguintes etapas:

1. Leitura da expressão digitada pelo usuário
2. Conversão em lista encadeada
3. Aplicação das regras de precedência
4. Combinação dos nós da lista
5. Cálculo do resultado final

# Objetivo do Projeto

Este projeto foi desenvolvido com o objetivo de praticar conceitos importantes da linguagem C, incluindo:

* Estruturas
* Listas encadeadas
* Manipulação de strings
* Ponteiros
* Recursão
* Parsing de expressões matemáticas
* Estruturas de dados
* Organização de código modular
