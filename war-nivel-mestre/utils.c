#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void) {
    system("clear"); // No Windows, use "cls"
}

int validarString(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (!isalpha(c) && c != ' ')
            return 0;
    }
    return 1;
}

// -----------------------------------------------------------------------------
// Lê string segura
// -----------------------------------------------------------------------------
void lerString(const char *msg, char *dest, int tamanho) {
    printf("%s", msg);
    if (fgets(dest, tamanho, stdin)) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

// -----------------------------------------------------------------------------
// Lê inteiro com validação
// -----------------------------------------------------------------------------
int lerInteiro(const char *msg) {
    int valor;
    char linha[64];

    while (1) {
        printf("%s", msg);
        if (!fgets(linha, sizeof(linha), stdin)) {
            printf("Erro na entrada!\n");
            continue;
        }

        if (sscanf(linha, "%d", &valor) == 1)
            return valor;

        printf("Entrada inválida! Digite um número inteiro.\n");
    }
}

// -----------------------------------------------------------------------------
// Lê quantidade de territórios
// -----------------------------------------------------------------------------
int lerQuantidadeTerritorios(void) {
    int qtd;

    printf("Quantos territórios deseja cadastrar? ");
    while (scanf("%d", &qtd) != 1 || qtd <= 0) {
        printf("Valor inválido! Digite um número maior que zero: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    return qtd;
}

// -----------------------------------------------------------------------------
// Pausar até ENTER
// -----------------------------------------------------------------------------
void pausar(void) {
    printf("Pressione Enter para continuar...");
    getchar();
}
