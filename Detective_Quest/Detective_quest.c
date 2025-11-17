#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da sala
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para explorar as salas
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        return;
    }
    
    printf("\nVocê está na: %s\n", salaAtual->nome);
    
    // Verifica se é uma sala sem saídas (nó folha)
    if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
        printf("Esta sala não tem mais saídas. Exploração concluída!\n");
        return;
    }
    
    // Mostra as opções disponíveis
    printf("Opções disponíveis:\n");
    if (salaAtual->esquerda != NULL) {
        printf("  (e) Ir para a esquerda - %s\n", salaAtual->esquerda->nome);
    }
    if (salaAtual->direita != NULL) {
        printf("  (d) Ir para a direita - %s\n", salaAtual->direita->nome);
    }
    printf("  (s) Sair do jogo\n");
    
    // Lê a escolha do jogador
    char escolha;
    printf("\nPara onde deseja ir? ");
    scanf(" %c", &escolha);
    
    // Processa a escolha do jogador
    switch (escolha) {
        case 'e':
        case 'E':
            if (salaAtual->esquerda != NULL) {
                explorarSalas(salaAtual->esquerda);
            } else {
                printf("Não há caminho para a esquerda!\n");
                explorarSalas(salaAtual);
            }
            break;
            
        case 'd':
        case 'D':
            if (salaAtual->direita != NULL) {
                explorarSalas(salaAtual->direita);
            } else {
                printf("Não há caminho para a direita!\n");
                explorarSalas(salaAtual);
            }
            break;
            
        case 's':
        case 'S':
            printf("Saindo do jogo...\n");
            return;
            
        default:
            printf("Opção inválida! Use 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
            explorarSalas(salaAtual);
            break;
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

int main() {
    printf("=== DETECTIVE QUEST ===\n");
    printf("Bem-vindo à mansão misteriosa!\n");
    printf("Explore os cômodos para encontrar pistas...\n\n");
    
    // Montagem do mapa da mansão (árvore binária)
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* quarto = criarSala("Quarto Principal");
    Sala* escritorio = criarSala("Escritório");
    Sala* porao = criarSala("Porão");
    
    // Construção da estrutura da árvore
    // Hall de Entrada
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;
    
    // Sala de Estar
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    
    // Cozinha
    cozinha->esquerda = quarto;
    cozinha->direita = escritorio;
    
    // Biblioteca (folha - sem saídas)
    // Jardim (folha - sem saídas)
    
    // Quarto Principal
    quarto->esquerda = porao;
    // quarto->direita permanece NULL
    
    // Escritório (folha - sem saídas)
    // Porão (folha - sem saídas)
    
    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hallEntrada);
    
    // Libera a memória alocada para a árvore
    liberarArvore(hallEntrada);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}