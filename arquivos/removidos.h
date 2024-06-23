#ifndef REMOVIDOS_H
    #define REMOVIDOS_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "indice.h"
        #include "interpreta-bin.h"
        #include "registro.h"

        typedef struct _removidos REMOVIDOS;
        void apagarListaRemovidos(REMOVIDOS *removidos);
        REMOVIDOS *criarListaRemovidos(FILE *file);
        void adicionarRegistroRemovido(REMOVIDOS *removidos, REGISTRO_INDICE *registroIndice, int tamanho);
        void removerRegistroRemovido(REMOVIDOS *removidos, int id);
        void removerRegistroRemovidoEAtualizarArquivo(REMOVIDOS *removidos, int id, FILE *file);
        int getTamanhoById(REMOVIDOS *removidos, int id);
        long long int getMaiorByteOffsetMenorQue(REMOVIDOS *removidos, int id);
        long long int *getBestFitArrayRegistros(REMOVIDOS *removidos, REGISTRO **registros, int quantidade, FILE *file);
        long long int getBestFitAndFreeSpace(REMOVIDOS *removidos, int tamanho, REGISTRO *registro, FILE *file);
        void imprimirRemovidos(REMOVIDOS *removidos, FILE *file);
#endif