#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor para armazenar os itens (mochila)
struct Item mochila[10];
int totalItens = 0; // Contador de itens na mochila

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menu();
void limparBuffer();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventário!\n");
    printf("Você pode cadastrar até 10 itens em sua mochila.\n\n");
    
    menu();
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirItem() {
    if (totalItens >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n--- CADASTRAR NOVO ITEM ---\n");
    
    // Ler nome do item
    printf("Nome do item (max 29 caracteres): ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0; // Remove \n
    
    // Ler tipo do item
    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0; // Remove \n
    
    // Ler quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    totalItens++;
    printf("\n✅ Item '%s' adicionado com sucesso!\n", mochila[totalItens-1].nome);
    
    // Lista todos os itens após adição
    listarItens();
}

void removerItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n--- REMOVER ITEM ---\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove \n
    
    // Busca sequencial pelo item
    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        return;
    }
    // Remove o item deslocando os elementos
    printf("\n✅ Item '%s' removido com sucesso!\n", mochila[indice].nome);
    
    for (int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    
    // Lista todos os itens após remoção
    listarItens();
}

void listarItens() {
    printf("\n--- LISTA DE ITENS NA MOCHILA ---\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia. Nenhum item cadastrado.\n");
        return;
    }
    
    printf("Total de itens: %d/10\n", totalItens);
    printf("----------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("----------------------------------------\n");
    }
}
void buscarItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    printf("\n--- BUSCAR ITEM ---\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove \n
    
    // Busca sequencial pelo item
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

void menu() {
    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair do sistema\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n🎮 Sistema de inventário encerrado. Boa sorte na missão!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}