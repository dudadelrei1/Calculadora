/*
 * ================================================
 * CALCULADORA COM LISTA ENCADEADA
 * ================================================
 * 
 * Programa que implementa uma calculadora interativa com suporte a:
 *   - Operações matemáticas: + - * / com precedência correta
 *   - Operador fatorial (!): unário pós-fixo
 *   - Função Fibonacci: modo separado para cálculo de números da sequência
 *   - Menu interativo: permite alternar entre modo expressão e modo Fibonacci
 * 
 * Características técnicas:
 *   - Usa lista duplamente encadeada para armazenar e processar expressões
 *   - Implementa precedência de operadores (!, *, /, +, -)
 *   - Utiliza array de ponteiros para funções
 *   - Utiliza alocação dinâmica
 *   - Validações: divisão por zero, fatorial apenas para inteiros não-negativos
 * 
 * Exemplo de uso:
 *   Modo Expressão: "3 + 5 * 2" → Resultado: 13.00
 *   Modo Fibonacci: entrada 5 → Fibonacci(5) = 8
 * 
 */

#include <stdio.h>     // Biblioteca padrão de entrada/saída (printf, scanf, fgets)
#include <stdlib.h>    // Biblioteca para alocação dinâmica de memória (malloc, free) e atoi/atof
#include <string.h>    // Biblioteca para manipulação de strings (strlen, strcmp, strcspn)
#include <ctype.h>     // Biblioteca para verificação de caracteres (isdigit, isspace, toupper)

// ========================================
// DEFINIÇÃO DE ESTRUTURAS DE DADOS
// ========================================

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

// ========================================
// PROTÓTIPOS DE FUNÇÕES
// ========================================

float soma(float a, float b);      // Função que realiza adição
float sub(float a, float b);       // Função que realiza subtração
float mult(float a, float b);      // Função que realiza multiplicação
float divi(float a, float b);      // Função que realiza divisão
Leitura* criar_lista(Leitura* inicio, float valor, char operador); // Insere elemento na lista
void precedencia(Leitura** lista); // Aplica regras de precedência de operadores
void imprimir_lista(Leitura* lista); // Exibe o conteúdo da lista (debug)
void liberar_lista(Leitura* lista);  // Libera memória alocada
int eh_operador(char c);            // Verifica se caractere é operador
float processar_expressao(const char* expressao); // Processa e calcula expressão
int fatorial(int a);                // Calcula fatorial recursivo
int potencia(unsigned a, unsigned b); //Calcula potencia com operador bit a bit
// ========================================
// ARRAY DE PONTEIROS PARA FUNÇÕES
// ========================================
// Define um tipo de ponteiro para função que recebe 2 floats e retorna float
typedef float (*operacao_t)(float, float);

// Array global que mapeia operadores para funções matemáticas
// Índice 0: + (soma)
// Índice 1: - (subtração)
// Índice 2: * (multiplicação)
// Índice 3: / (divisão)
operacao_t operacoes[4];

// ========================================
// FUNÇÃO: inicializar_operacoes
// ========================================
// Inicializa o array de ponteiros com as funções matemáticas
// Deve ser chamada no início do main() antes de usar as operações
void inicializar_operacoes(void) {
    operacoes[0] = soma;   // +
    operacoes[1] = sub;    // -
    operacoes[2] = mult;   // *
    operacoes[3] = divi;   // /
}

// ========================================
// FUNÇÃO: obter_indice_operacao
// ========================================
// Converte um caractere de operador em índice do array de ponteiros
// Parâmetro:
//   - op: caractere do operador (+, -, *, /)
// Retorna: índice (0-3) ou -1 se operador inválido
int obter_indice_operacao(char op) {
    switch (op) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        default: return -1;
    }
}

// ========================================
// FUNÇÃO: eh_operador
// ========================================
// Verifica se um caractere é um operador matemático
// Retorna: 1 (verdadeiro) se for +, -, *, /, ! ; 0 (falso) caso contrário
int eh_operador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '!' || c == '^';
}

// ========================================
// FUNÇÃO: criar_lista
// ========================================
// Insere um novo elemento (número ou operador) ao FINAL da lista
// Parâmetros:
//   - inicio: ponteiro para o primeiro nó (ou NULL se lista vazia)
//   - valor: valor numérico do elemento
//   - operador: caractere do operador (ou '\0' se for número)
// Retorna: ponteiro para o início da lista (pode mudar se lista estava vazia)
Leitura* criar_lista(Leitura* inicio, float valor, char operador) {
    // Aloca memória para um novo nó
    Leitura* novo = malloc(sizeof(Leitura));
    if (!novo) {
        // Se falhar em alocar, exibe erro e retorna a lista original
        printf("Erro de alocação de memória\n");
        return inicio;
    }

    // Preenche os campos do novo nó
    novo->elements.valor = valor;
    novo->elements.operador = operador;
    novo->prox = NULL;      // Novo nó é sempre o último (inicialmente)
    novo->anterior = NULL;  // Será ajustado se houver nó anterior

    // Se a lista está vazia, o novo nó é o início
    if (inicio == NULL) {
        return novo;
    }

    // Caso contrário, percorre até o final da lista
    Leitura* atual = inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // Liga o novo nó ao final e ajusta ponteiros bidireccionais
    atual->prox = novo;      // Último nó agora aponta para novo
    novo->anterior = atual;  // Novo nó aponta para anterior

    return inicio;
}

// ========================================
// FUNÇÃO: combinar_nos
// ========================================
// Combina um operador com seus operandos, calcula o resultado e reconecta a lista
// Para operadores binários (+, -, *, /): combina anterior + operador + próximo
// Para operador unário (!): combina anterior + ! (fatorial)
// Parâmetro:
//   - operador_node: ponteiro para o nó do operador a ser processado
void combinar_nos(Leitura* operador_node) {
    Leitura* anterior = operador_node->anterior;   // Nó à esquerda do operador
    Leitura* proximo = operador_node->prox;        // Nó à direita do operador

    // ========== CASO ESPECIAL: FATORIAL (unário pós-fixo) ==========
    // Fatorial só precisa do número anterior, não do próximo
    if (operador_node->elements.operador == '!') {
        if (!anterior) {
            printf("Erro: Fatorial sem operando\n");
            return;
        }

        float val = anterior->elements.valor;
        int n = (int)val;
        // Valida se é inteiro não-negativo
        if (val < 0 || (float)n != val) {
            printf("Erro: Fatorial definido somente para inteiros nao-negativos\n");
            return;
        }

        // Calcula o fatorial usando a função recursiva
        int fact_i = fatorial(n);
        float resultado = (float)fact_i;

        // Substitui o nó do operador pelo resultado
        operador_node->elements.valor = resultado;
        operador_node->elements.operador = '\0'; // '\0' marca que agora é número

        // Remove o nó anterior (o operando) da lista e reconecta
        operador_node->anterior = anterior->anterior;
        if (anterior->anterior) {
            anterior->anterior->prox = operador_node;
        }
        // O nó do operador mantém o próximo
        operador_node->prox = proximo;
        if (proximo) {
            proximo->anterior = operador_node;
        }

        free(anterior); // Libera memória do nó removido
        return;
    }

    // ========== OPERADORES BINÁRIOS: VALIDAÇÃO ==========
    // Para +, -, *, /, ^ precisamos de números antes E depois
    if (!anterior || !proximo) {
        printf("Erro: Operador sem operandos suficientes\n");
        return;
    }

    // Extrai os valores dos operandos
    float a = anterior->elements.valor;
    float b = proximo->elements.valor;
    float resultado;

    // Validação: Verifica divisão por zero ANTES de executar
    if (operador_node->elements.operador == '/' && b == 0) {
        printf("Erro: Divisão por zero!\n");
        return;
    }

    // ========== EXECUTA A OPERAÇÃO CORRETA ==========
    // Obtém o índice da operação através do operador
    int idx = obter_indice_operacao(operador_node->elements.operador);
    if (idx < 0) {
        printf("Erro: Operador desconhecido\n");
        return;
    }

    // Executa a operação através do ponteiro de função
    // Chama a função correspondente do array operacoes[]
    if(idx < 4){
        resultado = operacoes[idx](a, b);
    }
    if(idx ==  4){
        resultado = (float)potencia((unsigned int)a, (unsigned int)b);    
    }


    // ========== SUBSTITUI O OPERADOR PELO RESULTADO ==========
    operador_node->elements.valor = resultado;
    operador_node->elements.operador = '\0'; // Marca como número

    // ========== RECONECTA A LISTA ==========
    // Remove o nó anterior: faz o avô apontar direto para o operador
    operador_node->anterior = anterior->anterior;
    if (anterior->anterior) {
        anterior->anterior->prox = operador_node;
    }

    // Remove o próximo nó: faz o operador apontar para o após-próximo
    operador_node->prox = proximo->prox;
    if (proximo->prox) {
        proximo->prox->anterior = operador_node;
    }

    // Libera memória dos dois nós que foram "consumidos"
    free(anterior);
    free(proximo);
}

// ========================================
// FUNÇÃO: precedencia
// ========================================
// Aplica as REGRAS DE PRECEDÊNCIA de operadores matemáticos
// Ordem de processamento (do maior para o menor):
//   1º: Fatorial (!)
//   2º: Multiplicação (*) e Divisão (/)
//   3º: Adição (+) e Subtração (-)
// Parâmetro:
//   - lista: ponteiro duplo para a lista (pode mudar o início)
void precedencia(Leitura** lista) {
    if (!lista || !*lista) return; // Se lista vazia, sai

    int modificado; // Flag para saber se houve mudança na passada
    
    // ========== PRIMEIRA PASSADA: FATORIAL (!) ==========
    // Processa todos os fatoriais primeiro (maior precedência)
    do {
        modificado = 0;                    // Inicializa flag
        Leitura* atual = *lista;           // Começa do início

        while (atual != NULL) {
            // Procura pelo primeiro fatorial
            if (eh_operador(atual->elements.operador) && atual->elements.operador == '!') {
                // Atualiza o início se o nó atual for o primeiro
                if (atual->anterior == *lista) {
                    *lista = atual;
                }

                combinar_nos(atual);    // Combina e calcula
                modificado = 1;         // Marca que fez algo
                break;                  // Recomeça do início
            }
            atual = atual->prox;        // Vai para o próximo nó
        }
    } while (modificado);  // Continua enquanto houver fatoriais

     // ========== SEGUNDA PASSADA: POTENCIA (^) ==========
    // Processa todos os fatoriais primeiro (maior precedência)
    do {
        modificado = 0;                    // Inicializa flag
        Leitura* atual = *lista;           // Começa do início

        while (atual != NULL) {
            // Procura pelo primeiro fatorial
            if (eh_operador(atual->elements.operador) && atual->elements.operador == '^') {
                // Atualiza o início se o nó atual for o primeiro
                if (atual->anterior == *lista) {
                    *lista = atual;
                }

                combinar_nos(atual);    // Combina e calcula
                modificado = 1;         // Marca que fez algo
                break;                  // Recomeça do início
            }
            atual = atual->prox;        // Vai para o próximo nó
        }
    } while (modificado);  // Continua enquanto houver fatoriais

    // ========== TERCEIRA PASSADA: * e / ==========
    // Processa multiplicações e divisões (segunda precedência)
    do {
        modificado = 0;
        Leitura* atual = *lista;
        
        while (atual != NULL) {
            // Procura pelo primeiro * ou /
            if (eh_operador(atual->elements.operador) && 
               (atual->elements.operador == '*' || atual->elements.operador == '/')) {
                
                // Atualiza o início se necessário
                if (atual->anterior == *lista) {
                    *lista = atual;
                }

                combinar_nos(atual);
                modificado = 1;
                break;
            }
            atual = atual->prox;
        }
    } while (modificado);

    // ========== QUARTA PASSADA: + e - ==========
    // Processa adições e subtrações (última precedência)
    do {
        modificado = 0;
        Leitura* atual = *lista;
        
        while (atual != NULL) {
            // Procura pelo primeiro + ou -
            if (eh_operador(atual->elements.operador) && 
               (atual->elements.operador == '+' || atual->elements.operador == '-')) {
                
                // Atualiza o início se necessário
                if (atual->anterior == *lista) {
                    *lista = atual;
                }

                combinar_nos(atual);
                modificado = 1;
                break;
            }
            atual = atual->prox;
        }
    } while (modificado);
}

// ========================================
// FUNÇÕES MATEMÁTICAS BÁSICAS
// ========================================

// Soma de dois números: a + b
float soma(float a, float b) {
    return a + b;
}

// Subtração de dois números: a - b
float sub(float a, float b) {
    return a - b;
}

// Multiplicação de dois números: a * b
float mult(float a, float b) {
    return a * b;
}

// Divisão de dois números: a / b (com verificação de divisão por zero)
float divi(float a, float b) {
    if (b == 0) {
        printf("Erro: Divisão por zero!\n");
        return 0;
    }
    return a / b;
}

// ========================================
// FUNÇÃO: fatorial (RECURSIVA)
// ========================================
// Calcula o fatorial de um número inteiro: n! = n × (n-1) × ... × 1
// Casos base: 0! = 1, 1! = 1
// Parâmetro:
//   - a: número do qual calcular o fatorial
// Retorna: fatorial de a
int fatorial(int a){
    if(a == 0 || a == 1){
        return 1;       // Caso base
    }else{
        return a * fatorial(a-1);  // Chamada recursiva
    }
}

// ========================================
// FUNÇÃO: fibonacci (RECURSIVA)
// ========================================
// Calcula o n-ésimo número de Fibonacci
// Sequência: F(0)=1, F(1)=1, F(n)=F(n-1)+F(n-2)
// Parâmetro:
//   - n: índice do número de Fibonacci
// Retorna: n-ésimo número de Fibonacci
int fibonacci(int n){
    if(n == 0){
        return 1;      // Caso base
    }
    if(n == 1){
        return 1;      // Caso base
    }
    // Chamadas recursivas
    return fibonacci(n-1) + fibonacci(n-2);
}

int potencia(unsigned int base, unsigned int expoente){

    unsigned int maskara = 1;       // Máscara para testar o bit menos significativo
    unsigned int auxiliar;              // Vai receber (expoente & 1)
    unsigned int resultado = 1;     // Acumulador do resultado final
    unsigned int valor_atual = base; // Representa a "base" que será elevada, mudando a cada iteração

    // Enquanto ainda existirem bits no expoente para analisar
    while(expoente > 0){

        // Pega o bit menos significativo do expoente
        auxiliar = expoente & maskara;

        // Se esse bit for 1, multiplicamos o acumulador pela base atual
        if(auxiliar == 1){
            resultado = resultado * valor_atual;
        }

        // A base é elevada ao quadrado a cada etapa
        // Isso funciona porque cada bit representa uma potência de 2
        valor_atual *= valor_atual;

        // Desloca o expoente para a direita
        // Assim analisamos o próximo bit
        expoente >>= 1;
    }

    // Retorna o resultado calculado
    return resultado;
}
// ========================================
// FUNÇÃO: processar_expressao
// ========================================
// Processa uma expressão matemática em string
// Passos:
//   1. Percorre a string caractere por caractere
//   2. Identifica números e operadores
//   3. Constrói uma lista encadeada (números e operadores em ordem)
//   4. Aplica regras de precedência
//   5. Retorna e exibe o resultado final
// Parâmetro:
//   - expressao: string com a expressão (ex: "3 + 5 * 2")
// Retorna: resultado final como float
float processar_expressao(const char* expressao) {
    Leitura* lista = NULL;              // Inicia lista vazia
    const char* p = expressao;          // Ponteiro para percorrer string
    char buffer[100];                   // Buffer para ler números
    int buf_index = 0;                  // Índice dentro do buffer
    int esperando_numero = 1;           // 1=esperando número, 0=esperando operador

    // ========== LEITURA E PARSING DA EXPRESSÃO ==========
    while (*p) {
        // Ignora espaços em branco
        if (isspace(*p)) {
            p++;
            continue;
        }

        // CASO 1: Caractere é dígito, ponto ou sinal negativo
        if (isdigit(*p) || *p == '.' || (*p == '-' && esperando_numero)) {
            buf_index = 0;  // Reinicia buffer
            
            // Trata sinal negativo
            if (*p == '-') {
                buffer[buf_index++] = *p++;
            }
            
            // Coleta todos os dígitos e pontos decimais
            while (isdigit(*p) || *p == '.') {
                buffer[buf_index++] = *p++;
            }
            buffer[buf_index] = '\0';  // Termina a string
            
            // Converte string para float e insere na lista
            float num = atof(buffer);
            lista = criar_lista(lista, num, '\0');
            esperando_numero = 0;  // Agora espera operador
        }
        // CASO 2: Caractere é operador
        else if (eh_operador(*p) && !esperando_numero) {
            char op = *p;
            lista = criar_lista(lista, 0, op);  // Insere operador (valor=0)
            p++;
            
            // Fatorial é pós-fixo: não precisa de número depois
            if (op == '!') {
                esperando_numero = 0;  // Pode vir outro operador (outro !)
            } else {
                esperando_numero = 1;  // Espera número após operador binário
            }
        }
        // CASO 3: Caractere inválido
        else {
            printf("Caractere inválido ou expressão mal formada: %c\n", *p);
            p++;
        }
    }

    // Validação: se lista vazia, expressão não tinha nada
    if (!lista) {
        printf("Expressão vazia!\n");
        return 0;
    }

    // ========== APLICAR PRECEDÊNCIA E CALCULAR ==========
    precedencia(&lista);

    // Extrai resultado (deve haver apenas um nó restante)
    float resultado = lista->elements.valor;
    printf("Resultado: %.2f\n", resultado);

    // Libera toda a memória alocada
    liberar_lista(lista);

    return resultado;
}

// ========================================
// FUNÇÃO: liberar_lista
// ========================================
// Libera toda a memória alocada para a lista
// Percorre cada nó, salva o próximo, libera o atual e passa pro próximo
// Parâmetro:
//   - lista: ponteiro para o início da lista
void liberar_lista(Leitura* lista) {
    Leitura* atual = lista;
    while (atual != NULL) {
        Leitura* proximo = atual->prox;  // Salva o próximo antes de liberar
        free(atual);                     // Libera o nó atual
        atual = proximo;                 // Avança para o próximo
    }
}

// ========================================
// FUNÇÃO: main
// ========================================
// Função principal do programa
// Exibe menu de escolha entre dois modos:
//   1. Modo Expressão: calcula expressões matemáticas
//   2. Modo Fibonacci: calcula números de Fibonacci
// Retorna: 0 se execução bem-sucedida
int main(void) { 
    char linha[100];     // Buffer para leitura de entrada
    char entrada;        // Caractere da escolha do modo

    // ========== INICIALIZAÇÃO DO PROGRAMA ==========
    // Inicializa o array de ponteiros para funções
    inicializar_operacoes();

    // ========== EXIBIÇÃO DO MENU INICIAL ==========
    printf("=== CALCULADORA ===\n");
    printf("Digite expressoes matematicas ex: 3 + 5 * 2\n");
    printf("Suporte para: +, -, *, /, !\n");

    // ========== LOOP PRINCIPAL DO PROGRAMA ==========
    while (1) {
        // Pergunta qual modo o usuário deseja
        printf("\nFibonacci(F) ou Expressao numerica(E)? (ou 'S' para sair): ");
        if (!fgets(linha, sizeof(linha), stdin)) {
            break;  // Se erro na leitura, sai
        }
        
        // Remove o '\n' do final da string lida
        linha[strcspn(linha, "\n")] = '\0';
        
        // Converte primeira letra para maiúscula
        entrada = (char)toupper((unsigned char)linha[0]);

        // OPÇÃO 1: Sair do programa
        if (entrada == 'S') {
            break;
        } 
        // OPÇÃO 2: Modo Fibonacci
        else if (entrada == 'F') {
            while (1) {
                printf("Digite o numero para Fibonacci (ou 'voltar' para menu): ");
                if (!fgets(linha, sizeof(linha), stdin)) {
                    break;
                }
                linha[strcspn(linha, "\n")] = '\0';
                
                // Opção para voltar ao menu principal
                if (strcmp(linha, "voltar") == 0) {
                    break;
                }
                // Opção para encerrar completamente
                if (strcmp(linha, "sair") == 0) {
                    printf("Programa encerrado.\n");
                    return 0;
                }
                
                // Converte entrada para inteiro e calcula Fibonacci
                int n = atoi(linha);
                printf("Fibonacci(%d) = %d\n\n", n, fibonacci(n));
            }
        } 
        // OPÇÃO 3: Modo Expressão
        else if (entrada == 'E') {
            while (1) {
                printf("Expressao (ou 'voltar' para menu): ");
                if (!fgets(linha, sizeof(linha), stdin)) {
                    break;
                }
                linha[strcspn(linha, "\n")] = '\0';
                
                // Opção para voltar ao menu principal
                if (strcmp(linha, "voltar") == 0) {
                    break;
                }
                // Opção para encerrar completamente
                if (strcmp(linha, "sair") == 0) {
                    printf("Programa encerrado.\n");
                    return 0;
                }
                // Ignora entradas vazias
                if (strlen(linha) == 0) {
                    continue;
                }

                // Processa e calcula a expressão
                processar_expressao(linha);
                printf("\n");
            }
        } 
        // OPÇÃO 4: Entrada inválida
        else {
            printf("Opcao invalida. Digite 'F' para Fibonacci ou 'E' para Expressao.\n");
        }
    }

    printf("Programa encerrado.\n");
    return 0; 
} 