#include "criarIndice.h"

// Função que busca a posição de inserção de um registro no arquivo de índice
// Nao necessita armazenamento na memoria principal, porem eh O(n)
int buscaArquivoIndice(int id, FILE *arquivoInd)
{
    int quantidade;
    int posicao = 1; // primeiro byte apos cabecalho
    fread(&quantidade, sizeof(int), 1, arquivoInd);

    fseek(arquivoInd, posicao, SEEK_SET);

    int index = -1;

    while(fread(&index, sizeof(int), 1, arquivoInd) == 1)
    {
        if(index == id)
        {
            return -1; // indice ja existe
        }
        else if (id < index)
        {
            return posicao; // byte offset do primeiro registro com index maior que id
        }

        posicao = posicao + sizeof(int) + sizeof(long long int); // pula para o proximo registro
        fseek(arquivoInd, posicao, SEEK_SET);
    }

    return posicao; // nao existe nenhum registro com index maior que id
}

// Função que insere um registro no arquivo de índice na posição posicao
int insertInPosicaoBinIndice (REGISTRO_INDICE *registro, FILE *arquivoInd, long long int posicao)
{
    fseek(arquivoInd, 0, SEEK_SET);

    char status = '0';

    fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 0

    fseek(arquivoInd, 0, SEEK_END);
    long long int bytesToMove = ftell(arquivoInd) - posicao;

    char *buffer = (char *) malloc(bytesToMove);
    if (buffer == NULL)
    {
        fseek(arquivoInd, 0, SEEK_SET);
        status = '1';
        fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 1
        printf("Erro ao alocar memoria\n");
        return 0;
    }

    fseek(arquivoInd, posicao, SEEK_SET);
    fread(buffer, bytesToMove, 1, arquivoInd); // le todos os bytes no buffer

    fseek(arquivoInd, posicao + sizeof(int) + sizeof(long long int), SEEK_SET);

    fwrite(buffer, bytesToMove, 1, arquivoInd); // reescreve o buffer no arquivo separando posicao pro novo registro

    fseek(arquivoInd, posicao, SEEK_SET);

    // escreve o novo registro
    int index = getIndexRegistroIndice(registro);
    long long int byteOffset = getByteOffsetRegistroIndice(registro);
    fwrite(&index, sizeof(int), 1, arquivoInd);
    fwrite(&byteOffset, sizeof(long long int), 1, arquivoInd);

    free(buffer);

    fseek(arquivoInd, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 1

    return 1;
}

void escreverRegistrosIndices(FILE *arquivoIndices, char *arquivoIndicesNome, LISTA_INDICE *listaIndices) {
    fclose(arquivoIndices);
    
    // Abre o arquivo para escrita binária
    arquivoIndices = fopen(arquivoIndicesNome, "wb");
    if (arquivoIndices == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char status = '0';
    fwrite(&status, sizeof(char), 1, arquivoIndices);

    // Escreve os registros no arquivo
    for(int i = 0; i < getTamanhoLista(listaIndices); i++) {
        int index = getIndexRegistroIndice(getRegistroIndice(listaIndices, i));
        long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(listaIndices, i));
        fwrite(&index, sizeof(int), 1, arquivoIndices);
        fwrite(&byteOffset, sizeof(long long int), 1, arquivoIndices);
    }

    // Garante que todos os dados sejam escritos no disco
    fflush(arquivoIndices);
    fclose(arquivoIndices);

    // Reabre o arquivo para leitura/escrita binária
    arquivoIndices = fopen(arquivoIndicesNome, "rb+");
    if (arquivoIndices == NULL) {
        printf("EFalha no processamento do arquivo.\n");
        return;
    }

    // Posiciona o ponteiro no início do arquivo
    fseek(arquivoIndices, 0, SEEK_SET);

    char status2 = '1';
    fwrite(&status2, sizeof(char), 1, arquivoIndices);

    fseek(arquivoIndices, 0, SEEK_SET);
    char verificaStatus;
    fread(&verificaStatus, sizeof(char), 1, arquivoIndices);
}

int removeFromPosicaoBinIndice(FILE *arquivoInd, long long int posicao, char *arquivoIndName)
{
    fseek(arquivoInd, 0, SEEK_SET);

    char status = '0';
    fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 0

    // Abrir arquivo temporário
    FILE *arquivoTemp = fopen("temp.bin", "wb");
    if (arquivoTemp == NULL)
    {
        fseek(arquivoInd, 0, SEEK_SET);
        status = '1';
        fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 1
        printf("Erro ao criar arquivo temporário\n");
        return 0;
    }

    // Copiar os dados até a posição de remoção para o arquivo temporário
    fseek(arquivoInd, 1, SEEK_SET); // ignora o status
    char buffer;
    for (long long int i = 1; i < posicao; i++)
    {
        fread(&buffer, sizeof(char), 1, arquivoInd);
        fwrite(&buffer, sizeof(char), 1, arquivoTemp);
    }

    // Pular o tamanho do registro de índice a ser removido
    fseek(arquivoInd, sizeof(int) + sizeof(long long int), SEEK_CUR);

    // Copiar o restante dos dados para o arquivo temporário
    while (fread(&buffer, sizeof(char), 1, arquivoInd) == 1)
    {
        fwrite(&buffer, sizeof(char), 1, arquivoTemp);
    }

    // Fechar os arquivos
    fclose(arquivoTemp);
    fclose(arquivoInd);

    // Substituir o arquivo original pelo temporário
    remove(arquivoIndName);
    rename("temp.bin", arquivoIndName);

    // Reabrir o arquivo original
    arquivoInd = fopen(arquivoIndName, "rb+");
    if (arquivoInd == NULL)
    {
        printf("Erro ao reabrir o arquivo original\n");
        return 0;
    }

    fseek(arquivoInd, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, arquivoInd); // seta o status para 1

    return 1;
}

void imprimirRegistrosIndice(FILE *arquivoIndice)
{
    fseek(arquivoIndice, 1, SEEK_SET);
    
    int index = -1;
    long long int byteOffset = -1;

    while(fread(&index, sizeof(int), 1, arquivoIndice) == 1)
    {
        fread(&byteOffset, sizeof(long long int), 1, arquivoIndice);
    }
}

// funcao que le um arquivo de dados e cria um arquivo de indice
FILE *lerBinCriarIndice(FILE *arquivoBinario, char *arquivoIndice)
{
    FILE *arquivoInd = fopen(arquivoIndice, "wb+");
    if (arquivoInd == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoInd);
        fclose(arquivoBinario);
        return false;
    }
    
    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBinario);

    if (getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        apagarCabecalho(cabecalho);
        fclose(arquivoBinario); // fecha o arquivo
        fclose(arquivoInd);
        return false;
    }

    // seta o status do arquivo de indice como insonsistente
    char status = '0';
    fseek(arquivoInd, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivoInd);

    // pula o cabecalho
    long long int posicao = 25;

    REGISTRO_INDICE *registroIndice = criarRegistroIndice();

    // quantidade de registros no arquivo
    int quantidade = getNroRegArq(cabecalho) + getNroRem(cabecalho);

    apagarCabecalho(cabecalho);

    for(int i = 0; i < quantidade; i++)
    {
        REGISTRO *registro = lerRegistroFromBin(posicao, arquivoBinario);

        if(get_removido(registro) == '1') //pula o registro removido
        {
            posicao += get_tamanhoRegistro(registro);
            liberarRegistro(registro);
        } else {
            setIndexRegistroIndice(registroIndice, get_id(registro));
            setByteOffsetRegistroIndice(registroIndice, posicao);

            int posicaoInsercao = buscaArquivoIndice(get_id(registro), arquivoInd);
            insertInPosicaoBinIndice(registroIndice, arquivoInd, posicaoInsercao);

            posicao += get_tamanhoRegistro(registro);
            liberarRegistro(registro);
        }

    }

    apagarRegistroIndice(registroIndice);

    // seta o status do arquivo de indice como consistente
    status = '1';
    fseek(arquivoInd, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivoInd);

    //imprimirRegistrosIndice(arquivoInd);
    
    fclose(arquivoBinario);
    fclose(arquivoInd);

    return arquivoInd;

}