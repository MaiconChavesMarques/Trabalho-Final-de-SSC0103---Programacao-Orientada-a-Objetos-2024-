/*
* Pedro Henrique Ferreira Silva - NUSP: 14677526
* Rodrigo de Freitas Lima - NUSP: 12547510
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"

struct registro {
    char removido;
    int tamanhoRegistro;
    long long int prox;
    int id;
    int idade;
    int tamNomeJogador;
    char *nomeJogador;
    int tamNacionalidade;
    char *nacionalidade;
    int tamNomeClube;
    char *nomeClube;
};

// Função que imprime os registros de acordo com os parâmetros de busca
void imprimirRegistros(REGISTRO **registros)
{
    if(registros == NULL || registros[0] == NULL)
    {
        printf("Registro inexistente.\n");
        printf("\n");
        return;
    }
    for (int i = 0; registros[i] != NULL; i++) // Percorre o vetor de registros até encontrar um registro nulo
    {
        int id = get_id(registros[i]);
        int idade = get_idade(registros[i]);
        char *nomeClube = get_nomeClube(registros[i]);
        char *nacionalidade = get_nacionalidade(registros[i]);
        char *nomeJogador = get_nomeJogador(registros[i]);

        //printf("ID do Jogador: ");
        printf("id: %d\n", id);

        //printf("Idade do Jogador: ");
        if (idade == -1) // se a idade do jogador for -1, imprime "SEM DADO"
        {
            printf("idade: SEM DADO\n");
        }
        else // se não, imprime a idade do jogador
        {
            printf("idade: %d\n", idade);
        }

        //printf("Nome do Jogador: ");
        if (strcmp(nomeJogador, "SEM DADO") == 0) // se o nome do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do jogador
        {
            for (int j = 0; j < get_tamNomeJogador(registros[i]); j++)
            {
                printf("%c", nomeJogador[j]);
            }
            printf("\n");
        }

        //printf("Nacionalidade do Jogador: ");
        if (strcmp(nacionalidade, "SEM DADO") == 0) // se a nacionalidade do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere da nacionalidade
        {
            for (int j = 0; j < get_tamNacionalidade(registros[i]); j++)
            {
                printf("%c", nacionalidade[j]);
            }
            printf("\n");
        }

        //printf("Clube do Jogador: ");
        if(strcmp(nomeClube, "SEM DADO") == 0) // se o nome do clube do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do clube
        {
            for(int j = 0; j<get_tamNomeClube(registros[i]); j++)
            {
                printf("%c", nomeClube[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// Função que retorna a intersecao de dois vetores de registros, verificando se cada registro do primeiro vetor está no segundo vetor 
REGISTRO **intersecaoDoisRegistros(REGISTRO **registro1, REGISTRO **registro2)
{
    REGISTRO **intersecao = (REGISTRO **)malloc(0);
    int quantidade = 0;

    // para cada registro do primeiro vetor, verifica se existe um registro do segundo vetor que é igual a ele (possui o mesmo id)
    for (int i = 0; registro1[i] != NULL; i++)
    {
        for (int j = 0; registro2[j] != NULL; j++)
        {
            if (get_id(registro1[i]) == get_id(registro2[j])) // se forem iguais, adiciona o registro no vetor da intersecao
            {
                intersecao = (REGISTRO **)realloc(intersecao, sizeof(REGISTRO *) * (quantidade + 1));
                intersecao[quantidade] = registro1[i];
                quantidade++;
            }
        }
    }

    // adiciona mais um registro com o valor nulo no vetor intersecao para indicar o fim do vetor
    intersecao = (REGISTRO **)realloc(intersecao, sizeof(REGISTRO *) * (quantidade + 1));
    intersecao[quantidade] = NULL;
    return intersecao;
}

// Função que cria um registro com os valores iniciais
REGISTRO *criarRegistroNulo()
{
    REGISTRO *registro = (REGISTRO *)malloc(sizeof(REGISTRO));
    registro->removido = '1';
    registro->tamanhoRegistro = 0;
    registro->prox = -1;
    registro->id = -1;
    registro->idade = -1;
    registro->tamNomeJogador = -1;
    registro->nomeJogador = NULL;
    registro->tamNacionalidade = -1;
    registro->nacionalidade = NULL;
    registro->tamNomeClube = -1;
    registro->nomeClube = NULL;
    return registro;
}

// Função que cria um registro com os valores passados por parâmetro na função
REGISTRO *criarRegistro(char removido, int tamanhoRegistro, long prox, int id, int idade, int tamNomeJogador, char *nomeJogador, int tamNacionalidade, char *nacionalidade, int tamNomeClube, char *nomeClube)
{
    REGISTRO *registro = (REGISTRO *)malloc(sizeof(REGISTRO));
    registro->removido = removido;
    registro->tamanhoRegistro = tamanhoRegistro;
    registro->prox = prox;
    registro->id = id;
    registro->idade = idade;
    registro->tamNomeJogador = tamNomeJogador;
    registro->nomeJogador = nomeJogador;
    registro->tamNacionalidade = tamNacionalidade;
    registro->nacionalidade = nacionalidade;
    registro->tamNomeClube = tamNomeClube;
    registro->nomeClube = nomeClube;
    return registro;
}

// Funções get para que seja possível acessar os atributos dos registros em outras partes do código

char get_removido(REGISTRO *registro)
{
    return registro->removido;
}

REGISTRO *buscarRegistroOffset(long long offset, FILE *file) {
    REGISTRO *registro = lerRegistroFromBin(offset, file); // lê o registro do arquivo binário
    return registro;
}

int get_tamanhoRegistro(REGISTRO *registro)
{
    return registro->tamanhoRegistro;
}

long long int get_prox(REGISTRO *registro)
{
    return registro->prox;
}

int get_id(REGISTRO *registro)
{
    return registro->id;
}

int get_idade(REGISTRO *registro)
{
    return registro->idade;
}

int get_tamNomeJogador(REGISTRO *registro)
{
    return registro->tamNomeJogador;
}

char *get_nomeJogador(REGISTRO *registro)
{
    if (strcmp(registro->nomeJogador, "") == 0) // se a string do nome do jogador estiver vazia, retorna "SEM DADO"
    {
        return "SEM DADO";
    }
    return registro->nomeJogador;
}

int get_tamNacionalidade(REGISTRO *registro)
{
    return registro->tamNacionalidade;
}

char *get_nacionalidade(REGISTRO *registro)
{
    if (strcmp(registro->nacionalidade, "") == 0) // se a string da nacionalidade estiver vazia, retorna "SEM DADO"
    {
        return "SEM DADO";
    }
    return registro->nacionalidade;
}

int get_tamNomeClube(REGISTRO *registro)
{
    return registro->tamNomeClube;
}

char *get_nomeClube(REGISTRO *registro)
{
    if (strcmp(registro->nomeClube, "") == 0) // se a string do nome do clube estiver vazia, retorna "SEM DADO"
    {
        return "SEM DADO";
    }
    return registro->nomeClube;
}

// Funções set para que seja possível alterar o valor de um atributo de um registro em outras partes do código

void set_removido(REGISTRO *registro, int removido)
{
    registro->removido = removido;
}

void set_tamanhoRegistro(REGISTRO *registro, int tamanhoRegistro)
{
    registro->tamanhoRegistro = tamanhoRegistro;
}

void set_prox(REGISTRO *registro, long long int prox)
{
    registro->prox = prox;
}

void set_id(REGISTRO *registro, int id)
{
    registro->id = id;
}

void set_idade(REGISTRO *registro, int idade)
{
    if(idade == 0) // se idade for igual a 0, muda o valor do atributo idade do registro para -1 para indicar que é uma idade inválida
    {
        registro->idade = -1;
        return;
    }
    registro->idade = idade;
}

void set_tamNomeJogador(REGISTRO *registro, int tamNomeJogador)
{
    registro->tamNomeJogador = tamNomeJogador;
}

void set_nomeJogador(REGISTRO *registro, char *nomeJogador)
{
    registro->nomeJogador = nomeJogador;
}

void set_tamNacionalidade(REGISTRO *registro, int tamNacionalidade)
{
    registro->tamNacionalidade = tamNacionalidade;
}

void set_nacionalidade(REGISTRO *registro, char *nacionalidade)
{
    registro->nacionalidade = nacionalidade;
}

void set_tamNomeClube(REGISTRO *registro, int tamNomeClube)
{
    registro->tamNomeClube = tamNomeClube;
}

void set_nomeClube(REGISTRO *registro, char *nomeClube)
{
    registro->nomeClube = nomeClube;
}

// Função que libera o espaço de memória do registro e de seus atributos
void liberarRegistro(REGISTRO *registro)
{
    free(registro->nomeJogador);
    free(registro->nacionalidade);
    free(registro->nomeClube);
    free(registro);
}

REGISTRO *lerRegistroFromBin(int posicao, FILE *arquivoBin)
{
    fseek(arquivoBin, posicao, SEEK_SET);

    REGISTRO *registro = criarRegistroNulo();

    char removido;
    fread(&removido, sizeof(char), 1, arquivoBin); // lê o caractere "removido" de um registro do arquivo e salva na variável removido
    set_removido(registro, removido);

    int tamanhoRegistro;
    fread(&tamanhoRegistro, sizeof(int), 1, arquivoBin); // lê o tamanho de um registro do arquivo e salva na variável tamanhoRegistro
    set_tamanhoRegistro(registro, tamanhoRegistro);

    long long int prox;
    fread(&prox, sizeof(long long int), 1, arquivoBin); // lê a posição do próximo registro removido do arquivo e salva na variável prox
    set_prox(registro, prox);

    int id;
    fread(&id, sizeof(int), 1, arquivoBin); // lê o id de um registro do arquivo e salva na variável id
    set_id(registro, id);

    int idade;
    fread(&idade, sizeof(int), 1, arquivoBin); // lê a idade do jogador de um registro do arquivo e salva na variável idade
    set_idade(registro, idade);

    int tamNomeJogador;
    fread(&tamNomeJogador, sizeof(int), 1, arquivoBin); // lê o tamanho do nome do jogador de um registro do arquivo e salva na variável tamNomeJogador
    set_tamNomeJogador(registro, tamNomeJogador);

    char *nomeJogador = (char *)malloc(tamNomeJogador);
    // lê cada caractere do nome do jogador de um registro no arquivo e salva na variavel nomeJogador
    for(int i = 0; i < tamNomeJogador; i++)
    {
        fread(&nomeJogador[i], sizeof(char), 1, arquivoBin);
    }
    set_nomeJogador(registro, nomeJogador);

    int tamNacionalidade;
    fread(&tamNacionalidade, sizeof(int), 1, arquivoBin); // lê o tamanho da string nacionalidade de um registro do arquivo e salva na variável tamNacionalidade
    set_tamNacionalidade(registro, tamNacionalidade);

    char *nacionalidade = (char *)malloc(tamNacionalidade);
    // lê cada caractere da string nacionalidade um registro no arquivo e salva na variavel nacionalidade
    for(int i = 0; i < tamNacionalidade; i++)
    {
        fread(&nacionalidade[i], sizeof(char), 1, arquivoBin);
    }
    set_nacionalidade(registro, nacionalidade);

    int tamNomeClube;
    fread(&tamNomeClube, sizeof(int), 1, arquivoBin); // lê o tamanho do nome do clube de um registro do arquivo e salva na variável tamNomeClube
    set_tamNomeClube(registro, tamNomeClube);

    char *nomeClube = (char *)malloc(tamNomeClube);
    // lê cada caractere do nome do clube um registro no arquivo e salva na variavel nomeClube
    for(int i = 0; i < tamNomeClube; i++)
    {
        fread(&nomeClube[i], sizeof(char), 1, arquivoBin);
    }
    set_nomeClube(registro, nomeClube);

    return registro;
}