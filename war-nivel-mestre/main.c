#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "territorio.h"
#include "utils.h"
#include "cadastro.h"
#include "lista.h"
#include "ataque.h"
#include "missoes.h"
#include "memoria.h"

int main(void) {
    srand((unsigned)time(NULL));
    int opcao = -1;

    Territorio *mapa = NULL;
    int max_territorios = 0;
    int totalmapa = 0;

    // cores dos jogadores (para simplificar, pedimos no início)
    char corJogador1[16] = {0};
    char corJogador2[16] = {0};

    printf("Jogador 1 - informe a sua cor (ex: Vermelha, Azul): ");
    if (fgets(corJogador1, sizeof(corJogador1), stdin))
        corJogador1[strcspn(corJogador1, "\n")] = '\0';
    while (!validarString(corJogador1)) {
        printf("Cor inválida! Use apenas letras e espaços. Tente novamente: ");
        if (fgets(corJogador1, sizeof(corJogador1), stdin))
            corJogador1[strcspn(corJogador1, "\n")] = '\0';
    }

    printf("Jogador 2 - informe a sua cor (ex: Verde, Amarela): ");
    if (fgets(corJogador2, sizeof(corJogador2), stdin))
        corJogador2[strcspn(corJogador2, "\n")] = '\0';
    while (!validarString(corJogador2)) {
        printf("Cor inválida! Use apenas letras e espaços. Tente novamente: ");
        if (fgets(corJogador2, sizeof(corJogador2), stdin))
            corJogador2[strcspn(corJogador2, "\n")] = '\0';
    }

    // Missões (dinamicamente alocadas)
    char *missaoJogador1 = NULL;
    char *missaoJogador2 = NULL;
    atribuirMissao(&missaoJogador1);
    atribuirMissao(&missaoJogador2);

    // Exibir missões apenas uma vez para cada jogador
    printf("\n--- Missao Jogador 1 (%s) ---\n", corJogador1);
    exibirMissao(missaoJogador1);
    printf("\n--- Missao Jogador 2 (%s) ---\n", corJogador2);
    exibirMissao(missaoJogador2);

    do {
        limparTela();
        printf("-------------------------\n");
        printf("       Territórios       \n");
        printf("-------------------------\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Listar territórios   \n");
        printf("3 - Atacar territórios   \n");
        printf("4 - Verificar missões   \n");
        printf("0 - Sair\n");
        printf("-------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limparBufferEntrada();
            opcao = -1;
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                limparTela();

                // aloca mapa na primeira vez que cadastrar
                if (mapa == NULL) {
                    max_territorios = lerQuantidadeTerritorios();
                    mapa = calloc((size_t)max_territorios, sizeof(Territorio));
                    if (mapa == NULL) {
                        fprintf(stderr, "Erro ao alocar memoria para mapa\n");
                        return 1;
                    }
                    totalmapa = 0;
                }

                if (totalmapa >= max_territorios) {
                    printf("Limite de %d territorios atingido!\n", max_territorios);
                    printf("Pressione Enter para continuar...");
                    getchar();
                    break;
                }

                cadastroTerritorio(&mapa[totalmapa]);
                totalmapa++;

                printf("\nCadastrado com sucesso! Pressione Enter...");
                getchar();
                break;

            case 2:
                limparTela();
                listarTerritorios(mapa, totalmapa);
                printf("Pressione Enter...");
                getchar();
                break;

            case 3:
                limparTela();

                if (totalmapa < 2) {
                    printf("Cadastre ao menos dois territórios!\n");
                    printf("Pressione Enter...");
                    getchar();
                    break;
                }

                int a, d;
                printf("\nEscolha o ID do território ATACANTE: ");
                if (scanf("%d", &a) != 1) { limparBufferEntrada(); printf("Entrada inválida\n"); break; }
                limparBufferEntrada();
                printf("Escolha o ID do território DEFENSOR: ");
                if (scanf("%d", &d) != 1) { limparBufferEntrada(); printf("Entrada inválida\n"); break; }
                limparBufferEntrada();

                if (a < 0 || a >= totalmapa || d < 0 || d >= totalmapa) {
                    printf("IDs inválidos!\n");
                    printf("Pressione Enter...");
                    getchar();
                    break;
                }

                if (strcasecmp(mapa[a].cor, mapa[d].cor) == 0) {
                    printf("Não é possível atacar território da mesma cor!\n");
                    printf("Pressione Enter...");
                    getchar();
                    break;
                }

                // opcional: impedir atacar se atacante tiver só 1 tropa
                if (mapa[a].tropas < 2) {
                    printf("Território atacante precisa ter pelo menos 2 tropas para atacar.\n");
                    printf("Pressione Enter...");
                    getchar();
                    break;
                }

                atacar(&mapa[a], &mapa[d]);

                // === Atualiza rodadasSemAtaque:
                // o defensor (d) já foi resetado dentro de atacar(),
                // então aqui incrementamos todos os territorios que NÃO foram atacados nesta rodada.
                for (int i = 0; i < totalmapa; i++) {
                    if (i == d) {
                        // defensor já teve rodadasSemAtaque = 0 (atualizado em atacar)
                        continue;
                    }
                    // incrementa para os não atacados
                    mapa[i].rodadasSemAtaque++;
                }

                // após ataque verificamos missões silenciosamente
                if (verificarMissao(missaoJogador1, mapa, totalmapa, corJogador1)) {
                    printf("\nJogador 1 (%s) cumpriu a missão e venceu!\n", corJogador1);
                    opcao = 0; // sai do loop
                } else if (verificarMissao(missaoJogador2, mapa, totalmapa, corJogador2)) {
                    printf("\nJogador 2 (%s) cumpriu a missão e venceu!\n", corJogador2);
                    opcao = 0;
                } else {
                    printf("\nPressione Enter...");
                    getchar();
                }
                break;

            case 4:
                limparTela();
                printf("Verificando missões para ambos jogadores...\n\n");
                printf("Jogador 1 (%s): %s -> %s\n", corJogador1, missaoJogador1,
                       verificarMissao(missaoJogador1, mapa, totalmapa, corJogador1) ? "CUMPRIDA" : "NAO CUMPRIDA");
                printf("Jogador 2 (%s): %s -> %s\n", corJogador2, missaoJogador2,
                       verificarMissao(missaoJogador2, mapa, totalmapa, corJogador2) ? "CUMPRIDA" : "NAO CUMPRIDA");
                printf("\nPressione Enter...");
                getchar();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
                printf("Pressione Enter...");
                getchar();
                break;
        }

    } while (opcao != 0);

    // limpeza final
    if (mapa) liberarMemoria(mapa);
    free(missaoJogador1);
    free(missaoJogador2);

    return 0;
}
