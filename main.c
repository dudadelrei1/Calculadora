#include <stdio.h>
//Analisar se eh digito ou operador
#include <ctype.h>
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
	
	/*Armazena memoria para leitura dos dados inseridos
	Tamanho = n+n-1 porque se ha n valores, entao havera n-1 operadores*/
	//Transformaremos o char em float futuramente
	char* entradas = malloc((2*n-1)*sizeof(char));

	//Armazena memoria para os valores
	float* valores = calloc(n, sizeof(float)); 

	//Armazena memoria para os operadores
	char* operadores = malloc((n-1)*sizeof(char)); 

	//Le os dados inseridos
	printf("Insira os numeros e operadores (Ex: 2 + 3*4): \n"); 
	for(int i=0; i<(2*n-1); i++){
		scanf(" %c", &entradas[i]);
	}

	//Variaveis para controlar o tamanho dos vetores
	int tmhval = 0, tmhop = 0; 
	//Verifica se eh digito ou nao e transforma o tipo caso seja
	for (int i=0; i<(2*n-1); i++){
		if(isdigit(entradas[i])){
			valores[tmhval++] = entradas[i] - '0'; 
		}else if(!isdigit(entradas[i])){
			operadores[tmhop++] = entradas[i]; 
		}
	}


	float total = valores[0]; //Variavel para armazenar o resultado
	//Analisa qual operador esta sendo pedido
	for(int i=0; i<n-1; i++){
		switch(operadores[i]){
			case '+': 
				total = soma(total, valores[i]);
				break; 
			case '-': 
				total = sub(total, valores[i]);
				break;
			case '/': 
				total = divi(total, valores[i]);
				break;
			case '*': 
				total = mult(total, valores[i]);
				break;
		}
	}	

	printf("O resultado final eh: %f", total); 

	free(entradas); 
	free(valores); 
	free(operadores);git rn 0; 
}
