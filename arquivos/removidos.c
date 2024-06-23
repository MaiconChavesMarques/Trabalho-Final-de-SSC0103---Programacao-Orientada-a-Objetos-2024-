#include "removidos.h"

// lista que armazena os registros removidos
struct _removidos {
  LISTA_INDICE *lista;
  int *tamanhos;
};

// apaga a lista de removidos da memoria
void apagarListaRemovidos(REMOVIDOS *removidos) {
  apagarListaIndice(removidos->lista);
  free(removidos->tamanhos);
  free(removidos);
}

// shifta os elementos da lista para a direita (util para adicionar um novo registro no meio)
void shiftElementosListaRemovidosRight(REMOVIDOS *removidos, int pos) {
  for(int i = getTamanhoListaIndice(removidos->lista); i > pos; i--) {
    REGISTRO_INDICE *registro = getRegistroIndice(removidos->lista, i - 1);
    setRegistroListaIndice(removidos->lista, i, registro);
    removidos->tamanhos[i] = removidos->tamanhos[i - 1];
  }
}

// oq isso faz
long long int getMaiorByteOffsetMenorQue(REMOVIDOS *removidos, int id) {
    // Busca a posição do registro com o id fornecido
    int posicao = buscarPosicaoRegistroIndiceLinear(removidos->lista, id);
    if(posicao <= 0) {
      return -1;
    } else {
      REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, posicao-1);
      long long int byteOffset = getByteOffsetRegistroIndice(registroIndice);
      return byteOffset;
    }
}

// removidos->tamanhos[i] <= tamanhoAtual && getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, i)) > maiorByteOffset


// adiciona um novo registro na lista em ordem de tamanho
void adicionarRegistroRemovido(REMOVIDOS *removidos, REGISTRO_INDICE *registroIndice, int tamanho) {
    int right = getTamanhoListaIndice(removidos->lista);
    int left = 0;
    
    while (left < right) {
        int middle = (left + right) / 2;
        if (removidos->tamanhos[middle] > tamanho) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    // Move elementos à direita para abrir espaço para o novo registro
    shiftElementosListaRemovidosRight(removidos, left);

    // Adiciona o novo registro na posição encontrada
    setRegistroListaIndice(removidos->lista, left, registroIndice);
    removidos->tamanhos[left] = tamanho;

    // Atualiza o tamanho da lista
    setTamanho(removidos->lista, getTamanhoListaIndice(removidos->lista) + 1);
}

// inicializa uma lista removidos vazia
REMOVIDOS *criarListaRemovidosVazia() {
  REMOVIDOS *removidos = malloc(sizeof(REMOVIDOS));
  removidos->lista = criarListaIndice();
  removidos->tamanhos = malloc(sizeof(int) * 1000);

  return removidos;
}

// cria uma lista de registros removidos a partir de um arquivo binario
REMOVIDOS *criarListaRemovidos(FILE *file) {
  CABECALHO *cabecalho = getCabecalhoFromBin(file);
  REMOVIDOS *removidos = criarListaRemovidosVazia();

  fseek(file, 0, SEEK_END);
  int finalArquivo = ftell(file);

  int proxByteOffset = getTopo(cabecalho);
  
  int count = 0;

  // percorre todos os registros removidos
  while(proxByteOffset != -1 && proxByteOffset < finalArquivo) {
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);

    count++;

    if(get_removido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);

    liberarRegistro(registro);

    REGISTRO *proxRegistro;

    if(proxByteOffset != -1 && proxByteOffset < finalArquivo)
      proxRegistro = lerRegistroFromBin(proxByteOffset, file);

    // anotar ultimo reg removido
    if(get_prox(proxRegistro) == -1 && get_removido(proxRegistro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(proxRegistro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(proxRegistro));
      liberarRegistro(proxRegistro);
      break;
    }

    liberarRegistro(proxRegistro);
  }

  apagarCabecalho(cabecalho);

  return removidos;
}

// atualiza o campo prox de cada item da lista de registros removidos
void atualizarProxRegistrosRemovidos(int byteOffsetRegistroInserido, int proxRegistroAntigo, REMOVIDOS *removidos, FILE *file) {
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  fseek(file, 0, SEEK_END);
  int finalArquivo = ftell(file);

  int proxByteOffset = getTopo(cabecalho);
  proxByteOffset += 25; // pula o cabecalhos

  while(proxByteOffset != -1 && proxByteOffset < finalArquivo) {
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);

    if(get_removido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);
  }
}

int getTamanhoListaRemovidos(REMOVIDOS *removidos) {
  return getTamanhoListaIndice(removidos->lista);
}

// remove um item da lista a partir da posicao
void removerRegistroRemovidoPosicao(REMOVIDOS *removidos, int posicao) {
  removerRegistroIndice(removidos->lista, posicao);

  for(int i = posicao; i < getTamanhoListaIndice(removidos->lista); i++) {
    removidos->tamanhos[i] = removidos->tamanhos[i + 1];
  }
}

// remove um item da lista a partir do id
void removerRegistroRemovido(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return;
  }

  removerRegistroRemovidoPosicao(removidos, posicao);
}

// remove um item da lista a partir do byteOffset e atualiza o arquivo para ficar consistente
void removerRegistroRemovidoEAtualizarArquivo(REMOVIDOS *removidos, int posicao, FILE *file) {
  REGISTRO *registro = buscarRegistroOffset(getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, posicao)) ,file);

  if(posicao == -1) {
    return;
  }

  int tamanhoLista = getTamanhoListaIndice(removidos->lista);
  const int byteProx = 5;
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  setStatus(cabecalho, '0');

  setNroRegArq(cabecalho, getNroRegArq(cabecalho) + 1);
  writeNroRegArqCabecalho(cabecalho, file);
  setNroRem(cabecalho, getNroRem(cabecalho) - 1);
  writeNroRegRemCabecalho(cabecalho, file);
  
  if(tamanhoLista == 1) { // lista so tem um elemento removido
    setTopo(cabecalho, -1);
    writeTopoCabecalho(cabecalho, file);
  }
  else if(posicao == 0) // removendo o primeiro elemento
  {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, 1);
    long long int byteOffset = getByteOffsetRegistroIndice(registroIndice);

    setTopo(cabecalho, byteOffset);
    writeTopoCabecalho(cabecalho, file);
  }
  else if(posicao == tamanhoLista - 1) // removendo o ultimo elemento
  {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, posicao - 1);
    long long int byteOffset = getByteOffsetRegistroIndice(registroIndice);

    int prox = -1;
    
    byteOffset += byteProx;
    fseek(file, byteOffset, SEEK_SET);
    fwrite(&prox, sizeof(int), 1, file);
  }
  else
  {
    REGISTRO_INDICE *registroIndiceAnterior = getRegistroIndice(removidos->lista, posicao - 1);
    REGISTRO_INDICE *registroIndiceProximo = getRegistroIndice(removidos->lista, posicao + 1);

    long long int byteOffsetAnterior = getByteOffsetRegistroIndice(registroIndiceAnterior);
    long long int byteOffsetProximo = getByteOffsetRegistroIndice(registroIndiceProximo);

    byteOffsetAnterior += byteProx;
    fseek(file, byteOffsetAnterior, SEEK_SET);
    fwrite(&byteOffsetProximo, sizeof(int), 1, file);
  }

  liberarRegistro(registro);
  apagarCabecalho(cabecalho);

  removerRegistroRemovidoPosicao(removidos, posicao);
}

// retorna o tamanho do registro a partir do id
int getTamanhoById(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return -1;
  }

  return removidos->tamanhos[posicao];
}

// retorna o byteOffset do best fit de cada registro de um vetor
long long int *getBestFitArrayRegistros(REMOVIDOS *removidos, REGISTRO **registros, int quantidade, FILE *file)
{
  int *tamanhos = malloc(sizeof(int) * quantidade);
  long long int *byteOffsets = malloc(sizeof(long long int) * quantidade);

  // se nao tem nenhum registro removido
  if(getTamanhoListaRemovidos(removidos) == 0)
  {
    CABECALHO *cabecalho = getCabecalhoFromBin(file);

    setNroRegArq(cabecalho, getNroRegArq(cabecalho) + quantidade);
    writeNroRegArqCabecalho(cabecalho, file);

    for(int i = 0; i < quantidade; i++)
    {
      byteOffsets[i] = -1;
    }

    apagarCabecalho(cabecalho);

    free(tamanhos);

    return byteOffsets;
  }

  for(int i = 0; i < quantidade; i++) {
    if(get_tamanhoRegistro(registros[i]) == 0) {
      tamanhos[i] = -1;
      byteOffsets[i] = 0;
      continue;
    }
    tamanhos[i] = get_tamanhoRegistro(registros[i]);
  }

  // pegue o bestFit na ordem do maior para o menor
  for(int i = 0; i < quantidade; i++) {
    int maior = -1;
    int posicao = -1;

    for(int j = 0; j < quantidade; j++) {
      if(tamanhos[j] > maior) {
        maior = tamanhos[j];
        posicao = j;
      }
    }

    if(posicao == -1)
    {
      continue;
    }
    byteOffsets[posicao] = getBestFitAndFreeSpace(removidos, tamanhos[posicao], registros[posicao], file);
    tamanhos[posicao] = -1;
  }

  free(tamanhos);

  return byteOffsets;
}

// retorna o byteOffset do best fit de um registro e libera o espaco na lista de removidos
long long int getBestFitAndFreeSpace(REMOVIDOS *removidos, int tamanho, REGISTRO *registro, FILE *file) {
  int left = 0;
  int right = getTamanhoListaIndice(removidos->lista) - 1;

  int middle = (left + right) / 2;

  // busca binaria do tamanho
  while(left < right) {
    if(removidos->tamanhos[middle] == tamanho)
    {
      break;
    }
    else if(removidos->tamanhos[middle] > tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle));

  // retorna o primeiro elemento da lista com o tamanho desejado
  while(middle - 1 >= 0 && removidos->tamanhos[middle - 1] == tamanho) {
    if(removidos->tamanhos[middle] != removidos->tamanhos[middle - 1]) {
      break;
    }

    long long int byteOffsetAnterior = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle - 1));
    byteOffset = byteOffsetAnterior;

    middle--;
  }

  if(middle + 1 < getTamanhoListaIndice(removidos->lista)) { // tem um registro removido depois
    long long int proxByteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle + 1));
    set_prox(registro, proxByteOffset);
  }
  else { // nao tem registro removido depois
    set_prox(registro, -1);
  }

  removerRegistroRemovidoEAtualizarArquivo(removidos, middle, file);

  return byteOffset;
}

// imprime a lista de removidos (funcao para debugging)
void imprimirRemovidos(REMOVIDOS *removidos, FILE *file) {
  for(int i = 0; i < getTamanhoListaIndice(removidos->lista); i++) {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, i);
    printf("id: %d, byteOffset: %lld, nome: %s\n", getIndexRegistroIndice(registroIndice), getByteOffsetRegistroIndice(registroIndice), get_nomeClube(buscarRegistroOffset(getByteOffsetRegistroIndice(registroIndice), file)));
    printf("  tamanho: %d\n", removidos->tamanhos[i]);
  }
}