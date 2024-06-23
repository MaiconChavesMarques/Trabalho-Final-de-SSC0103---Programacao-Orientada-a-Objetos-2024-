#include "inserirDado.h"

// escrevendo o ultimo em todos
void inserirNovoDado(char *arquivoBinario, char *arquivoIndice, int numOperacoes)
{
    FILE *arquivoBin = fopen(arquivoBinario, "rb+");
    FILE *arquivoInd = fopen(arquivoIndice, "rb+");

    if (arquivoBin == NULL || arquivoInd == NULL)
    {
        fclose(arquivoBin);
        fclose(arquivoInd);
        return;
    }
    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBin);

    if(getStatus(cabecalho) == '0')
    {
        //printf("Falha no processamento do arquivo.\n"); // erro ja eh printado uma vez
        apagarCabecalho(cabecalho);
        fclose(arquivoBin);
        fclose(arquivoInd);
        return;
    }

    LISTA_INDICE *lista = criarListaIndice();
    carregarIndice(lista, arquivoInd); // carrega o arquivo de indice

    REMOVIDOS *removidos = criarListaRemovidos(arquivoBin);

    REGISTRO **registros = malloc(sizeof(REGISTRO *) * numOperacoes);

    int id;
    char idadeStr[10];
    char **nomeJogador = malloc(sizeof(char*) * numOperacoes);
    char **nacionalidade = malloc(sizeof(char*) * numOperacoes);
    char **nomeClube = malloc(sizeof(char*) * numOperacoes);

    for(int i = 0; i < numOperacoes; i++)
    {
        nomeJogador[i] = malloc(sizeof(char) * 50);
        nacionalidade[i] = malloc(sizeof(char) * 50);
        nomeClube[i] = malloc(sizeof(char) * 50);
    }

    for(int i = 0; i < numOperacoes; i++)
    {
        // le o input do usuario
        scanf("%i", &id);
        scan_quote_string(idadeStr);
        scan_quote_string(nomeJogador[i]);
        scan_quote_string(nacionalidade[i]);
        scan_quote_string(nomeClube[i]);
        REGISTRO_INDICE *registroIndice = buscarRegistroIndice(lista, id);

        if(registroIndice != NULL) // registro ja existe
        {
            nomeJogador[i] = '\0';
            nacionalidade[i] = '\0';
            nomeClube[i] = '\0';
            registros[i] = criarRegistro('1',
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         nomeJogador[i],
                                         0,
                                         nomeClube[i],
                                         0,
                                         nacionalidade[i]);
            continue;
        }

        int idade = -1;

        if(strcmp(idadeStr, "NULO") == 0 || strcmp(idadeStr, "") == 0)
        {
            idade = -1;
        }
        else
        {
            idade = atoi(idadeStr);
        }

        if(strcmp(nomeJogador[i], "NULO") == 0 || strcmp(nomeJogador[i], "") == 0)
        {
            strcpy(nomeJogador[i], "");
        }

        if(strcmp(nacionalidade[i], "NULO") == 0 || strcmp(nacionalidade[i], "") == 0)
        {
            strcpy(nacionalidade[i], "");
        }

        if(strcmp(nomeClube[i], "NULO") == 0 || strcmp(nomeClube[i], "") == 0)
        {
            strcpy(nomeClube[i], "");
        }

        registros[i] = criarRegistro('0', 
                                     33 + strlen(nomeJogador[i]) + strlen(nomeClube[i]) + strlen(nacionalidade[i]), 
                                     -1,
                                     id,
                                     idade,
                                     strlen(nomeJogador[i]),
                                     nomeJogador[i],
                                     strlen(nacionalidade[i]),
                                     nacionalidade[i], 
                                     strlen(nomeClube[i]),
                                     nomeClube[i]);
    }

    // pega o byteOffset do best fit de cada registro
    long long int *byteOffsets = getBestFitArrayRegistros(removidos, registros, numOperacoes, arquivoBin);
    int tamanhoRegistroAtual = 0;

    for(int i = 0; i < numOperacoes; i++)
    {
        if(byteOffsets[i] == 0) // registro ja existe
        {
            continue;
        }
        if(byteOffsets[i] == -1) // registro insere no fim
        {
            tamanhoRegistroAtual = 0;
            fseek(arquivoBin, 0, SEEK_END);
            byteOffsets[i] = ftell(arquivoBin);
            setProxByteOffset(cabecalho, byteOffsets[i] + get_tamanhoRegistro(registros[i]));
            writeProxByteOffsetCabecalho(cabecalho, arquivoBin);
        }
        else
        {
            REGISTRO *registro = lerRegistroFromBin(byteOffsets[i], arquivoBin);
            tamanhoRegistroAtual = get_tamanhoRegistro(registro);
            liberarRegistro(registro);
        }

        set_prox(registros[i], -1);

        // escrevendo arquivo
        setStatus(cabecalho, '0');
        writeStatusCabecalho(cabecalho, arquivoBin);

        // escreve os dados do registro no arquivoBin
        escreverRegistro(registros[i], byteOffsets[i], tamanhoRegistroAtual, arquivoBin);

        // terminou de escrever o arquivo
        setStatus(cabecalho, '1');
        writeStatusCabecalho(cabecalho, arquivoBin);

        // cria o registro de indice adequado
        REGISTRO_INDICE *registroIndice = criarRegistroIndice();
        setIndexRegistroIndice(registroIndice, get_id(registros[i]));
        setByteOffsetRegistroIndice(registroIndice, byteOffsets[i]);

        long long int byteOffsetArquivoIndice = buscarPosicaoArquivoIndice(get_id(registros[i]), arquivoInd);

        insertInPosicaoBinIndice(registroIndice, arquivoInd, byteOffsetArquivoIndice);

        apagarRegistroIndice(registroIndice);
    }

    for(int i = 0; i < numOperacoes; i++)
    {
        liberarRegistro(registros[i]);
    }

    free(registros);
    free(byteOffsets);

    free(nomeJogador);
    free(nacionalidade);
    free(nomeClube);

    apagarCabecalho(cabecalho);
    apagarListaRemovidos(removidos);
    apagarListaIndice(lista); 

    fclose(arquivoBin);
    fclose(arquivoInd);
}