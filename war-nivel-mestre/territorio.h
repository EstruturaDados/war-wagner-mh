#ifndef TERRITORIO_H
#define TERRITORIO_H

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    
    // Necessário para Missão 5:
    // "Manter um território sem ser atacado por 3 rodadas"
    int rodadasSemAtaque;   // <<--- ATIVAR ESTE CAMPO
} Territorio;

#endif // TERRITORIO_H
