#ifndef INSERIRDADO_H
    #define INSERIRDADO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    #include "funcoes_fornecidas.h"
    #include "indice.h"
    #include "registro.h"
    #include "removidos.h"
    #include "escreveBin.h"
    #include "criarIndice.h"

    void inserirNovoDado(char *arquivoBinario, char *arquivoIndice, int numOperacoes);
#endif