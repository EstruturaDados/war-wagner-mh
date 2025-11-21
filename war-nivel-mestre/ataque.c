#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ataque.h"

void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\nSimulando ataque...\n");
    printf("%s (%s) ATACANDO -> %s (%s)\n",
        atacante->nome, atacante->cor,
        defensor->nome, defensor->cor
    );

    // Marca que o defensor foi atacado nesta rodada (reseta contador)
    defensor->rodadasSemAtaque = 0;

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor  = (rand() % 6) + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n>>> O atacante VENCEU!\n");

        // defensor muda de dono (cor)
        strcpy(defensor->cor, atacante->cor);

        // defensor recebe metade das tropas do atacante (arredondando para baixo)
        defensor->tropas = atacante->tropas / 2;

        // opcional: reduzir tropas do atacante após transferência
        atacante->tropas = atacante->tropas - defensor->tropas;
        if (atacante->tropas < 1) atacante->tropas = 1;

        printf("O território %s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);

    } else {
        printf("\n>>> O defensor RESISTIU!\n");

        // atacante perdeu uma tropa (não fica abaixo de 1)
        if (atacante->tropas > 1) atacante->tropas -= 1;

        printf("O atacante perdeu 1 tropa! Tropas restantes: %d\n",
               atacante->tropas);
    }

    printf("\nAtaque finalizado!\n\n");
}
