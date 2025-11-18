#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// ======== STRUCT DO TERRITÓRIO ==========
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ======= LIMPAR BUFFER ==========
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ====== LIMPAR TELA =========
void limparTela(){
    system("clear");
}

// ===== VALIDAR STRING =========
int validarString(char str[]){
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ')
            return 0;
    }
    return 1;
}

// ===== FUNÇÃO ATAQUE =======
void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\nSimulando ataque...\n");
    printf("%s (%s) ATACANDO -> %s (%s)\n",
        atacante->nome, atacante->cor,
        defensor->nome, defensor->cor
    );

    // rolagem dos dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // ======= LÓGICA DO RESULTADO =======
    if (dadoAtacante > dadoDefensor) {

        printf("\n>>> O atacante VENCEU!\n");

        // defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // defensor recebe metade das tropas do atacante (arredondando para baixo)
        defensor->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);

    } else {

        printf("\n>>> O defensor RESISTIU!\n");

        // atacante perdeu uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
        }

        printf("O atacante perdeu 1 tropa! Tropas restantes: %d\n",
               atacante->tropas);
    }

    printf("\nAtaque finalizado!\n\n");
}

// ====== FUNÇÃO PARA LIBERAR MEMÓRIA ============
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ===== LER QUANTIDADE DO MAPA =====
int lerQuantidadeTerritorios(){
    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    limparBufferEntrada();
    return qtd;
}

int main() {
    srand(time(NULL));
    int opcao;

    // Ponteiro e variáveis para o mapa
    Territorio *mapa = NULL;
    int max_territorios = 0;
    int totalmapa = 0;

    /* === NOVO: entrada dinâmica ===
    int max_territorios = lerQuantidadeTerritorios();
    Territorio *mapa = calloc(max_territorios, sizeof(Territorio));
    int totalmapa = 0; */

    do {
        limparTela();
        printf("-------------------------\n");
        printf("       Territórios       \n");
        printf("-------------------------\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Listar territórios   \n");
        printf("3 - Atacar territórios   \n");
        printf("0 - Sair\n");
        printf("-------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limparBufferEntrada();
            opcao = -1;
        } else {
            limparBufferEntrada();
        }

        switch (opcao) {

            // -------- CADASTRAR ------------
            case 1:
                limparTela();

                // Pergunta quantidade apenas na primeira vez
                if (mapa == NULL) {
                    max_territorios = lerQuantidadeTerritorios();
                    mapa = calloc(max_territorios, sizeof(Territorio));
                    totalmapa = 0;
                }

                if (totalmapa >= max_territorios) {
                    printf("Limite de %d territorios atingido!\n", max_territorios);
                    getchar();
                    break;
                }

                // Definir o nome do território
                
                do {
                    printf("Nome do território: ");
                    fgets(mapa[totalmapa].nome, 30, stdin);
                    mapa[totalmapa].nome[strcspn(mapa[totalmapa].nome, "\n")] = '\0';
                } while (!validarString(mapa[totalmapa].nome));

                
                // Definir a cor do território
                
                do {
                    printf("Cor do território: ");
                    fgets(mapa[totalmapa].cor, 10, stdin);
                    mapa[totalmapa].cor[strcspn(mapa[totalmapa].cor, "\n")] = '\0';
                } while (!validarString(mapa[totalmapa].cor));
                
                // Definir a quantidade de tropas
                do {
                    printf("Tropas: ");
                    if (scanf("%d", &mapa[totalmapa].tropas) !=1 ||
                     mapa[totalmapa].tropas < 1) {
                        printf("Valor inválido!\n");
                        limparBufferEntrada();
                     }else{
                        limparBufferEntrada();
                        break;
                     }
                } while (1);

                totalmapa++;
                printf("\nCadastrado com sucesso!\n");
                getchar();
                break;
            
            // -------- LISTAR -------------
            case 2:
                limparTela();
                printf("-- Territórios --\n\n");
                if (totalmapa == 0) {
                    printf("Nenhum cadastrado.\n");
                } else {
                    for (int i = 0; i < totalmapa; i++) {
                        printf("ID %d\n", i);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Cor: %s\n", mapa[i].cor);
                        printf("Tropas: %d\n", mapa[i].tropas);
                        printf("----------------------\n");
                    }
                }
                getchar();
                break;
            
            // -------- ATAQUE -------------
            case 3:
                limparTela();

                if (totalmapa < 2){
                    printf("Cadastre ao menos dois territórios!\n");
                    getchar();
                    break;
                }

                // escolher atacante
                int a, d;

                printf("\nEscolha o ID do território atacante: ");
                scanf("%d", &a);
                limparBufferEntrada();

                printf("\nEscolha o ID do território defensor: ");
                scanf("%d", &d);
                limparBufferEntrada();

                if (a < 0 || a >= totalmapa || d < 0 || d >= totalmapa) {
                    printf("\nIDs inválidos!\n");
                    getchar();
                    break;
                }

                if (strcmp(mapa[a].cor, mapa[d].cor) == 0){
                    printf("\nNão é possível atacar território da mesma cor!\n");
                    getchar();
                    break;
                }

                atacar(&mapa[a], &mapa[d]);

                printf("\nPressione Enter...");
                getchar();
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
                getchar();
        }

    } while (opcao != 0);

    // Libera memória somente se foi alocada
    if (mapa != NULL) {
    liberarMemoria(mapa);
    }
    
    return 0;
}