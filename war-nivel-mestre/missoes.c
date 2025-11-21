#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "missoes.h"

// vetor de missões (texto)
static char *missoes[TOTAL_MISSOES] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Possuir ao menos 5 tropas em um territorio",
    "Conquistar todos os territorios da cor azul",
    "Manter um territorio sem ser atacado por 3 rodadas"
};

void atribuirMissao(char **destino) {
    int idx = rand() % TOTAL_MISSOES;
    *destino = malloc(strlen(missoes[idx]) + 1);
    if (*destino == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para missao\n");
        exit(EXIT_FAILURE);
    }
    strcpy(*destino, missoes[idx]);
}

void exibirMissao(const char *missao) {
    printf("\n--- MISSÃO ATRIBUÍDA ---\n%s\n\n", missao);
}

/*
 Verificações simples (não perfeitas, mas funcionais):
 - "3 territorios seguidos": verifica se existem 3 territorios consecutivos com cor == corJogador
 - "vermelha": verifica se não existe território com cor "vermelha" e tropas > 0
 - "5 tropas": verifica se jogador tem algum território com tropas >= 5
 - "azul": verifica se não existe atualmente nenhum territorio com cor "azul" (interpretacao simples)
 - "3 rodadas": NÃO implementada (placeholder)
*/
int verificarMissao(const char *missao, const Territorio *mapa, int total, const char *corJogador) {
    if (missao == NULL || mapa == NULL || total <= 0 || corJogador == NULL) return 0;

    // 1) Conquistar 3 territorios seguidos
    if (strstr(missao, "3 territorios seguidos")) {
        int consec = 0;
        for (int i = 0; i < total; i++) {
            if (strcasecmp(mapa[i].cor, corJogador) == 0) {
                consec++;
                if (consec >= 3) return 1;
            } else {
                consec = 0;
            }
        }
        return 0;
    }

    // 2) Eliminar todas as tropas da cor vermelha
    if (strstr(missao, "cor vermelha") || strstr(missao, "vermelha")) {
        for (int i = 0; i < total; i++) {
            if (strcasecmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0; // ainda existe vermelha com tropas
        }
        return 1; // não encontrou mais tropas vermelhas
    }

    // 3) Possuir ao menos 5 tropas em um territorio
    if (strstr(missao, "5 tropas")) {
        for (int i = 0; i < total; i++) {
            if (strcasecmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 5)
                return 1;
        }
        return 0;
    }

    // 4) Conquistar todos os territorios da cor azul (interpretação simples):
    //    considera missão cumprida se NÃO existir nenhum território com cor "azul" (ou seja, foram conquistados)
    if (strstr(missao, "cor azul") || strstr(missao, "azul")) {
        for (int i = 0; i < total; i++) {
            if (strcasecmp(mapa[i].cor, "azul") == 0)
                return 0; // ainda existe azul não conquistado
        }
        return 1;
    }

    // 5) Manter um território sem ser atacado por 3 rodadas
    if (strstr(missao, "3 rodadas")) {
        for (int i = 0; i < total; i++) {
            if (strcasecmp(mapa[i].cor, corJogador) == 0 &&
                mapa[i].rodadasSemAtaque >= 3) {
                return 1; // missão cumprida
            }
        }
        return 0;
    }
}