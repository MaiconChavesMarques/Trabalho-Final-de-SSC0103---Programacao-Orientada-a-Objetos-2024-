#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "removidos.h"
    #include "funcoes_fornecidas.h"
    #include "criarIndice.h"
    
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo);
    void removerRegistrosBuscados(char *arquivoBin, char *arquivoIndice);
    void removeById(int id, LISTA_INDICE *listaIndices, FILE *file, FILE *fileIndices, REMOVIDOS *listaRemovidos, CABECALHO *cabecalho, char* arquivoIndice);
    bool escreverRegistro(REGISTRO *registro, int byteOffset, int tamRegistroAtual, FILE *arquivoBin);
    void criarArquivoArvoreB(char *arquivoBin, char *arquivoArvB);
    void imprimirArvoreB(FILE *arquivo);
#endif