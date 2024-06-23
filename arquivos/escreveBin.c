#include "escreveBin.h"
#include "cabecalho.h"
#include "arvoreB.h"
#include "funcoes_fornecidas.h"

// Função que pega os registros do arquivo binário e imprime eles na tela
void imprimeRegistrosFromBin(char *filePath)
{
    int impressoes = 0;
    FILE *file = fopen(filePath, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    if (file == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    int i = 0;

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = getCabecalhoFromBin(file);

    if (getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.");
        fclose(file); // fecha o arquivo
        return;
    }

    long long int byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
    byteOffset = 25;

    if (numRegistros == 0) // verifica se o arquivo não possui registros
    {
        printf("Registro inexistente.\n\n");
        fclose(file); // fecha o arquivo
        return;
    }

    for (i = 0; i < numRegistros; i++)
    {
        REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário
        byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
        impressoes += imprimeRegistro(registro);
        liberarRegistro(registro); // libera a memória do registro
    }

    if (impressoes == 0)
    {
        printf("Registro inexistente.\n\n");
    }

    apagarCabecalho(cabecalho); // libera a memória do cabeçalho

    fclose(file); // fecha o arquivo
    return;
}

int imprimeRegistro(REGISTRO *registro)
{
    if (get_removido(registro) == '0')
    { // se o registro não foi removido, imprime seus dados na tela

        // recebe o valor dos atributos do registro
        int id = get_id(registro);
        int idade = get_idade(registro);
        char *nomeClube = get_nomeClube(registro);
        char *nacionalidade = get_nacionalidade(registro);
        char *nomeJogador = get_nomeJogador(registro);

        printf("%d\n", id);
        printf("%d\n", idade);

        //printf("Nome do Jogador: ");
        if (strcmp(nomeJogador, "SEM DADO") == 0) // se o nome do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do jogador
        {
            for (int j = 0; j < get_tamNomeJogador(registro); j++)
            {
                printf("%c", nomeJogador[j]);
            }
            printf("\n");
        }

        //printf("Nacionalidade do Jogador: ");
        if (strcmp(nacionalidade, "SEM DADO") == 0) // se a nacionalidade for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere da nacionalidade
        {
            for (int j = 0; j < get_tamNacionalidade(registro); j++)
            {
                printf("%c", nacionalidade[j]);
            }
            printf("\n");
        }

        //printf("Clube do Jogador: ");
        if (strcmp(nomeClube, "SEM DADO") == 0) // se o nome do clube for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do clube
        {
            for (int j = 0; j < get_tamNomeClube(registro); j++)
            {
                printf("%c", nomeClube[j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void imprimeRegistrosBuscados(char *arquivo)
{
    int numOperacoes;
    scanf("%d", &numOperacoes); // lê o número de buscas a serem feitas

    for (int i = 0; i < numOperacoes; i++)
    {
        int impressoes = 0;
        int m;
        scanf("%i", &m); // lê o número de parâmetros da busca

        FILE *file = fopen(arquivo, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
        if (file == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }

        // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
        CABECALHO *cabecalho = getCabecalhoFromBin(file);

        if (getStatus(cabecalho) == '0')
        {
            printf("Falha no processamento do arquivo.");
            fclose(file); // fecha o arquivo
            return;
        }

        long long int byteOffset = getProxByteOffset(cabecalho);
        int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
        byteOffset = 25;

        if (numRegistros == 0) // verifica se o arquivo não possui registros
        {
            printf("Registro inexistente.\n\n");
            fclose(file); // fecha o arquivo
            return;
        }

        char campos[5][50];
        char parametros[5][50];
        int id, idade;
        char nome[50], nomeClube[50], nacionalidade[50];
        for (int j = 0; j < m; j++)
        {
            scanf("%s", campos[j]); // lê um parâmetro da busca
            if (strcmp(campos[j], "id") == 0)
            {
                scanf("%i", &id); // lê o id da busca
                snprintf(parametros[j], 50, "%i", id);
                printf("%s\n", parametros[j]);
            }
            else if (strcmp(campos[j], "nome") == 0)
            {
                scan_quote_string(nome);
                strcpy(parametros[j], nome);
            }
            else if (strcmp(campos[j], "idade") == 0)
            {
                scanf("%i", &idade);
                snprintf(parametros[j], 50, "%i", idade);
            }
            else if (strcmp(campos[j], "nomeClube") == 0)
            {
                scan_quote_string(nomeClube);
                strcpy(parametros[j], nomeClube);
            }
            else if (strcmp(campos[j], "nacionalidade") == 0)
            {
                scan_quote_string(nacionalidade);
                strcpy(parametros[j], nacionalidade);
            }
            else
            {
                printf("Campo invalido\n");
            }
        }

        printf("Busca %d\n", i + 1);
        printf("\n");

        for (int j = 0; j < numRegistros; j++)
        {
            REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário
            byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro

            int imprimir = 1;
            if (get_removido(registro) == '1')
            {
                imprimir = 0;
            }
            else
            {
                for (int k = 0; k < m; k++)
                {
                    if (strcmp(campos[k], "id") == 0)
                    { // verifica se o parâmetro da busca é o id
                        if (id != get_id(registro))
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nome") == 0)
                    {
                        if (strcmp(nome, get_nomeJogador(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "idade") == 0)
                    {
                        if (idade != get_idade(registro))
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nomeClube") == 0)
                    {
                        if (strcmp(nomeClube, get_nomeClube(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nacionalidade") == 0)
                    {
                        if (strcmp(nacionalidade, get_nacionalidade(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                }
            }
            if (imprimir == 1)
            {
                imprimeRegistro(registro);
                impressoes++;
            }
        }
        fclose(file);
        apagarCabecalho(cabecalho); // libera a memória do cabeçalho

        /*if(impressoes == 0) {
          printf("Registro inexistente.\n\n");
        }*/
    }
}

void removerRegistrosBuscados(char *arquivoBin, char *arquivoIndice)
{
    FILE *file = fopen(arquivoBin, "rb+"); // abre o arquivo binário no modo leitura e escrita
    FILE *fileIndices = fopen(arquivoIndice, "rb+"); // abre o arquivo de índices no modo leitura e escrita
    if (file == NULL || fileIndices == NULL) // verifica se ocorreu um erro ao abrir os arquivos
    {
        // printf("Falha no processamento do arquivo.\n"); // já tem no lerBinCriarIndice
        if(file != NULL) fclose(file);
        if(fileIndices != NULL) fclose(fileIndices);
        return;
    }

    LISTA_INDICE *listaIndices = criarListaIndice(); // cria uma lista de índices
    carregarIndice(listaIndices, fileIndices); // carrega os índices do arquivo para a lista

    REMOVIDOS *listaRemovidos = criarListaRemovidos(file); // cria uma lista de registros removidos

    // cria um cabeçalho e chama a função getCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = getCabecalhoFromBin(file);

    if (getStatus(cabecalho) == '0') // verifica o status do cabeçalho
    {
        // printf("Falha no processamento do arquivo.\n"); // já tem no lerBinCriarIndice
        fclose(file); // fecha o arquivo
        fclose(fileIndices);
        apagarCabecalho(cabecalho);
        apagarListaIndice(listaIndices);
        return;
    }

    // status dos arquivos de dados e de indices = 0 
    char status = '0';
    fseek(file, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, file);

    fseek(fileIndices, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, fileIndices);

    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros

    if (numRegistros == 0) // verifica se o arquivo não possui registros
    {
        printf("Registro inexistente.\n\n");
        fclose(file); // fecha o arquivo
        return;
    }

    int numOperacoes;
    scanf("%d", &numOperacoes); // lê o número de buscas a serem feitas

    for (int i = 0; i < numOperacoes; i++) // para cada operação de busca
    {
        long long byteOffset = 25; // define o byteOffset inicial
        int removidos = 0; // contador de registros removidos
        int m;
        scanf("%d", &m); // lê o número de parâmetros da busca

        char campos[5][50]; // array para armazenar os campos de busca
        int id = -1, idade; // variáveis para armazenar os valores dos parâmetros
        char nome[50], nomeClube[50], nacionalidade[50]; // variáveis para armazenar os valores dos parâmetros
        for (int j = 0; j < m; j++)
        {
            scanf("%s", campos[j]); // lê um parâmetro da busca
            if (strcmp(campos[j], "id") == 0)
            {
                scanf("%d", &id); // lê o id da busca
                removeById(id, listaIndices, file, fileIndices, listaRemovidos, cabecalho, arquivoIndice); // remove o registro pelo id
                removidos++;
            }
            else if (strcmp(campos[j], "nomeJogador") == 0)
            {
                scan_quote_string(nome); // lê o nome do jogador
            }
            else if (strcmp(campos[j], "idade") == 0)
            {
                scanf("%d", &idade); // lê a idade
            }
            else if (strcmp(campos[j], "nomeClube") == 0)
            {
                scan_quote_string(nomeClube); // lê o nome do clube
            }
            else if (strcmp(campos[j], "nacionalidade") == 0)
            {
                scan_quote_string(nacionalidade); // lê a nacionalidade
            }
        }

        if (id == -1) { // se não foi especificado um id, busca pelos outros parâmetros
            for (int j = 0; j < numRegistros; j++) // para cada registro
            {
                REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário

                int remover = 1; // flag para indicar se o registro deve ser removido
                if (get_removido(registro) == '1')
                {
                    remover = 0; // indica se o registro não deve ser removido
                }
                else
                {
                    for (int k = 0; k < m; k++)
                    {
                        if (strcmp(campos[k], "nomeJogador") == 0)
                        {
                            if (strcmp(nome, get_nomeJogador(registro)) != 0)
                            {
                                remover = 0;
                            }
                        }
                        else if (strcmp(campos[k], "idade") == 0)
                        {
                            if (idade != get_idade(registro))
                            {
                                remover = 0;
                            }
                        }
                        else if (strcmp(campos[k], "nomeClube") == 0)
                        {
                            if (strcmp(nomeClube, get_nomeClube(registro)) != 0)
                            {
                                remover = 0;
                            }
                        }
                        else if (strcmp(campos[k], "nacionalidade") == 0)
                        {
                            if (strcmp(nacionalidade, get_nacionalidade(registro)) != 0)
                            {
                                remover = 0;
                            }
                        } else {
                            remover = 0;
                        }
                    }
                }
                if (remover == 1)
                {
                    char removed = '1';
                    char verificar;

                    fseek(file, byteOffset, SEEK_SET); // muda o ponteiro do arquivo para a posição do registro
                    fwrite(&removed, sizeof(char), 1, file); // marca o registro como removido
                    fseek(file, byteOffset, SEEK_SET); // volta o ponteiro para a posição do registro
                    fread(&verificar, sizeof(char), 1, file); // lê o registro para verificar a remoção

                    REGISTRO_INDICE *registroIndice = criarRegistroIndice(); // cria um registro de índice
                    setIndexRegistroIndice(registroIndice, get_id(registro)); // define o id do registro de índice
                    setByteOffsetRegistroIndice(registroIndice, byteOffset); // define o byteOffset do registro de índice

                    adicionarRegistroRemovido(listaRemovidos, registroIndice, get_tamanhoRegistro(registro)); // adiciona o registro removido à lista de removidos
                    removidos++; // incrementa o contador de registros removidos

                    setNroRegArq(cabecalho, getNroRegArq(cabecalho) - 1); // decrementa o número de registros no cabeçalho
                    setNroRem(cabecalho, getNroRem(cabecalho) + 1); // incrementa o número de registros removidos no cabeçalho

                    removerRegistroIndice(listaIndices, buscarPosicaoRegistroIndice(listaIndices, get_id(registro))); // remove o registro do índice
                    escreverRegistrosIndices(fileIndices, arquivoIndice, listaIndices); // escreve os registros de índices no arquivo

                    long long int byteOffsetAnteriorRemovidos = getMaiorByteOffsetMenorQue(listaRemovidos, get_id(registro)); // obtém o maior byteOffset menor que o atual
                    long long int byteOffsetProxRemovidos;

                    if(byteOffsetAnteriorRemovidos == -1) {
                        setTopo(cabecalho, byteOffset); // define o topo do cabeçalho
                        fseek(file, 1, SEEK_SET); // muda o ponteiro para a posição do topo no arquivo
                        fread(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // lê o próximo byteOffset removido
                        fseek(file, 1, SEEK_SET); // volta o ponteiro para a posição do topo no arquivo
                        fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no topo do arquivo
                    } else {
                        fseek(file, byteOffsetAnteriorRemovidos+5, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset removido no arquivo
                        fread(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // lê o próximo byteOffset removido
                        fseek(file, byteOffsetAnteriorRemovidos+5, SEEK_SET); // volta o ponteiro para a posição do próximo byteOffset removido no arquivo
                        fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no arquivo
                    }

                    if(byteOffset == obterMaiorByteOffset(listaIndices)) {
                        setProxByteOffset(cabecalho, byteOffset); // define o próximo byteOffset no cabeçalho
                        fseek(file, 9, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset no arquivo
                        fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no arquivo
                    }

                    fseek(file, byteOffset+5, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset removido no arquivo
                    fwrite(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // escreve o próximo byteOffset removido no arquivo

                    writeNroRegArqCabecalho(cabecalho, file); // escreve o número de registros no cabeçalho
                    writeNroRegRemCabecalho(cabecalho, file); // escreve o número de registros removidos no cabeçalho

                }
                byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
                free(registro);
            }
        }

    }

    apagarCabecalho(cabecalho); // libera a memória do cabeçalho

    // status dos arquivos de dados e de indices = 1 
    status = '1';
    fseek(file, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, file);

    fseek(fileIndices, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, fileIndices);

    apagarListaIndice(listaIndices);

    fclose(file); // fecha o arquivo de dados
    fclose(fileIndices); // fecha o arquivo de indices
}

void removeById(int id, LISTA_INDICE *listaIndices, FILE *file, FILE *fileIndices, REMOVIDOS *listaRemovidos, CABECALHO *cabecalho, char* arquivoIndice) {
    REGISTRO_INDICE *registroIndice = buscarRegistroIndice(listaIndices, id); // busca o registro de índice pelo id
    long long int byteOffset;
    if(registroIndice != NULL) {
        byteOffset = getByteOffsetRegistroIndice(registroIndice); // obtém o byteOffset do registro de índice
    }

    if(registroIndice != NULL && get_removido(buscarRegistroOffset(byteOffset, file)) == '0') { // se o registro existe e ainda não foi removido
        fseek(file, byteOffset, SEEK_SET); // muda o ponteiro do arquivo para a posição do registro
        char removed = '1';
        fwrite(&removed, sizeof(char), 1, file); // marca o registro como removido
        
        REGISTRO *registro = buscarRegistroOffset(byteOffset, file); // busca o registro pelo byteOffset
        if(registro)
        adicionarRegistroRemovido(listaRemovidos, registroIndice, get_tamanhoRegistro(registro)); // adiciona o registro removido à lista de removidos
        setNroRegArq(cabecalho, getNroRegArq(cabecalho) - 1); // decrementa o número de registros no cabeçalho
        setNroRem(cabecalho, getNroRem(cabecalho) + 1); // incrementa o número de registros removidos no cabeçalho

        removerRegistroIndice(listaIndices, buscarPosicaoRegistroIndice(listaIndices, id)); // remove o registro do índice
        escreverRegistrosIndices(fileIndices, arquivoIndice, listaIndices); // escreve os registros de índices no arquivo

        long long int byteOffsetAnteriorRemovidos = getMaiorByteOffsetMenorQue(listaRemovidos, id); // obtém o maior byteOffset menor que o atual
        long long int byteOffsetProxRemovidos;

        if(byteOffsetAnteriorRemovidos == -1) {
            setTopo(cabecalho, byteOffset); // define o topo do cabeçalho
            fseek(file, 1, SEEK_SET); // muda o ponteiro para a posição do topo no arquivo
            fread(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // lê o próximo byteOffset removido
            fseek(file, 1, SEEK_SET); // volta o ponteiro para a posição do topo no arquivo
            fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no topo do arquivo
        } else {
            fseek(file, byteOffsetAnteriorRemovidos+5, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset removido no arquivo
            fread(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // lê o próximo byteOffset removido
            fseek(file, byteOffsetAnteriorRemovidos+5, SEEK_SET); // volta o ponteiro para a posição do próximo byteOffset removido no arquivo
            fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no arquivo
        }

        if(byteOffset == obterMaiorByteOffset(listaIndices)) {
            setProxByteOffset(cabecalho, byteOffset); // define o próximo byteOffset no cabeçalho
            fseek(file, 9, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset no arquivo
            fwrite(&byteOffset, sizeof(long long int), 1, file); // escreve o byteOffset no arquivo
        }

        fseek(file, byteOffset+5, SEEK_SET); // muda o ponteiro para a posição do próximo byteOffset removido no arquivo
        fwrite(&byteOffsetProxRemovidos, sizeof(long long int), 1, file); // escreve o próximo byteOffset removido no arquivo

        writeNroRegArqCabecalho(cabecalho, file); // escreve o número de registros no cabeçalho
        writeNroRegRemCabecalho(cabecalho, file); // escreve o número de registros removidos no cabeçalho
    }
}

bool escreverRegistro(REGISTRO *registro, int byteOffset, int tamRegistroAtual, FILE *arquivoBin)
{
    if(registro == NULL || byteOffset < 25 || arquivoBin == NULL)
    {
        return false;
    }

    char removido = get_removido(registro);
    int tamRegistroOriginal = get_tamanhoRegistro(registro);
    int tamanhoRegistro = tamRegistroOriginal;
    long long int prox = get_prox(registro);
    int id = get_id(registro);
    int idade = get_idade(registro);
    int tamNomeJogador = get_tamNomeJogador(registro);
    char *nomeJogador = get_nomeJogador(registro);
    int tamNacionalidade = get_tamNacionalidade(registro);
    char *nacionalidade = get_nacionalidade(registro);
    int tamNomeClube = get_tamNomeClube(registro);
    char *nomeClube = get_nomeClube(registro);

    fseek(arquivoBin, byteOffset, SEEK_SET); // muda o ponteiro do arquivo para a posição do registro

    if(tamRegistroAtual != 0)
    {
        set_tamanhoRegistro(registro, tamRegistroAtual);
        tamanhoRegistro = tamRegistroAtual;
    }

    fwrite(&removido, sizeof(char), 1, arquivoBin); // escreve o campo removido no arquivo
    fwrite(&tamanhoRegistro, sizeof(int), 1, arquivoBin); // escreve o campo tamanhoRegistro no arquivo
    fwrite(&prox, sizeof(long long int), 1, arquivoBin); // escreve o campo prox no arquivo
    fwrite(&id, sizeof(int), 1, arquivoBin); // escreve o campo id no arquivo
    fwrite(&idade, sizeof(int), 1, arquivoBin); // escreve o campo idade no arquivo
    fwrite(&tamNomeJogador, sizeof(int), 1, arquivoBin); // escreve o campo tamNomeJogador no arquivo
    fwrite(nomeJogador, sizeof(char), tamNomeJogador, arquivoBin); // escreve o campo nomeJogador no arquivo
    fwrite(&tamNacionalidade, sizeof(int), 1, arquivoBin); // escreve o campo tamNacionalidade no arquivo
    fwrite(nacionalidade, sizeof(char), tamNacionalidade, arquivoBin); // escreve o campo nacionalidade no arquivo
    fwrite(&tamNomeClube, sizeof(int), 1, arquivoBin); // escreve o campo tamNomeClube no arquivo
    fwrite(nomeClube, sizeof(char), tamNomeClube, arquivoBin); // escreve o campo nomeClube no arquivo

    for (int i = 0; i < tamRegistroAtual - tamRegistroOriginal; i++)
    {
        fwrite("$", sizeof(char), 1, arquivoBin); // preenche o registro com '$'
    }

    return true;
}

void criarArquivoArvoreB(char *arquivoBin, char *arquivoArvB)
{
    FILE *arquivoBinario = fopen(arquivoBin, "rb"); // abre o arquivo binário no modo escrita
    FILE *arquivoArvoreB = fopen(arquivoArvB, "wb+"); // abre o arquivo de índices no modo escrita

    if(!arquivoBinario || !arquivoArvoreB)
    {
        printf("Falha no processamento do arquivo.\n");
        if(arquivoBinario) fclose(arquivoBinario);
        if(arquivoArvoreB) fclose(arquivoArvoreB);
        return;
    }

    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBinario); // lê o cabeçalho do arquivo binário

    if(getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoBinario);
        fclose(arquivoArvoreB);
        apagarCabecalho(cabecalho);
        return;
    }

    CABECALHO_ARVORE_B *cabecalhoArvoreB = criarCabecalhoArvoreBVazio(); // cria um cabeçalhos
    setStatusCabecalhoArvoreB(cabecalhoArvoreB, '0');
    escreverCabecalhoArvoreB(arquivoArvoreB, cabecalhoArvoreB); // escreve o cabeçalho no arquivo

    // pula o cabecalho
    long long int posicao = 25;

    REGISTRO_INDICE *registroIndice = criarRegistroIndice();

    // quantidade de registros no arquivo
    int quantidade = getNroRegArq(cabecalho) + getNroRem(cabecalho);

    apagarCabecalho(cabecalho);

    for(int i = 0; i < quantidade; i++)
    {
        REGISTRO *registro = lerRegistroFromBin(posicao, arquivoBinario); // lê um registro do arquivo binário

        if(get_removido(registro) == '1') //pula o registro removido
        {
            posicao += get_tamanhoRegistro(registro);
            continue;
        }

        int chave = get_id(registro); // obtém a chave do registro
        long long int byteOffset = posicao; // obtém o byteOffset do registro
        
        inserirArvoreB(arquivoArvoreB, chave, byteOffset); // insere o registro na árvore B

        posicao += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
        liberarRegistro(registro); // libera a memória do registro
    }

    imprimirArvoreB(arquivoArvoreB); // imprime a árvore B

    apagarCabecalhoArvoreB(cabecalhoArvoreB); // libera a memória do cabeçalho da árvore B
    cabecalhoArvoreB = lerCabecalhoArvoreB(arquivoArvoreB); // lê o cabeçalho da árvore B
    setStatusCabecalhoArvoreB(cabecalhoArvoreB, '1'); // define o status do cabeçalho como consistente
    escreverCabecalhoArvoreB(arquivoArvoreB, cabecalhoArvoreB); // escreve o cabeçalho no arquivo
}