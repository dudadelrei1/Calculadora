#include <stdio.h>
#include "operacoes.h"

int main(void){
	int a, b; 
	printf("Digite dois valore inteiros: ");
	scanf("%d%d", &a, &b);
	soma(a,b); 
	sub(a,b); 
	div(a,b); 
	mult(a,b);
}
