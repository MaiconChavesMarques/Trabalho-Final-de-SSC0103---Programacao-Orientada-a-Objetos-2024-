#include "cabecalhoArvoreB.h"

struct _cabecalhoArvoreB {
    char status;
    int noRaiz;
    int proxRRN;
    int nroChaves;
};

// cria um cabecalho da arvore B com os valores padrao
CABECALHO_ARVORE_B *criarCabecalhoArvoreBVazio()
{
    CABECALHO_ARVORE_B *cabecalho = malloc(sizeof(CABECALHO_ARVORE_B));
    cabecalho->status = '0';
    cabecalho->noRaiz = 0;
    cabecalho->proxRRN = 0;
    cabecalho->nroChaves = 0;

    return cabecalho;
}

char getStatusCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return '$';
    }

    return cabecalho->status;
}

int getNoRaizCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return -1;
    }

    return cabecalho->noRaiz;
}

int getProxRRNCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return -1;
    }

    return cabecalho->proxRRN;
}

int getNroChavesCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return -1;
    }

    return cabecalho->nroChaves;
}

bool setStatusCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, char status)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    cabecalho->status = status;

    return true;
}

bool setNoRaizCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int noRaiz)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    cabecalho->noRaiz = noRaiz;

    return true;
}

bool setProxRRNCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int proxRRN)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    cabecalho->proxRRN = proxRRN;

    return true;
}

bool setNroChavesCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho, int nroChaves)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    cabecalho->nroChaves = nroChaves;

    return true;
}

// cria um cabecalho da arbore B a partir de um arquivo
CABECALHO_ARVORE_B *lerCabecalhoArvoreB(FILE *file)
{
    if (file == NULL)
    {
        return NULL;
    }

    CABECALHO_ARVORE_B *cabecalho = malloc(sizeof(CABECALHO_ARVORE_B));

    fseek(file, 0, SEEK_SET);

    fread(&cabecalho->status, sizeof(char), 1, file);
    fread(&cabecalho->noRaiz, sizeof(int), 1, file);
    fread(&cabecalho->proxRRN, sizeof(int), 1, file);
    fread(&cabecalho->nroChaves, sizeof(int), 1, file);

    return cabecalho;
}

// escreve em um arquivo o cabecalho da Arvore B
bool escreverCabecalhoArvoreB(FILE *file, CABECALHO_ARVORE_B *cabecalho)
{
    if (file == NULL || cabecalho == NULL)
    {
        return false;
    }

    fseek(file, 0, SEEK_SET);

    int tamanhoCabecalho = sizeof(char) + sizeof(int) * 3;

    fwrite(&cabecalho->status, sizeof(char), 1, file);
    fwrite(&cabecalho->noRaiz, sizeof(int), 1, file);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, file);
    fwrite(&cabecalho->nroChaves, sizeof(int), 1, file);

    char lixo = '$';
    for(int i = tamanhoCabecalho; i < TAMANHO_REGISTRO_ARVORE_B; i++)
    {
        fwrite(&lixo, sizeof(char), 1, file); // lixo para o cabecalho ter o mesmo tamanho do registro
    }

    return true;
}

bool apagarCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    free(cabecalho);

    return true;
}

bool imprimirCabecalhoArvoreB(CABECALHO_ARVORE_B *cabecalho)
{
    if (cabecalho == NULL)
    {
        return false;
    }

    printf("Status: %c\n", cabecalho->status);
    printf("No raiz: %d\n", cabecalho->noRaiz);
    printf("Prox RRN: %d\n", cabecalho->proxRRN);
    printf("Nro chaves: %d\n", cabecalho->nroChaves);

    return true;
}