#include <stdio.h>
//Analisar se eh digito ou operador
#include <ctype.h>
//Para malloc e calloc
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "operacoes.h"

int main(void){
	//Analisa se a entrada eh inteira para evitar erros
	//if(n){
	//}

	//Armazena memoria para os valores
	float* valores = calloc(100, sizeof(float)); 
	//Checa se os ponteiros sao validos

	//Armazena memoria para os operadores
	char* operadores = malloc(99*sizeof(char)); 

    // Armazena memoria para as entradas
    char* entradas[200];
    for(int i=0; i<200; i++){
        entradas[i]=malloc(10*sizeof(char));
    }

	//Le os dados inseridos
	printf("Insira os numeros e operadores (Ex: 2 + 3*4): \n");  
    int tmhval = 0; 
    int tmhop = 0; 
    for (int i = 0; i < 200 && scanf(" %c", &entradas[i][0]) != '\n'; i++) {
        if (isdigit(entradas[i][0]) || (entradas[i][0] == '-' && isdigit(entradas[i][1]))) {
            // número (positivo ou negativo)
            valores[tmhval++] = atof(entradas[i]);
        } else {
            // operador ou parêntese
            operadores[tmhop++] = entradas[i][0];
        }
    }

    //Processa as entradas com parenteses
    for(int i=0; i<100 && entradas[i][0] != '\n'; i++){
        if(entradas[i][0] == '('){
            while(entradas[i][0] != ')'){
                calcular(100, valores, operadores);

            }
        }
    }

	//Depois inserir recursividade e potencia

	calcular(100, valores, operadores);

	printf("O resultado final eh: %.4f", valores[0]);

	free(valores);
	free(operadores);
	return 0; 
}
