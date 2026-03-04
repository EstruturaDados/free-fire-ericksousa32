#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =======================
// Estruturas e Constantes
// =======================

#define MAX_ITENS 50

typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
    int prioridade;  // Nível Mestre
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;
bool ordenadoPorNome = false;

// =======================
// Protótipos de Funções
// =======================
void menuPrincipal();
void adicionarItem();
void removerItem();
void listarItens();
void buscarItem();
int buscarSequencial(const char *nome);
void ordenarItensPorNome();
void ordenarItensPorTipo();
void ordenarItensPorPrioridade();
int buscaBinaria(const char *nome, int *comparacoes);
void trocarItens(int i, int j);
void limparBuffer();

// =======================
// Função Principal
// =======================

int main() {
    menuPrincipal();
    return 0;
}

// =======================
// Implementação
// =======================

void menuPrincipal() {
    int opcao;

    do {
        printf("\n=== MOCHILA FREE FIRE ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (Sequencial)\n");
        printf("5. Ordenar itens\n");
        printf("6. Buscar item (Binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 5: {
                int criterio;
                printf("\nOrdenar por:\n1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
                scanf("%d", &criterio);
                limparBuffer();

                if (criterio == 1) ordenarItensPorNome();
                else if (criterio == 2) ordenarItensPorTipo();
                else if (criterio == 3) ordenarItensPorPrioridade();
                else printf("Critério inválido!\n");

                break;
            }
            case 6: {
                char nomeBusca[30];
                printf("Digite o nome para busca binária: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                if (!ordenadoPorNome) {
                    printf("Primeiro ordene por NOME!\n");
                } else {
                    int comps = 0;
                    int idx = buscaBinaria(nomeBusca, &comps);
                    if (idx != -1) {
                        Item *it = &mochila[idx];
                        printf("\nItem encontrado (binária): %s - %s - Qtd: %d - Pri: %d\n",
                            it->nome, it->tipo, it->quantidade, it->prioridade);
                        printf("Comparações: %d\n", comps);
                    } else {
                        printf("Item não encontrado.\n");
                        printf("Comparações: %d\n", comps);
                    }
                }
                break;
            }
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nDigite nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite tipo: ");
    fgets(novo.tipo, 30, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    printf("Digite prioridade (1-5): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();

    mochila[totalItens++] = novo;
    ordenadoPorNome = false;

    printf("Item adicionado!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int idx = buscarSequencial(nome);

    if (idx == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = idx; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("Item removido!\n");
}

void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        Item *it = &mochila[i];
        printf("%d) %s | %s | Qtd: %d | Pri: %d\n",
            i + 1, it->nome, it->tipo, it->quantidade, it->prioridade);
    }
}

void buscarItem() {
    char nome[30];
    printf("Digite nome para buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int idx = buscarSequencial(nome);
    if (idx == -1) {
        printf("Item não encontrado!\n");
    } else {
        Item *it = &mochila[idx];
        printf("Encontrado: %s | %s | Qtd: %d | Pri: %d\n",
            it->nome, it->tipo, it->quantidade, it->prioridade);
    }
}

int buscarSequencial(const char *nome) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarItensPorNome() {
    int comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item aux = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].nome, aux.nome) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = aux;
    }
    ordenadoPorNome = true;
    printf("Ordenado por nome! Comparações: %d\n", comparacoes);
}

void ordenarItensPorTipo() {
    int comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item aux = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, aux.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = aux;
    }
    ordenadoPorNome = false;
    printf("Ordenado por tipo! Comparações: %d\n", comparacoes);
}

void ordenarItensPorPrioridade() {
    int comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item aux = mochila[i];
        int j = i - 1;
        while (j >= 0 && mochila[j].prioridade > aux.prioridade) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = aux;
    }
    ordenadoPorNome = false;
    printf("Ordenado por prioridade! Comparações: %d\n", comparacoes);
}

int buscaBinaria(const char *nome, int *comparacoes) {
    int esquerda = 0, direita = totalItens - 1;
    *comparacoes = 0;

    while (esquerda <= direita) {
        (*comparacoes)++;
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
