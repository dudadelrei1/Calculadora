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
		//Le o valor
    	scanf("%f", &valores[i]);
		//Le o operador, se nao for o ultimo numero
    	if (i < n-1) {
        	scanf(" %c", &operadores[i]);
    	}
	}

	int index = 0; //Variavel de controle do whilw
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

	free(valores);
	free(operadores);
	return 0; 
}
