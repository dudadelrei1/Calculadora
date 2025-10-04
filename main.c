#include <stdio.h>
//Analisar se eh digito ou operador
#include <ctype.h>
//Para malloc e calloc
#include <stdlib.h>
//Para pow
#include <math.h>
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

	
	//Checa se os ponteiros sao validos

	//Armazena memoria para os operadores
	char* operadores = malloc((n-1)*sizeof(char)); 

	//Le os dados inseridos
	printf("Insira os numeros e operadores (Ex: 2 + 3*4): \n"); 
	for(int i=0; i<(2*n-1); i++){
		scanf(" %c", &entradas[i]);
	}

	//Variaveis para controlar o tamanho dos vetores
	int tmhval = 0, tmhop = 0; 
	//Vetor para armazenar os digitos consecutivos obtidos
	float* digitos = calloc(n, sizeof(float));
	//Variavel para controlar o tamanho do vetor de digitos
	int tmhdig = 0; 

	//Verifica se eh digito ou nao e transforma o tipo caso seja
	for (int i=0; i<(2*n-1); i++){
		//Reseta a quantidade de digitos da entrada, se for digito
		tmhdig = 0;
		//Se nao for digito, armazena no vetor de operadores 
		if(!isdigit(entradas[i])){
			operadores[tmhop++] = entradas[i]; 
		
		}else{
			//Enquanto for digito, armazena no vetor de digitos 
			while(isdigit(entradas[i])){
				//Transforma o char em float e armazena no vetor de digitos
				digitos[tmhdig] = entradas[i] - '0';
				tmhdig++; 
				i++; 
			} 
			//Transforma o vetor de digitos em um unico numero 
			for(int j=0; j<tmhdig; j++){
				//Soma o valores dos digitos multiplicados por 10 elevado a posicao
				valores[tmhval] += digitos[j]*pow(10, tmhdig-j-1);
				//Aumenta o tamanho do vetor de valores apenas quando o numero esta completo
				if(j==tmhdig-1){
					tmhval++;
				}
			}
		}	
	}


	float total = valores[0]; //Variavel para armazenar o resultado
	//Analisa qual operador esta sendo pedido
	for(int i=0; i<n; i++){
		switch(operadores[i]){
			case '+': 
				total = soma(total, valores[i+1]);
				i++; 
				break; 
			case '-': 
				total = sub(total, valores[i+1]);
				i++; 
				break;
			case '/': 
				total = divi(total, valores[i+1]);
				i++; 
				break;
			case '*': 
				total = mult(total, valores[i+1]);
				i++; 
				break;
		}
	}	

	printf("O resultado final eh: %f", total); 

	free(entradas); 
	free(valores); 
	free(operadores);
	return 0; 
}
