/* 
    Ideia do código: 
        Mesmo funcionamento do chechpoint 1, mas tratar com lista, e não com vetores
        Valores lidos serão tipo CHAR (PESQUISAR COMO TRANSFORMAR STRING EM FLOAT)
        EU ACHO que se criarmos uma lista que lê todos os valores tipo char, observarmos se é operador ou não, 
        transformamos em float se necessário e DEPOIS seguirmos a lógica do checkpoint 1 FUNCIONA
        É necessário trabalhar SEMPRE com uma váriavel RESULTADO para controlar as operações anteriores. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Lista duplamente encadeada
typedef struct Leitura {
    //String em formato de ponteiro
    char* valor;
    struct Leitura* prox;
    struct Leitura* anterior;
} Leitura;

float soma(char* a, char* b); 
float sub(char* a, char* b); 
float mult(char* a, char* b); 
float divi(char* a, char* b); 
float transforma(char* valor); 

//Lista encadeada para ler as entradas
Leitura *criar_lista(Leitura* inicio, char* argumento) {
    // Cria um novo nó dinamicamente com malloc
    Leitura *novo = malloc(sizeof(Leitura));

    // Armazena o valor passado como argumento dentro do campo 'valor' do novo nó
    novo->valor = malloc(sizeof(argumento)); // aloca espaço suficiente
    strcpy(novo->valor, argumento);              // copia o conteúdo da string


    // Como será o último nó, o ponteiro 'prox' aponta para NULL
    novo->prox = NULL;

    // Caso a lista esteja vazia (início == NULL), 
    // o novo nó será o primeiro elemento da lista
    if (inicio == NULL) {
        return novo;
    }

    // Se a lista já possui elementos, percorremos até o último nó
    Leitura *atual = inicio;
    while (atual->prox != NULL) {
        atual = atual->prox; // avança nó a nó até chegar no final
    }

    // Quando o último nó é encontrado, seu 'prox' passa a apontar para o novo nó
    atual->prox = novo;
    //Quando o último nó é encontrado, seu 'anterior' será o que aponta para ele
    novo->anterior = atual; 

    // Retorna o ponteiro para o início da lista (não muda)
    return inicio;
}

Leitura* elimina_elemento(Leitura* lista){
                Leitura* no_anterior = lista->anterior;
                Leitura* no_proximo  = lista->prox;

                // 1. Reajusta o encadeamento
                if (no_anterior != NULL) {
                    lista->anterior = no_anterior->anterior;
                    if (no_anterior->anterior != NULL)
                        no_anterior->anterior->prox = lista;
                }

                if (no_proximo != NULL) {
                    lista->prox = no_proximo->prox;
                    if (no_proximo->prox != NULL)
                        no_proximo->prox->anterior = lista;
                }

                // 2. Libera os nós removidos
                free(no_anterior);
                free(no_proximo);

                return lista; 
}

int controla_tamanho(Leitura* lista, int tamanho){
    for(Leitura* atual = lista; atual != NULL; atual = atual->prox){
        tamanho++; 
    }
    return tamanho; 

}
//Analisa a precedencia dos operadores

void precedencia(Leitura* lista){
    //Vetor auxiliar para armazenar os valores da minha lista
    float* valores = malloc(100*sizeof(char));
    if(!valores){
        printf("ERRO NA ALOCACAO"); 
        return 1;
    }

    int controle = controla_tamanho(lista, 0); 

    int index = 0; //Variavel de controle do while
	// Primeiro while (* e /, por ordem de precedencia)
    while (index < controle) {
        if (lista->valor == '*' || lista->valor == '/') {
            if (lista->valor == '*'){
                valores[index] = mult((lista->anterior)->valor, (lista->prox)->valor);
                //Poderia igualar lista->valor diretamente, mas precisamos usar alocacao dinamica
                lista->valor = malloc(strlen(valores) + 1); // aloca espaço suficiente
                strcpy(lista->valor, valores);              // copia o conteúdo da string
                elimina_elemento(lista);

            }
            else{
                valores[index] = divi((lista->anterior)->valor, (lista->prox)->valor);
                lista->valor = malloc(strlen(valores) + 1); // aloca espaço suficiente
                strcpy(lista->valor, valores);              // copia o conteúdo da string
                elimina_elemento(lista);
            }
        }
        index++; 
    }

    controle = controla_tamanho(lista, 0); 

	// Segundo while (+ e -)
	//Comportamento similar ao primeiro while
    while (index < controle) {
        if (lista->valor == '+' || lista->valor == '-') {
            if (lista->valor == '+'){
                valores[index] = soma((lista->anterior)->valor, (lista->prox)->valor);
                lista->valor = malloc(strlen(valores) + 1); // aloca espaço suficiente
                strcpy(lista->valor, valores);              // copia o conteúdo da string
                elimina_elemento(lista);

            }
            else{
                valores[index] = sub((lista->anterior)->valor, (lista->prox)->valor);
                lista->valor = malloc(strlen(valores) + 1); // aloca espaço suficiente
                strcpy(lista->valor, valores);              // copia o conteúdo da string
                elimina_elemento(lista);
            }
        }
        index++; 
    }
    free(valores);
}

//Transforma o tipo de char para float
float transforma(char* valor){
    float num = strtof(valor, NULL);
    return num; 
    
}

//Funcao soma
float soma(char* a, char* b){
	float c = transforma(a) + transforma(b); 
	return c;
} 

//Funcao subtracao
float sub(char* a, char* b){
    float c = transforma(a) - transforma(b); 
    return c; 
}

//Funcao divisao
float divi(char* a, char* b){
    float c = transforma(a)/transforma(b); 
    return c; 
}

//Funcao multiplicacao
float mult(char* a, char* b){
    float c = transforma(a)*transforma(b); 
    return c; 
}

//Recursao - Fatorial
//DEPOIS CHECAR SE A ENTRADA É INTEIRA MESMO
/*int fatorial(int a){
    if(a == 0 || a == 1){
        return 1; 
    }else{
        return a*fatorial(a-1);
    }

}*/

//Modulo
/*float modulo(float a){
    if(a<0){
        return -a;
    } else{
        return a; 
    } 
}*/
 
//Radiciacao
/*float raiz(float a, float b){

}*/

//Potenciacao
/*float potencia(float a, float b){

}*/

int main(void){ 
    Leitura* lista = NULL;
    char entrada[100];

    printf("Digite uma expressão (ex: 3 + 5 * 2). ENTER vazio para parar:\n");

    // Lê os argumentos (um por um)
    while (1) {
        if (!fgets(entrada, sizeof(entrada), stdin)) break;
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strlen(entrada) == 0) break;

        lista = criar_lista(lista, entrada);
    }

    precedencia(lista);
    //Ponteiro para funcao
    float (*ponteiro)(char*) = transforma;
    printf("\nResultado final = %.2f\n", ponteiro(lista->valor));

    // Libera memória
    while (lista != NULL) {
        Leitura* temp = lista;
        lista = lista->prox;
        free(temp->valor);
        free(temp);
    }

    return 0; 
}