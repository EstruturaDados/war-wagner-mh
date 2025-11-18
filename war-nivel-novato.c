#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para limpar buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c !=EOF);
}

// Função para limpar tela
void limparTela(){
    system("clear");
}

// Função para validar se a string contém apenas letras e espaços
int validarString(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = str[i];

        if (!isalpha(c) && c != ' ') {
            return 0; // inválido
        }
    }
    return 1; // válido
}

int main(){
    Territorio mapa[MAX_TERRITORIOS];
    int totalmapa = 0;
    int opcao;

    do {
        limparTela();
        printf("-------------------------\n");
        printf("       Territorios       \n");
        printf("-------------------------\n");
        printf("1 - Cadastrar territorios\n");
        printf("2 - Listar territorios   \n");
        printf("0 - Sair\n");
        printf("-------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limparBufferEntrada();
            opcao = -1;
        } else {
            limparBufferEntrada();
        }

        switch (opcao) {
            case 1:
                limparTela();
                if (totalmapa >= MAX_TERRITORIOS) {
                    printf("Limite de %d territórios atingido!\n", MAX_TERRITORIOS);
                    printf("Pressione Enter para continuar...");
                    getchar();
                    break;
                }

                // Nome do território
                do {
                    printf("Digite o nome do territorio: ");
                    fgets(mapa[totalmapa].nome, sizeof(mapa[totalmapa].nome), stdin);
                    mapa[totalmapa].nome[strcspn(mapa[totalmapa].nome, "\n")] = '\0';

                    if (!validarString(mapa[totalmapa].nome)) {
                        printf("Nome inválido! Use apenas letras e espaços.\n");
                    } else {
                        break;
                    }
                } while (1);

                // Cor do território
                do {
                    printf("Digite a cor do territorio: ");
                    fgets(mapa[totalmapa].cor, sizeof(mapa[totalmapa].cor), stdin);
                    mapa[totalmapa].cor[strcspn(mapa[totalmapa].cor, "\n")] = '\0';

                    if (!validarString(mapa[totalmapa].cor)) {
                        printf("Cor inválida! Use apenas letras e espaços.\n");
                    } else {
                        break;
                    }
                } while (1);

                // Tropas
                do {
                    printf("Digite a quantidade de tropas: ");
                    if (scanf("%d", &mapa[totalmapa].tropas) != 1 || mapa[totalmapa].tropas < 1) {
                        printf("Entrada inválida! Digite um número inteiro positivo.\n");
                        limparBufferEntrada();
                    } else {
                        limparBufferEntrada();
                        break;
                    }
                } while (1);

                totalmapa++;
                printf("\nTerritório cadastrado com sucesso!\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 2:
                limparTela();
                printf("-- Lista de Territórios Cadastrados --\n\n");
                if (totalmapa == 0) {
                    printf("Nenhum território cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalmapa; i++) {
                        printf("-------------------------\n");
                        printf("Território nº %d\n", i+1);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Cor: %s\n", mapa[i].cor);
                        printf("Tropas: %d\n", mapa[i].tropas);
                    }
                    printf("-------------------------\n");
                }
                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}