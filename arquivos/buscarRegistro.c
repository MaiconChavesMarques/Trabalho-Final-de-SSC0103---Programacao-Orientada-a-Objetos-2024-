#include "buscarRegistro.h"
#define BYTEOFFSET 25 // primeiro byte apos cabecalho

REGISTRO **buscarRegistro(char *chave, char *operacao, CABECALHO *cabecalho, FILE *file)
{
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho);

    if(numRegistros == 0)
    {
        printf("Registro inexistente\n\n");
        return NULL;
    }

    if(strcmp(operacao, "id") == 0)
    {
        return buscarId(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nome") == 0)
    {
        return buscarNome(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "idade") == 0)
    {
        return buscarIdade(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nomeClube") == 0)
    {
        return buscarNomeClube(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nacionalidade") == 0)
    {
        return buscarNacionalidade(chave, numRegistros, file);
    }
    else
    {
        printf("Campo invalido\n");
        return NULL;
    }
}

REGISTRO **buscarId(char *id, int numRegistros, FILE *file)
{
    REGISTRO **registros = malloc(sizeof(REGISTRO *));
    registros[0] = NULL;
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    int idInt = atoi(id);

    int qtdRegistrosEncontrados = 0;

    for(int i = 0; i < numRegistros; i++)
    {
        registros[qtdRegistrosEncontrados] = lerRegistroFromBin(byteOffset, file);
        byteOffset += get_tamanhoRegistro(registros[qtdRegistrosEncontrados]);
        if(get_id(registros[qtdRegistrosEncontrados]) == idInt)
        {
            qtdRegistrosEncontrados++;
            registros = realloc(registros, (qtdRegistrosEncontrados + 1) * sizeof(REGISTRO *));
        }
    }

    if(qtdRegistrosEncontrados == 0)
    {
        registros[0] = NULL;
    }

    return registros;
}

REGISTRO **buscarNome(char *nome, int numRegistros, FILE *file)
{
    REGISTRO **registros = malloc(sizeof(REGISTRO *));
    registros[0] = NULL;
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    int qtdRegistrosEncontrados = 0;

    for(int i = 0; i < numRegistros; i++)
    {
        registros[qtdRegistrosEncontrados] = lerRegistroFromBin(byteOffset, file);
        byteOffset += get_tamanhoRegistro(registros[qtdRegistrosEncontrados]);
        if(strcmp(get_nome(registros[qtdRegistrosEncontrados]), nome) == 0)
        {
            qtdRegistrosEncontrados++;
            registros = realloc(registros, (qtdRegistrosEncontrados + 1) * sizeof(REGISTRO *));
        }
    }

    if(qtdRegistrosEncontrados == 0)
    {
        registros[0] = NULL;
    }

    return NULL;
}

REGISTRO **buscarIdade(char *idade, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    int idadeInt = atoi(idade);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(get_idade(registro) == idadeInt)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO **buscarNomeClube(char *nomeClube, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(strcmp(get_nomeClube(registro), nomeClube) == 0)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO **buscarNacionalidade(char *nacionalidade, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(strcmp(get_nacionalidade(registro), nacionalidade) == 0)
        {
            return registro;
        }
    }

    return NULL;
}