#include <stdio.h> 

char op;
char ops[10000]; 
int number = 0; 
double numero[10000]; 
double total = 0; 

int main(){
	
    printf("\tCalculadora!\n"); 
    
    printf("Digite a expressão que deseja realizar(para encerrar a operação digite 'e' - *sem as aspas): ");

    //Analise dos numeros e operadores digitados
    do {
    scanf("%lf", &numero[number]);
    scanf(" %c", &op);
    //if (op == 'e') {return 0;}
    ops[number] = op;
    number++; 
    } while(1);
    
    //Loop para realizar primeiramente as multiplicações ou divisões (a depender de quem aparecer primeiro)
    for(int i = 0; i<number; i++){
    if(ops[i] == '*'){
        
        numero[i] = numero[i]*numero[i+1]; 
        for (int j = i + 1; j < number; j++) {
         numero[j] = numero[j + 1];
         ops[j - 1] = ops[j]; }
         
         number--;
         i--;} 
    else if(ops[i] == '/'){
        numero[i] = numero[i]/numero[i+1]; 
        for(int j = i+1; j<number; j++){
            numero[j] = numero[j+1]; 
            ops[j-1] = ops[j]; 
        }
         number--; 
    }}
    
    //Soma do primeiro numero
    total += numero[0]; 
    
    //Loop para realizar as somas ou subtrações
    for(int i = 0; i<number; i++){
    if(ops[i] == '+'){
        total += numero[i+1];
        for(int j = i+1; j<number; j++){
        ops[j-1] = ops[j]; 
        }
    number--; 
    }else if(ops[i] == '-'){
        total -= numero[i+1];
        for(int j = i+1; j<number; j++){
        ops[j-1] = ops[j]; 
        } 
         number--;
    }
    }
    
    printf("%lf", total);
	
	return 0; 
	}
