#include <stdio.h>
#include "lista.h"

void listarTerritorios(const Territorio *mapa, int total) {
    if (total <= 0) {
        printf("Nenhum território cadastrado.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("ID %d\n", i);
        printf("  Nome : %s\n", mapa[i].nome);
        printf("  Cor  : %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("----------------------\n");
    }
}
