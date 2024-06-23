#ifndef REGISTROARVOREB_H
    #define REGISTROARVOREB_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>

    #define ORDEM_ARVORE_B 4
    
    typedef struct _registroArvoreB REGISTRO_ARVORE_B;

    #define TAMANHO_REGISTRO_ARVORE_B 60

    REGISTRO_ARVORE_B *criarRegistroArvoreBVazio();
    bool inserirChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave, long long int byteOffset);
    bool removerChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave);
    bool inserirDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente, int chaveDescendente);
    bool removerDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente);
    int getAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    bool setAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro, int alturaNo);
    int getNroChavesRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    int getChave(REGISTRO_ARVORE_B *registro, int posicao);
    long long int getByteOffsetRegistroArvoreB(REGISTRO_ARVORE_B *registro, int posicao);
    int getDescendente(REGISTRO_ARVORE_B *registro, int posicao);
    bool apagarRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    bool imprimirRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    REGISTRO_ARVORE_B *lerRegistroArvoreB(FILE *arquivo, int rrn);
    bool escreverRegistroArvoreB(REGISTRO_ARVORE_B *registro, FILE *arquivo, int rrn);
#endif