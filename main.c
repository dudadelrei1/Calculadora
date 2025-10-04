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

	float total = valores[0]; //Variavel para armazenar o resultado
	//Analisa qual operador esta sendo pedido
	for(int i=0; i<n-1; i++){
		switch(operadores[i]){
			case '+': 
				total = soma(total, valores[i+1]);
				break; 
			case '-': 
				total = sub(total, valores[i+1]);
				break;
			case '/': 
				total = divi(total, valores[i+1]);
				break;
			case '*': 
				total = mult(total, valores[i+1]);
				break;
		}
	}	

	printf("O resultado final eh: %f", total); 
 
	free(valores); 
	free(operadores);
	return 0; 
}
