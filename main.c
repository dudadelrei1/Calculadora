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
	int tmhstr = n - 1; // quantidade de caracteres esperada (números + operadores)
	for(int i = 0; i < tmhstr; i++){
    	scanf(" %c", &entradas[i]);
    	if(i > 0 && isdigit(entradas[i])){
        	// Se dois dígitos seguidos formam um número, aumenta o tamanho esperado
        	tmhstr++;
    	}
	}

	//Variaveis para controlar o tamanho dos vetores
	int tmhval = 0, tmhop = 0; 
	//string para armazenar os digitos consecutivos obtidos
	char* digitos = calloc(n, sizeof(char));
	//Variavel para controlar o tamanho do vetor de digitos
	int tmhdig = 0; 
	
	//Verifica se eh digito ou nao e transforma o tipo caso seja
	for (int i = 0; i < (2*n-1); i++) { 
    	tmhdig = 0;

    	if (!isdigit(entradas[i])) {
        	operadores[tmhop++] = entradas[i]; 
    	} else {
        	while (i < (2*n-1) && isdigit(entradas[i])) {
            	digitos[tmhdig++] = entradas[i++];
        	}
		i--; //Ajusta o indice pois o for incrementa ele
        digitos[tmhdig] = '\0'; // fecha string
        valores[tmhval++] = atof(digitos);//Converte string para float
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

	free(entradas); 
	free(valores); 
	free(operadores);
	free(digitos);
	return 0; 
}
