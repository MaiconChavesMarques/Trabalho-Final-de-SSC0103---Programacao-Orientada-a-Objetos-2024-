#ifndef CRIAR_INDICE_H
    #define CRIAR_INDICE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #include "indice.h"
    #include "cabecalho.h"
    #include "registroIndice.h"
    #include "interpreta-bin.h"

    FILE *lerBinCriarIndice(FILE *arquivoBinario, char *arquivoIndice);
    int insertInPosicaoBinIndice(REGISTRO_INDICE *registro, FILE *arquivoInd, long long int posicao);
    int removeFromPosicaoBinIndice(FILE *arquivoInd, long long int posicao, char *arquivoIndName);
    void escreverRegistrosIndices(FILE *arquivoIndices, char *arquivoIndicesNome, LISTA_INDICE *listaIndices);
    void imprimirRegistrosIndice(FILE *arquivoIndice);
#endif