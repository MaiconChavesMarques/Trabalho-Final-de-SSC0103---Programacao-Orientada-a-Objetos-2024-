#include "registroArvoreB.h"

struct _registroArvoreB {
    int alturaNo;
    int nroChaves;
    int chaves[ORDEM_ARVORE_B - 1];
    long long int byteOffsets[ORDEM_ARVORE_B - 1];
    int descendentes[ORDEM_ARVORE_B];
};

// cria um registro de árvore B com os valores padrao
REGISTRO_ARVORE_B *criarRegistroArvoreBVazio()
{
    REGISTRO_ARVORE_B *registro = malloc(sizeof(REGISTRO_ARVORE_B));
    registro->alturaNo = 0;
    registro->nroChaves = 0;
    for (int i = 0; i < ORDEM_ARVORE_B - 1; i++)
    {
        registro->chaves[i] = -1;
    }
    for (int i = 0; i < ORDEM_ARVORE_B - 1; i++)
    {
        registro->byteOffsets[i] = -1;
    }
    for (int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        registro->descendentes[i] = -1;
    }

    return registro;
}

// insere uma chave no registro de árvore B
bool inserirChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave, long long int byteOffset)
{
    if (registro->nroChaves == ORDEM_ARVORE_B - 1) // se o registro estiver cheio
    {
        return false;
    }
    else if (registro->nroChaves == 0) // se o registro estiver vazio
    {
        registro->chaves[0] = chave;
        registro->byteOffsets[0] = byteOffset;
        registro->nroChaves++;
    }
    else // se o registro nao estiver vazio nem cheio
    {
        int posicao = 0;
        for(int i = 0; i < registro->nroChaves; i++)
        {
            if(registro->chaves[i] == chave) // se a chave ja existe
            {
                return false;
            }

            if(registro->chaves[i] > chave)
            {
                posicao = i;
                break;
            }

            posicao++;
        }

        for(int i = posicao; i < registro->nroChaves; i++)
        {
            registro->chaves[i + 1] = registro->chaves[i];
            registro->byteOffsets[i + 1] = registro->byteOffsets[i];
        }
        registro->chaves[posicao] = chave;
        registro->byteOffsets[posicao] = byteOffset;
        registro->nroChaves++;
    }

    return true;
}

// remove uma chave do registro de árvore B
bool removerChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave)
{
    if (registro->nroChaves == 0) // se o registro estiver vazio
    {
        return false;
    }
    else
    {
        int i = 0;
        while (i < registro->nroChaves && registro->chaves[i] != chave) // procura a chave
        {
            i++;
        }
        if (i == registro->nroChaves) // nao achou a chave
        {
            return false;
        }
        else
        {
            for (int j = i; j < registro->nroChaves - 1; j++)
            {
                registro->chaves[j] = registro->chaves[j + 1]; // reposiciona as chaves
                registro->byteOffsets[j] = registro->byteOffsets[j + 1]; // reposiciona os byte offsets
            }
            registro->nroChaves--;
        }
    }

    return true;
}

// insere um descendente no registro de árvore B
bool inserirDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente, int chaveDescendente)
{
    if (!registro || registro->nroChaves == 0)
    {
        return false;
    }

    int i = 0;

    while (i < registro->nroChaves && registro->chaves[i] < chaveDescendente) // acha a posicao do descendente
    {
        if(registro->chaves[i] == chaveDescendente) // se a chave ja existe
        {
            return false;
        }
        i++;
    }

    if(registro->descendentes[i] != -1) // se a posicao ja esta ocupada
    {
        return false;
    }

    registro->descendentes[i] = descendente; // insere o descendente na posicao em que Ci < chaveDescendente < Ci+1

    return true;
}

bool removerDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente)
{
    if (registro->nroChaves == 0)
    {
        return false;
    }
    
    int i = 0;

    while (i < registro->nroChaves && registro->descendentes[i] != descendente) // acha a posicao do descendente
    {
        i++;
    }

    if(i == ORDEM_ARVORE_B) // nao achou o descendente
    {
        return false;
    }

    registro->descendentes[i] = -1; // remove o descendente

    return true;
}

int getAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return -1;
    }
    
    int alturaNo = registro->alturaNo;

    return alturaNo;
}

bool setAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro, int alturaNo)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        registro->alturaNo = alturaNo;
    }

    return true;
}

int getNroChavesRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return -1;
    }
    
    int nroChaves = registro->nroChaves;

    return nroChaves;
}

int getChave(REGISTRO_ARVORE_B *registro, int posicao)
{
    if (registro == NULL || posicao < 0 || posicao >= ORDEM_ARVORE_B - 1)
    {
        return -1;
    }

    return registro->chaves[posicao];
}

long long int getByteOffsetRegistroArvoreB(REGISTRO_ARVORE_B *registro, int posicao)
{
    if (registro == NULL || posicao < 0 || posicao >= ORDEM_ARVORE_B - 1)
    {
        return -1;
    }

    return registro->byteOffsets[posicao];
}

int getDescendente(REGISTRO_ARVORE_B *registro, int posicao)
{
    if (registro == NULL || posicao < 0 || posicao >= ORDEM_ARVORE_B)
    {
        return -1;
    }

    return registro->descendentes[posicao];
}

bool apagarRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        free(registro);
    }

    return true;
}

bool imprimirRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        printf("Altura: %d\n", registro->alturaNo);
        printf("Nro chaves: %d\n", registro->nroChaves);
        printf("Chaves: ");
        for (int i = 0; i < registro->nroChaves; i++)
        {
            printf("%d ", registro->chaves[i]);
        }
        printf("\n");
        printf("Byte offsets: ");
        for (int i = 0; i < registro->nroChaves; i++)
        {
            printf("%lld ", registro->byteOffsets[i]);
        }
        printf("Descendentes: ");
        for (int i = 0; i < registro->nroChaves + 1; i++)
        {
            printf("%d ", registro->descendentes[i]);
        }
        printf("\n");
    }

    return true;
}

REGISTRO_ARVORE_B *lerRegistroArvoreB(FILE *arquivo, int rrn)
{
    REGISTRO_ARVORE_B *registro = criarRegistroArvoreBVazio();
    if (registro == NULL || arquivo == NULL)
    {
        return NULL;
    }
    
    long long int byteOffset = rrn * TAMANHO_REGISTRO_ARVORE_B;

    fseek(arquivo, byteOffset, SEEK_SET);

    fread(&registro->alturaNo, sizeof(int), 1, arquivo);
    fread(&registro->nroChaves, sizeof(int), 1, arquivo);
    for(int i = 0; i < ORDEM_ARVORE_B -1; i++)
    {
        fread(&registro->chaves[i], sizeof(int), 1, arquivo);
        fread(&registro->byteOffsets[i], sizeof(long long int), 1, arquivo);
    }
    fread(registro->descendentes, sizeof(int), ORDEM_ARVORE_B, arquivo);

    return registro;
}

bool escreverRegistroArvoreB(REGISTRO_ARVORE_B *registro, FILE *arquivo, int rrn)
{
    if (registro == NULL || arquivo == NULL)
    {
        return false;
    }
    
    long long int byteOffset = rrn * TAMANHO_REGISTRO_ARVORE_B;

    fseek(arquivo, byteOffset, SEEK_SET);

    fwrite(&registro->alturaNo, sizeof(int), 1, arquivo);
    fwrite(&registro->nroChaves, sizeof(int), 1, arquivo);
    for(int i = 0; i < ORDEM_ARVORE_B - 1; i++)
    {
        fwrite(&registro->chaves[i], sizeof(int), 1, arquivo);
        fwrite(&registro->byteOffsets[i], sizeof(long long int), 1, arquivo);
    }
    fwrite(registro->descendentes, sizeof(int), ORDEM_ARVORE_B, arquivo);

    return true;
}