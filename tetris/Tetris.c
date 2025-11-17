#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define MAX_PECAS 100

// Estrutura para representar uma peça do Tetris
typedef struct {
    char nome;  // Tipo da peça: I, O, T, L
    int id;     // Identificador único
} Peca;

// Estrutura para representar a fila de peças
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int tamanho;
    int total_pecas_geradas; // Contador para IDs únicos
} FilaPecas;

// Protótipos das funções
void inicializarFila(FilaPecas *fila);
int filaVazia(FilaPecas *fila);
int filaCheia(FilaPecas *fila);
void enqueue(FilaPecas *fila, Peca peca);
Peca dequeue(FilaPecas *fila);
Peca gerarPeca(FilaPecas *fila);
void exibirFila(FilaPecas *fila);
void exibirMenu();

int main() {
    FilaPecas fila;
    int opcao;
    
    // Inicializar random seed
    srand(time(NULL));
    
    // Inicializar a fila
    inicializarFila(&fila);
    
    printf("=== Tetris Stack - Sistema de Fila de Peças ===\n");
    printf("Fila inicializada com %d peças.\n\n", TAMANHO_FILA);
    
    do {
        exibirFila(&fila);
        exibirMenu();
        
        printf("\nDigite sua opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 0:
                printf("Saindo do sistema...\n");
                break;
                
            case 1: // Jogar peça (dequeue)
                if (!filaVazia(&fila)) {
                    Peca peca_removida = dequeue(&fila);
                    printf(">>> Peça jogada: [%c %d]\n", peca_removida.nome, peca_removida.id);
                    
                    // Adiciona uma nova peça automaticamente após remover
                    if (!filaCheia(&fila)) {
                        Peca nova_peca = gerarPeca(&fila);
                        enqueue(&fila, nova_peca);
                        printf(">>> Nova peça adicionada: [%c %d]\n", nova_peca.nome, nova_peca.id);
                    }
                } else {
                    printf(">>> Erro: Fila vazia! Não há peças para jogar.\n");
                }
                break;
                
            case 2: // Inserir nova peça (enqueue)
                if (!filaCheia(&fila)) {
                    Peca nova_peca = gerarPeca(&fila);
                    enqueue(&fila, nova_peca);
                    printf(">>> Nova peça adicionada: [%c %d]\n", nova_peca.nome, nova_peca.id);
                } else {
                    printf(">>> Erro: Fila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
                
            default:
                printf(">>> Opção inválida! Tente novamente.\n");
                break;
        }
        
        printf("\n");
        
    } while (opcao != 0);
    
    return 0;
}

// Inicializa a fila com peças aleatórias
void inicializarFila(FilaPecas *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    fila->total_pecas_geradas = 0;
    
    // Preencher a fila inicial com peças aleatórias
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca nova_peca = gerarPeca(fila);
        enqueue(fila, nova_peca);
    }
}

// Verifica se a fila está vazia
int filaVazia(FilaPecas *fila) {
    return fila->tamanho == 0;
}

// Verifica se a fila está cheia
int filaCheia(FilaPecas *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

// Adiciona uma peça ao final da fila
void enqueue(FilaPecas *fila, Peca peca) {
    if (!filaCheia(fila)) {
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->pecas[fila->tras] = peca;
        fila->tamanho++;
    }
}

// Remove e retorna a peça da frente da fila
Peca dequeue(FilaPecas *fila) {
    Peca peca_removida;
    
    if (!filaVazia(fila)) {
        peca_removida = fila->pecas[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->tamanho--;
    }
    
    return peca_removida;
}

// Gera uma peça aleatória com ID único
Peca gerarPeca(FilaPecas *fila) {
    Peca nova_peca;
    
    // Tipos de peças disponíveis
    char tipos[] = {'I', 'O', 'T', 'L'};
    int num_tipos = sizeof(tipos) / sizeof(tipos[0]);
    
    // Escolher tipo aleatório
    nova_peca.nome = tipos[rand() % num_tipos];
    
    // Atribuir ID único
    nova_peca.id = fila->total_pecas_geradas;
    fila->total_pecas_geradas++;
    
    return nova_peca;
}

// Exibe o estado atual da fila
void exibirFila(FilaPecas *fila) {
    printf("=== Estado da Fila de Peças ===\n");
    
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
    } else {
        printf("Fila de peças: ");
        
        int indice = fila->frente;
        for (int i = 0; i < fila->tamanho; i++) {
            printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
            indice = (indice + 1) % TAMANHO_FILA;
        }
        printf("\n");
        
        printf("Peças na fila: %d/%d\n", fila->tamanho, TAMANHO_FILA);
    }
    printf("\n");
}

// Exibe o menu de opções
void exibirMenu() {
    printf("=== Opções Disponíveis ===\n");
    printf("1 - Jogar peça (dequeue)\n");
    printf("2 - Inserir nova peça (enqueue)\n");
    printf("0 - Sair\n");
}