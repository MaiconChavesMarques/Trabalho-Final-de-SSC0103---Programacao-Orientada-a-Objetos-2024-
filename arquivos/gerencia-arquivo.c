#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerencia-arquivo.h"
#include "cabecalho.h"

/*
struct dados {
    int id;
    int idade;
    char *nome_jogador;
    char *nacionalidade;
    char *nomeClube;
};

// Função que lê o arquivo csv e salva seus dados em uma lista de registros
LISTA *lerCsv(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) { // verifica se ocorreu um erro ao abrir o arquivo em modo de leitura
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char linha[1090];
    int i = 0;

    LISTA *lista = criarLista(); // cria um lista vazia

    // enquanto tiver algo na linha do arquivo csv, lê os dados da linha
    while(fgets(linha, 1090, arquivo) != NULL) {
        // pula a primeira linha
        if (i == 0) {
            i++;
            continue;
        }

        DADOS *dados = (DADOS *) malloc(sizeof(DADOS));
        REGISTRO *registro = getRegistro(lista, i - 1); // pega o endereço do registro da posição anterior da lista
        lerLinha(linha, dados); // lê a linha e armazena os dados lidos na varível dados

        // cria um registro com os valores que estão em dados
        registro = criarRegistro('0', 
                                (33 + strlen(dados->nome_jogador) + strlen(dados->nacionalidade) + strlen(dados->nomeClube)), 
                                -1,  
                                dados->id,
                                dados->idade,
                                strlen(dados->nome_jogador), 
                                dados->nome_jogador, 
                                strlen(dados->nacionalidade), 
                                dados->nacionalidade, 
                                strlen(dados->nomeClube), 
                                dados->nomeClube);
        adicionarRegistro(lista, registro); // adiciona o registro criado na lista

        free(dados); // libera a memória da variável dados

        i++;
    }

    fclose(arquivo); // fecha o arquivo csv

    return lista; // retorna a lista com os valores dos registros lidos do arquivo csv
}

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


// Função que escreve os dados do cabeçalho e dos registros no arquivo binário
void escreveBinario(CABECALHO *cabecalho, LISTA *lista, char *binario) {
  setStatus(cabecalho, '1'); // define o status como 1 antes de manipular o arquivo
  FILE *f = fopen(binario, "wb");
  if(f == NULL) { // verifica se houve erro ao abrir o arquino no modo escrita
    return;
  }

  // pega os dados do cabeçalho e salva em variáveis
  char status = getStatus(cabecalho);
  long long int topo = getTopo(cabecalho);
  long long int proxByteOffset = getProxByteOffset(cabecalho);
  int nroRegArq = getNroRegArq(cabecalho);
  int nroRegRem = getNroRem(cabecalho);

  fseek(f, 0, SEEK_SET); // move o ponteiro do arquivo para a posição inicial

  // escreve os valores do cabeçalho no arquivo
  if(
    fwrite(&status, sizeof(char), 1, f) == 1 &&
    fwrite(&topo, sizeof(long long int), 1, f) == 1 &&
    fwrite(&proxByteOffset, sizeof(long long int), 1, f) == 1 &&
    fwrite(&nroRegArq, sizeof(int), 1, f) == 1 &&
    fwrite(&nroRegRem, sizeof(int), 1, f) == 1
  ) {
    setStatus(cabecalho, '1');
  }

  // pega os valores dos registros e escreve os valores de cada registro no arquivo
  for(int i=0; i<getTamanho(lista); i++) {
    int removido = get_removido(getRegistro(lista, i));
    int tamRegistro = get_tamanhoRegistro(getRegistro(lista, i));
    long long int prox = get_prox(getRegistro(lista, i));
    int id = get_id(getRegistro(lista, i));
    int idade = get_idade(getRegistro(lista, i));
    int tamNomeJogador = get_tamNomeJogador(getRegistro(lista, i));
    char *nomeJogador = get_nomeJogador(getRegistro(lista, i));
    int tamNacionalidade = get_tamNacionalidade(getRegistro(lista, i));
    char *nacionalidade = get_nacionalidade(getRegistro(lista, i));
    int tamNomeClube = get_tamNomeClube(getRegistro(lista, i));
    char *nomeClube = get_nomeClube(getRegistro(lista, i));

    // escreve os campos do registro no arquivo
    fwrite(&removido, sizeof(char), 1, f);
    fwrite(&tamRegistro, sizeof(int), 1, f);
    fwrite(&prox, sizeof(long long int), 1, f);
    fwrite(&id, sizeof(int), 1, f);
    fwrite(&idade, sizeof(int), 1, f);

    fwrite(&tamNomeJogador, sizeof(int), 1, f);
    // escreve todos os caracteres do nome do jogador no arquivo
    for(int i=0; i<tamNomeJogador; i++) {
      fwrite(&nomeJogador[i], sizeof(char), 1, f);
    }

    fwrite(&tamNacionalidade, sizeof(int), 1, f);
    // escreve todos os caracteres da nacionalidade no arquivo
    for(int i=0; i<tamNacionalidade; i++) {
      fwrite(&nacionalidade[i], sizeof(char), 1, f);
    }

    fwrite(&tamNomeClube, sizeof(int), 1, f);
    // escreve todos os caracteres do nome do clube no arquivo
    for(int i=0; i<tamNomeClube; i++) {
      fwrite(&nomeClube[i], sizeof(char), 1, f);
    }
  }
  fclose(f); // fecha o arquivo
}
*/