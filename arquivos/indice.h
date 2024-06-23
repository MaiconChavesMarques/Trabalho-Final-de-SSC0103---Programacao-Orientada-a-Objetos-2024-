#ifndef INDICE_H
    #define INDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "registroIndice.h"
        #include "registro.h"

        typedef struct _lista LISTA_INDICE;

        int getTamanhoLista(LISTA_INDICE *lista);
        int getTamanhoMaxLista(LISTA_INDICE *lista);
        LISTA_INDICE *criarListaIndice();
        REGISTRO_INDICE *getRegistroIndice(LISTA_INDICE *lista, int index);
        int getTamanhoListaIndice(LISTA_INDICE *lista);
        long long int obterMaiorByteOffset(LISTA_INDICE *lista);
        bool adicionarRegistroIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro);
        bool adicionarRegistroOrdenadoIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro, FILE *file);
        bool modificarRegistroIndice(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro);
        REGISTRO_INDICE *buscarRegistroIndice(LISTA_INDICE *lista, int id);
        int buscarPosicaoRegistroIndiceLinear(LISTA_INDICE *lista, int id);
        int buscarPosicaoRegistroIndice(LISTA_INDICE *lista, int id);
        void setRegistroListaIndice(LISTA_INDICE *lista, int index, REGISTRO_INDICE *registro);
        void removerRegistroIndice(LISTA_INDICE *lista, int index);
        bool apagarListaIndice(LISTA_INDICE *lista);
        void imprimirListaIndice(LISTA_INDICE *lista);
        bool carregarIndice(LISTA_INDICE *lista, FILE *file);
        long long int buscarPosicaoArquivoIndice(int id, FILE *file);
        void setTamanho(LISTA_INDICE *lista, int tamanho);
#endif

