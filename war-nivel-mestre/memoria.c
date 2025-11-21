#include <stdlib.h>
#include "memoria.h"

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}
