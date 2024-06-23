#include "indice.h"

struct _lista
{
    int tamanho;
    int max_tamanho;
    REGISTRO_INDICE **registros; // a lista possui um vetor de endereços de registros
};

int getTamanhoLista(LISTA_INDICE *lista) {
    return lista->tamanho;
}

int getTamanhoMaxLista(LISTA_INDICE *lista) {
    return lista->max_tamanho;
}

long long int obterMaiorByteOffset(LISTA_INDICE *lista) {
    if (lista == NULL || lista->tamanho == 0) {
        return -1; // Retorna um valor inválido para indicar que não foi possível obter o maior byte offset
    }

    long long int maiorByteOffset = getByteOffsetRegistroIndice(lista->registros[0]);

    for (int i = 1; i < lista->tamanho; i++) {
        long long int byteOffsetAtual = getByteOffsetRegistroIndice(lista->registros[i]);
        if (byteOffsetAtual > maiorByteOffset) {
            maiorByteOffset = byteOffsetAtual;
        }
    }

    return maiorByteOffset;
}

LISTA_INDICE *criarListaIndice()
{
    LISTA_INDICE *lista = (LISTA_INDICE *)malloc(sizeof(LISTA_INDICE));
    lista->tamanho = 0;
    lista->max_tamanho = 1000;
    lista->registros = (REGISTRO_INDICE **)malloc(sizeof(REGISTRO_INDICE *) * lista->max_tamanho); // aloca espaço para 1000 endereços de registros

    return lista;
}

REGISTRO_INDICE *getRegistroIndice(LISTA_INDICE *lista, int index)
{
    return lista->registros[index]; // retorna o registro de determinado index da lista
}

int getTamanhoListaIndice(LISTA_INDICE *lista)
{
    return lista->tamanho;
}

bool adicionarRegistroIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro)
{
    if(lista->tamanho >= lista->max_tamanho) {
        lista->max_tamanho += 1000;
        lista->registros = (REGISTRO_INDICE **)realloc(lista->registros, sizeof(REGISTRO_INDICE *) * lista->max_tamanho);
        if(!lista->registros) {
            printf("Erro ao realocar memória.\n");
            return false;
        }
    }
    lista->registros[lista->tamanho] = registro; // adiciona o registro no final da lista
    (lista->tamanho)++;                          // atualiza o tamanho da lista
    return true;
}

bool adicionarRegistroOrdenadoIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro, FILE *file)
{
    if (lista->tamanho >= lista->max_tamanho) {
        lista->max_tamanho += 1000;
        lista->registros = (REGISTRO_INDICE **)realloc(lista->registros, sizeof(REGISTRO_INDICE *) * lista->max_tamanho);
        if (!lista->registros) {
            printf("Erro ao realocar memória.\n");
            return false;
        }
    }

    // Encontrar a posição correta para inserir o novo registro
    int pos = 0;
    while (pos < lista->tamanho && get_tamanhoRegistro(buscarRegistroOffset(getByteOffsetRegistroIndice(lista->registros[pos]), file)) < get_tamanhoRegistro(buscarRegistroOffset(getByteOffsetRegistroIndice(registro), file))) {
        pos++;
    }

    // Deslocar os elementos para a direita para abrir espaço para o novo registro
    for (int i = lista->tamanho; i > pos; i--) {
        lista->registros[i] = lista->registros[i - 1];
    }

    // Inserir o novo registro na posição correta
    lista->registros[pos] = registro;
    (lista->tamanho)++;

    return true;
}

bool modificarRegistroIndice(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro)
{
    lista->registros[index] = novoRegistro; // o registro de determinado index recebe o valor do novo registro
    return true;
}

// busca binaria em relação ao id
REGISTRO_INDICE *buscarRegistroIndice(LISTA_INDICE *lista, int id)
{
    REGISTRO_INDICE *registro = NULL;

    int inicio = 0;
    int fim = lista->tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (getIndexRegistroIndice(lista->registros[meio]) == id)
        {
            registro = lista->registros[meio];
            break;
        }
        else if (getIndexRegistroIndice(lista->registros[meio]) < id)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return registro; // se o registro não foi encontrado, retorna -1
}

int buscarPosicaoRegistroIndice(LISTA_INDICE *lista, int id) {
    // Verifica se a lista está vazia
    if (lista->tamanho == 0) {
        return -1;
    }


    int inicio = 0;
    int fim = lista->tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        
        int idMeio = getIndexRegistroIndice(getRegistroIndice(lista, meio));
        
        // Compara o id do meio com o id procurado
        if (idMeio == id) {
            return meio; // id encontrado
        } else if (idMeio < id) {
            inicio = meio + 1; // Busca na metade superior
        } else {
            fim = meio - 1; // Busca na metade inferior
        }
    }

    return -1; // Se o registro não foi encontrado, retorna -1
}

int buscarPosicaoRegistroIndiceLinear(LISTA_INDICE *lista, int id) {
    // Verifica se a lista está vazia
    if (lista->tamanho == 0) {
        return -1;
    }

    // Percorre a lista de forma linear para encontrar o id
    for (int i = 0; i < lista->tamanho; i++) {
        int idAtual = getIndexRegistroIndice(getRegistroIndice(lista, i));
        if (idAtual == id) {
            return i; // id encontrado
        }
    }

    return -1; // Se o registro não foi encontrado, retorna -1
}

long long int buscarPosicaoArquivoIndice(int id, FILE *file)
{
    fseek(file, 1, SEEK_SET); // pula o status

    int index = -1;
    long long int byteOffset = -1;

    while (fread(&index, sizeof(int), 1, file) == 1)
    {
        fread(&byteOffset, sizeof(long long int), 1, file);

        if (index >= id)
        {
            return ftell(file) - sizeof(long long int) - sizeof(int);
        }
    }

    return ftell(file);
}

void setTamanho(LISTA_INDICE *lista, int tamanho)
{
    lista->tamanho = tamanho;
}

void setRegistroListaIndice(LISTA_INDICE *lista, int index, REGISTRO_INDICE *registro)
{
    lista->registros[index] = registro;
}

// Função para remover um registro da lista
void removerRegistroIndice(LISTA_INDICE *lista, int index)
{
    apagarRegistroIndice(lista->registros[index]); // apaga o registro

    // desloca todos os registros depois do registro a ser removido para a esquerda
    for (int i = index; i < lista->tamanho - 1; i++)
    {
        lista->registros[i] = lista->registros[i + 1];
    }

    lista->tamanho--;
}

// Função que libera a memória da lista e de seus registros
bool apagarListaIndice(LISTA_INDICE *lista)
{
    if (lista == NULL)
        return false;

    for (int i = 0; i < lista->tamanho; i++)
    {
        apagarRegistroIndice(lista->registros[i]);
    }
    free(lista->registros);

    free(lista);
}

// Função que imprime os campos de todos os registros da lista
void imprimirListaIndice(LISTA_INDICE *lista)
{
    int impressoes = 0;
    for (int i = 0; i < lista->tamanho; i++)
    {
        impressoes++;

        // recebe o valor dos atributos do registro
        int id = getIndexRegistroIndice(lista->registros[i]);
        int byteOffset = getByteOffsetRegistroIndice(lista->registros[i]);

        printf("Index: %d\n", id);
        printf("Byte Offset: %d\n", byteOffset);
        
        printf("\n");
    }

    if (impressoes == 0)
    {
        // printf("Registro inexistente.\n\n");
    }
}

bool carregarIndice(LISTA_INDICE *lista, FILE *file)
{
    fseek(file, 1, SEEK_SET); // pula o status

    int index = -1;
    long long int byteOffset = -1;

    while (fread(&index, sizeof(int), 1, file) == 1)
    {
        fread(&byteOffset, sizeof(long long int), 1, file);
        REGISTRO_INDICE *registro = criarRegistroIndice();
        setIndexRegistroIndice(registro, index);
        setByteOffsetRegistroIndice(registro, byteOffset);
        adicionarRegistroIndice(lista, registro);
    }

    return true;
}