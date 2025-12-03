#ifndef FUNC_H
#define FUNC_H

// Estrutura que armazena um ELEMENTO: número OU operador
typedef struct Elementos {
    float valor;     // Armazena o valor numérico (se for um número)
    char operador;   // Armazena o caractere do operador (+, -, *, /, !) ou '\0' se for número
} Elementos;

// Estrutura que representa um NÓ da lista duplamente encadeada
typedef struct Leitura {
    Elementos elements;        // Dados do nó (valor e/ou operador)
    struct Leitura* prox;      // Ponteiro para o próximo nó
    struct Leitura* anterior;  // Ponteiro para o nó anterior
} Leitura;

typedef float (*operacao_t)(float, float);

float soma(float a, float b);      // Função que realiza adição
float sub(float a, float b);       // Função que realiza subtração
float mult(float a, float b);      // Função que realiza multiplicação
float divi(float a, float b);      // Função que realiza divisão
Leitura* criar_lista(Leitura* inicio, float valor, char operador); // Insere elemento na lista
void precedencia(Leitura** lista);      // Aplica regras de precedência de operadores
void liberar_lista(Leitura* lista);     // Libera memória alocada
int eh_operador(char c);                // Verifica se caractere é operador
float processar_expressao(char* expressao); // Processa e calcula expressão
int fatorial(int a);                    // Calcula fatorial recursivo
int potencia(unsigned a, unsigned b);   //Calcula potencia com operador bit a bit
int eh_inteiro(float a, float b);       //Analisa se os numeros recebidos sao inteiros
float potenciaint(float a, float b);    //Calculo de potencia com math.h
void salvar_historico(const char* expressao, double resultado); // Função que salva as operações realizadas pelo usuário em um arquivo
void mostrar_historico(void); //Função que exibe o histórico ao usuário
void calculadora(void);
void inicializar_operacoes(void);
int modo(void);
typedef float (*operacao_t)(float, float);

#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif