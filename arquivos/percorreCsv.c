#include "percorreCsv.h"

struct dados {
    int id;
    int idade;
    char *nome_jogador;
    char *nacionalidade;
    char *nomeClube;
};


// Função que lê uma linha do arquivo csv e salva os valores lidos na variável dados
void lerLinha(char *linha, DADOS *dados) {
    int contadores[5];
    int i = 0;
    int j = 0;
    int offset = 0;
    while(linha[i] != '\n' && linha[i] != '\0') { // enquanto não chegar no fim da linha
        if (linha[i] == ',') { // se encontrou uma vírbula, atribui o valor de i-offseet no contador para armazenar a quantidade de caracteres do dado e atualiza o offset para a posição do pŕoximo dado da linha
            contadores[j] = i - offset;
            offset = i + 1;
            j++; // atualiza a posição dos contadores
        }
        i++; // atualiza a posição da linha
    }
    contadores[j] = i - offset;

    // aloca espaço na memódia para armazenar as strings dos dados
    char *id = (char *) malloc((contadores[0] + 1) * sizeof(char));
    char *idade = (char *) malloc((contadores[1] + 1) * sizeof(char));
    char *nome_jogador = (char *) malloc((contadores[2] + 1) * sizeof(char));
    char *nacionalidade = (char *) malloc((contadores[3] + 1) * sizeof(char));
    char *nomeClube = (char *) malloc((contadores[4] + 1) * sizeof(char));

    // lê os caracteres da linha e armazena eles nas variáveis do tipo string
    i = 0;
    for(j = 0; j < contadores[0]; i++) {
        id[j] = linha[i];
        j++;
    }
    id[contadores[0]] = '\0';
    i++;
    for(j = 0; j < contadores[1]; j++) {
        idade[j] = linha[i];
        i++;
    }
    idade[contadores[1]] = '\0';
    i++;
    for(j = 0; j < contadores[2]; j++) {
        nome_jogador[j] = linha[i];
        i++;
    }
    nome_jogador[contadores[2]] = '\0';
    i++;
    for(j = 0; j < contadores[3]; j++) {
        nacionalidade[j] = linha[i];
        i++;
    }
    nacionalidade[contadores[3]] = '\0';
    i++;

    if (contadores[4] == 1)
      contadores[4]--; // contadores 4 está sempre com um a mais por algum motivo quando esta vazio. Suspeitaa: falta de virgula no final.

    for(j = 0; j < contadores[4]; j++) {
        nomeClube[j] = linha[i];
        i++;
    }
    nomeClube[contadores[4]] = '\0';

    dados->id = atoi(id); // converte o id lido para inteiro e salva em dados->id
    free(id); // libera a memória da string id

    if(atoi(idade) == 0) // se idade é 0, salva como -1 para indicar que é uma idade inválida
        dados->idade = -1;
    else // se não, salva ela como um inteiro
        dados->idade = atoi(idade);
    free(idade); // libera a memória da string idade
    
    // salva as strings dos dados na variável dados
    dados->nome_jogador = nome_jogador;
    dados->nacionalidade = nacionalidade;
    dados->nomeClube = nomeClube;
}

void escreveCabecalho(CABECALHO *cabecalho, FILE *arquivoBin) {
    writeStatusCabecalho(cabecalho, arquivoBin);
    writeTopoCabecalho(cabecalho, arquivoBin);
    writeProxByteOffsetCabecalho(cabecalho, arquivoBin);
    writeNroRegArqCabecalho(cabecalho, arquivoBin);
    writeNroRegRemCabecalho(cabecalho, arquivoBin);
}

void escreveRegistro(REGISTRO *registro, FILE *arquivoBin) {
    int removido = get_removido(registro);
    int tamRegistro = get_tamanhoRegistro(registro);
    long long int prox = get_prox(registro);
    int id = get_id(registro);
    int idade = get_idade(registro);
    int tamNomeJogador = get_tamNomeJogador(registro);
    char *nomeJogador = get_nomeJogador(registro);
    int tamNacionalidade = get_tamNacionalidade(registro);
    char *nacionalidade = get_nacionalidade(registro);
    int tamNomeClube = get_tamNomeClube(registro);
    char *nomeClube = get_nomeClube(registro);

    // escreve os campos do registro no arquivo
    fwrite(&removido, sizeof(char), 1, arquivoBin);
    fwrite(&tamRegistro, sizeof(int), 1, arquivoBin);
    fwrite(&prox, sizeof(long long int), 1, arquivoBin);
    fwrite(&id, sizeof(int), 1, arquivoBin);
    fwrite(&idade, sizeof(int), 1, arquivoBin);

    fwrite(&tamNomeJogador, sizeof(int), 1, arquivoBin);
    // escreve todos os caracteres do nome do jogador no arquivo
    for(int i=0; i<tamNomeJogador; i++) {
      fwrite(&nomeJogador[i], sizeof(char), 1, arquivoBin);
    }

    fwrite(&tamNacionalidade, sizeof(int), 1, arquivoBin);
    // escreve todos os caracteres da nacionalidade no arquivo
    for(int i=0; i<tamNacionalidade; i++) {
      fwrite(&nacionalidade[i], sizeof(char), 1, arquivoBin);
    }

    fwrite(&tamNomeClube, sizeof(int), 1, arquivoBin);
    // escreve todos os caracteres do nome do clube no arquivo
    for(int i=0; i<tamNomeClube; i++) {
      fwrite(&nomeClube[i], sizeof(char), 1, arquivoBin);
    }
}

// Função que seta os valores do cabeçalho de acordo com os valores do registro
void setCabecalho(CABECALHO *cabecalho, REGISTRO *registro, FILE *arquivoBin)
{
    if(get_removido(registro) == '0') {
        // se o registro não foi removido, incrementa o número de registros no arquivo
        setNroRegArq(cabecalho, getNroRegArq(cabecalho) + 1);
    } else {
        // se o registro foi removido, incrementa o número de registros removidos e seta o topo caso nao esteja setado
        if(getTopo(cabecalho) == -1)
            setTopo(cabecalho, ftell(arquivoBin));
        setNroRem(cabecalho, getNroRem(cabecalho) + 1);
    }

    setProxByteOffset(cabecalho, ftell(arquivoBin));
}

// Função que lê o arquivo csv e salva seus dados em uma lista de registros
void *lerCsvEscreveBin(char *nomeArquivoCsv, char *nomeArquivoBin) {
    FILE *arquivoCsv = fopen(nomeArquivoCsv, "r");
    FILE *arquivoBin = fopen(nomeArquivoBin, "wb");

    if (arquivoCsv == NULL) { // verifica se ocorreu um erro ao abrir o arquivo em modo de leitura
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoCsv);
        exit(1);
    }

    if (arquivoBin == NULL) { // verifica se ocorreu um erro ao abrir o arquivo em modo de escrita binária
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoBin);
        exit(1);
    }

    char linha[1090];
    int i = 0;

    CABECALHO *cabecalho = criarCabecalho();
    setStatus(cabecalho, '0');
    escreveCabecalho(cabecalho, arquivoBin);

    DADOS *dados = (DADOS *) malloc(sizeof(DADOS));

    REGISTRO *registro = criarRegistro('0', 0, -1, -1, -1, 0, "", 0, "", 0, "");

    while (fgets(linha, 1090, arquivoCsv) != NULL) {
        // pula a primeira linha
        if (i == 0) {
            i++;
            continue;
        }
        fseek(arquivoBin, 0, SEEK_END);

        // le a linha do arquivo csv e salva os valores em um registro
        lerLinha(linha, dados);

        set_removido(registro, '0');
        set_tamanhoRegistro(registro, (33 + strlen(dados->nome_jogador) + strlen(dados->nacionalidade) + strlen(dados->nomeClube)));
        set_prox(registro, -1);
        set_id(registro, dados->id);
        set_idade(registro, dados->idade);
        set_tamNomeJogador(registro, strlen(dados->nome_jogador));
        set_nomeJogador(registro, dados->nome_jogador);
        set_tamNacionalidade(registro, strlen(dados->nacionalidade));
        set_nacionalidade(registro, dados->nacionalidade);
        set_tamNomeClube(registro, strlen(dados->nomeClube));
        set_nomeClube(registro, dados->nomeClube);

        // escreve o registro no arquivo binário
        escreveRegistro(registro, arquivoBin);

        free(dados->nome_jogador);
        free(dados->nacionalidade);
        free(dados->nomeClube);

        // atualiza os valores do cabeçalho de acordo com o registro e escreve no binario
        setCabecalho(cabecalho, registro, arquivoBin);
        escreveCabecalho(cabecalho, arquivoBin);

        i++;
    }

    free(registro);

    fclose(arquivoCsv); // fecha o arquivo csv

    setStatus(cabecalho, '1');

    writeStatusCabecalho(cabecalho, arquivoBin);

    free(cabecalho);

    fclose(arquivoBin); // fecha o arquivo binário

    //return lista; // retorna a lista com os valores dos registros lidos do arquivo csv
}