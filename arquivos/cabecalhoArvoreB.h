#ifndef CABECALHOARVOREB_H
    #define CABECALHOARVOREB_H
    #include "registroArvoreB.h"

    typedef struct _cabecalhoArvoreB CABECALHO_ARVORE_B;

    CABECALHO_ARVORE_B *criarCabecalhoArvoreBVazio();
    char getStatusCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    int getNoRaizCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    int getProxRRNCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    int getNroChavesCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    bool setStatusCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, char status);
    bool setNoRaizCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int noRaiz);
    bool setProxRRNCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int proxRRN);
    bool setNroChavesCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int nroChaves);
    CABECALHO_ARVORE_B *lerCabecalhoArvoreB(FILE *file);
    bool escreverCabecalhoArvoreB(FILE *file, CABECALHO_ARVORE_B *cabecalho);
    bool apagarCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    bool imprimirCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho);
    
#endif