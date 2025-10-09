/*
------------------------------------------------------------
Programa: Calculadora simples em C
Autor: Duda Del Rei
Data: Outubro de 2025

Descrição geral:
Implementa uma calculadora que realiza operações básicas
(+ , - , * , /) respeitando a precedência das operações.

O programa:
1. Lê a quantidade de números a serem processados;
2. Solicita os valores e operadores (ex: 2 + 3 * 4);
3. Executa as operações de multiplicação e divisão primeiro;
4. Depois realiza soma e subtração;
5. Exibe o resultado final.

Exemplo de uso:
Quantos numeros serao processados?:
3
Insira os numeros e operadores (Ex: 2 + 3*4):
2 + 3 * 4
O resultado final eh: 14.0000
------------------------------------------------------------
*/

#include <stdio.h>
//Analisar se eh digito ou operador
#include <ctype.h>

//Funcao soma
float soma(float a, float b){
	float c = a + b; 
	return c;
} 

//Funcao subtracao
float sub(float a, float b){
    float c = a - b; 
    return c; 
}

//Funcao multiplicacao
float divi(float a, float b){
    float c = a/b; 
    return c; 
}

//Funcao divisao
float mult(float a, float b){
    float c = a*b; 
    return c; 
}

int main(void){
	//Lê quantos numeros serao processados
	printf("Quantos numeros serao processados?: \n");
	int n; 
    scanf("%d", &n); 
	
	//Armazena memoria para os valores
	float valores[4*n]; 

	//Armazena memoria para os operadores
	char operadores[n-1]; 

	//Le os dados inseridos
	printf("Insira os numeros e operadores (Ex: 2 + 3*4): \n"); 
	for (int i = 0; i < n; i++) {
		//Le o valor
    	scanf("%f", &valores[i]);
		//Le o operador, se nao for o ultimo numero
    	if (i < n-1) {
        	scanf(" %c", &operadores[i]);
    	}
	}
	
	int index = 0; //Variavel de controle do while
	int igualanmenosum = n-1; //Numero de operadores (n-1) - variavel auxiliar
	// Primeiro while (* e /)
	while (index < igualanmenosum) {
    	if (operadores[index] == '*' || operadores[index] == '/') {
        	if (operadores[index] == '*'){
            	valores[index] = mult(valores[index], valores[index+1]);
        	}
        	else{
            	valores[index] = divi(valores[index], valores[index+1]);
        	}

        // Desloca os valores para a esquerda
		//Diminui o numero de operadores e valores
        for (int j = index+1; j < igualanmenosum; j++) {
            valores[j] = valores[j+1]; 
            operadores[j-1] = operadores[j];
        }

        igualanmenosum--; } // agora temos um número a menos
        // não incrementa index, pois o novo valores[index] precisa ser reavaliado
		else{
			index++;
		}
}

	// Segundo while (+ e -)
	//Comportamento similar ao primeiro while
	index = 0; 
	while (index < igualanmenosum) {
    	if (operadores[index] == '+' || operadores[index] == '-') {
        	if (operadores[index] == '+') {
           		valores[index] = soma(valores[index], valores[index+1]);
        } else {
            	valores[index] = sub(valores[index], valores[index+1]);
		}
		for (int j = index+1; j < igualanmenosum; j++) {
            valores[j] = valores[j+1]; 
            operadores[j-1] = operadores[j];
        }
        igualanmenosum--;
    } else{
		index++;
	}
	}

	printf("O resultado final eh: %.4f", valores[0]);

	return 0; 
}