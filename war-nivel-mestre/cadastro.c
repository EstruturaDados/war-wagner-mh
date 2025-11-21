#include <stdio.h>
#include <string.h>
#include "cadastro.h"
#include "utils.h"

void cadastroTerritorio(Territorio *t) {
    
    // Definir nome do território
    do {
        printf("Nome do território: ");
        if (!fgets(t->nome, sizeof(t->nome), stdin)) {
            t->nome[0] = '\0';
            limparBufferEntrada();
        }
        t->nome[strcspn(t->nome, "\n")] = '\0';
        if (!validarString(t->nome))
            printf("Nome inválido! Use apenas letras e espaços.\n");
    } while (!validarString(t->nome));

    // Definir a cor do território
    do {
        printf("Cor do território: ");
        if (!fgets(t->cor, sizeof(t->cor), stdin)) {
            t->cor[0] = '\0';
            limparBufferEntrada();
        }
        t->cor[strcspn(t->cor, "\n")] = '\0';
        if (!validarString(t->cor))
            printf("Cor inválida! Use apenas letras e espaços.\n");
    } while (!validarString(t->cor));

    // Definir a quantidade de tropas
    do {
        printf("Tropas: ");
        if (scanf("%d", &t->tropas) != 1 || t->tropas < 1) {
            printf("Valor inválido! Digite um inteiro positivo.\n");
            limparBufferEntrada();
        } else {
            limparBufferEntrada();
            break;
        }
    } while (1);

    // Inicializa contadores extras necessários para Missão 5
    t->rodadasSemAtaque = 0;
}
