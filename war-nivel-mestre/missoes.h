#ifndef MISSOES_H
#define MISSOES_H

#include "territorio.h"

#define TOTAL_MISSOES 5

// atribui uma missão (aloca memoria para destino)
void atribuirMissao(char **destino);

// exibe missão
void exibirMissao(const char *missao);

// verifica missão do jogador (baseado na cor do jogador)
// retorna 1 se cumprida, 0 caso contrário
int verificarMissao(const char *missao, const Territorio *mapa, int total, const char *corJogador);

#endif // MISSOES_H
