#include <stdio.h>
//Analisar se eh digito ou operador
#include <ctype.h>
//Para malloc e calloc
#include <stdlib.h>
#include "operacoes.h"

int main(void){
	//Lê quantos numeros serao processados
	printf("Quantos numeros serao processados?: \n");
	int n; 
	scanf("%d", &n); 
	//Analisa se a entrada eh inteira para evitar erros
	//if(n){
	//}

	//Armazena memoria para os valores
	float* valores = calloc(n, sizeof(float)); 
	//Checa se os ponteiros sao validos

	//Armazena memoria para os operadores
	char* operadores = malloc((n-1)*sizeof(char)); 

	//Le os dados inseridos
	printf("Insira os numeros e operadores (Ex: 2 + 3*4): \n"); 
	for (int i = 0; i < n; i++) {
    	scanf("%f", &valores[i]);
    	if (i < n-1) {
        	scanf(" %c", &operadores[i]);
    	}
	}

	float total = 0; //Variavel para armazenar o resultado
	int index = 0; 
	int igualanmenosum = n-1; 
	float resultado = 0; 
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
        for (int j = index+1; j < igualanmenosum; j++) {
            valores[j] = valores[j+1]; 
            operadores[j-1] = operadores[j];
        }

        igualanmenosum--; } // agora temos um número a menos
        // não incrementa index, pois o novo valores[index] precisa ser reavaliado
        index++;
}

	// Segundo while (+ e -)
	index = 0; 
	while (index < igualanmenosum) {
    	if (operadores[index] == '+' || operadores[index] == '-') {
        	if (operadores[index] == '+') {
           		total = soma(valores[index], valores[index+1]);
        } else {
            	total = sub(valores[index], valores[index+1]);
		}
		
        igualanmenosum--;
    } 
        index++;
	}

	printf("O resultado final eh: %f", total);

	free(valores);
	free(operadores);
	return 0; 
}
