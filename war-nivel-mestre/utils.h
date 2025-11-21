#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// limpa buffer do teclado
void limparBufferEntrada(void);

// limpa tela (opcional)
void limparTela(void);

// valida se string contém apenas letras e espaço
int validarString(const char *str);

// lê string segura
void lerString(const char *msg, char *dest, int tamanho);

// lê um inteiro de forma segura
int lerInteiro(const char *msg);

// lê quantidade de territórios, validando entrada
int lerQuantidadeTerritorios(void);

// pausa até ENTER
void pausar(void);

#endif // UTILS_H
