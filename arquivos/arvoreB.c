#include "arvoreB.h"

// altura no folha = 0, altura no = distancia do no ate a folha
int aumentarAlturaRecursivamente(FILE *arquivo, int rrnRaiz)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnRaiz);

    int nroDescendentes = 0;

    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        if(getDescendente(registro, i) != -1)
        {
            nroDescendentes++;
        }
    }

    int maxAltura = -1;

    if(nroDescendentes == 0) // eh folha
    {
        setAlturaNoRegistroArvoreB(registro, 0);
        escreverRegistroArvoreB(registro, arquivo, rrnRaiz);
        apagarRegistroArvoreB(registro);
        return 0;
    }

    for(int i = 0; i < nroDescendentes; i++)
    {
        int rrnDescendente = getDescendente(registro, i);
        int altura = aumentarAlturaRecursivamente(arquivo, rrnDescendente);
        if(altura > maxAltura)
        {
            maxAltura = altura;
        }
    }

    setAlturaNoRegistroArvoreB(registro, maxAltura + 1);
    escreverRegistroArvoreB(registro, arquivo, rrnRaiz);
    apagarRegistroArvoreB(registro);

    return maxAltura + 1;
}


bool particionarNo(FILE *arquivo, REGISTRO_ARVORE_B *registro, int rrnAtual, int chave, int nivel, int proxRrn, int *caminho, long long int byteOffset, CABECALHO_ARVORE_B *cabecalho)
{
    if(nivel != 0) // nao eh o no raiz
    {
        // pega o registro pai
        REGISTRO_ARVORE_B *registroPai = lerRegistroArvoreB(arquivo, caminho[nivel - 1]);

        int nroChavesPai = getNroChavesRegistroArvoreB(registroPai);

        if(nroChavesPai == ORDEM_ARVORE_B - 1) // pai cheio
        {
            particionarNo(arquivo, registroPai, caminho[nivel - 1], chave, nivel - 1, proxRrn, caminho, byteOffset, cabecalho);
        }

        int chaves[ORDEM_ARVORE_B]; // pega todas as chaves do registro + a chave a inserir
        long long int byteOffsets[ORDEM_ARVORE_B];

        // variaveis para detectar onde colocar a nova chave
        bool inserido = false;
        int index = 0;

        for (int i = 0; i < ORDEM_ARVORE_B; i++)
        {
            int chaveLida = getChave(registro, index);
            if(!inserido && chave < chaveLida) // colocando nova chave
            {
                inserido = true;
                chaves[i] = chave;
                byteOffsets[i] = byteOffset;
                continue;
            }
            chaves[i] = chaveLida;
            byteOffsets[i] = getByteOffsetRegistroArvoreB(registro, index);
            index++;
        }

        bool isFolha = false;

        int primeiroDescendente = getDescendente(registro, 0);

        if(primeiroDescendente == -1) // se nao ha o primeiro descendente, obrigatoriamente eh folha
        {
            isFolha = true;
        }

        REGISTRO_ARVORE_B *registroEsq = criarRegistroArvoreBVazio();
        int maiorChaveEsq = -1;
        REGISTRO_ARVORE_B *registroDir = criarRegistroArvoreBVazio();
        int menorChaveDir = -1;

        if(isFolha) // colocamos apenas as chaves nos novos registros
        {
            for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
            {
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
            }
            for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
            {
                inserirChaveRegistroArvoreB(registroDir, chaves[i], byteOffsets[i]);
            }
        }
        else // colocamos as chaves e os descendentes nos novos registros
        {
            for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
            {
                REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
                int chaveDescendente = getChave(registroDescendente, 0);
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
                inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
                apagarRegistroArvoreB(registroDescendente);
            }
            for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
            {
                REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
                int chaveDescendente = getChave(registroDescendente, 0);
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
                inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
                apagarRegistroArvoreB(registroDescendente);
            }
        }

        // escreve os registros particionados
        escreverRegistroArvoreB(registroEsq, arquivo, rrnAtual);
        escreverRegistroArvoreB(registroDir, arquivo, proxRrn);

        // chave a ser promovida
        int chaveMeio = chaves[ORDEM_ARVORE_B / 2];
        int byteOffsetMeio = byteOffsets[ORDEM_ARVORE_B / 2];

        maiorChaveEsq = getChave(registroEsq, ORDEM_ARVORE_B / 2 - 1);
        menorChaveDir = getChave(registroDir, 0);

        // escreve o pai
        inserirChaveRegistroArvoreB(registroPai, chaveMeio, byteOffsetMeio);
        inserirDescendenteRegistroArvoreB(registroPai, rrnAtual, maiorChaveEsq);
        inserirDescendenteRegistroArvoreB(registroPai, proxRrn, menorChaveDir);
        escreverRegistroArvoreB(registroPai, arquivo, caminho[nivel - 1]);

        // reescreve o cabecalho
        setProxRRNCabecalhoArvoreB(cabecalho, proxRrn + 1);
        setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
        escreverCabecalhoArvoreB(arquivo, cabecalho);

        // aumenta a altura dos nos
        aumentarAlturaRecursivamente(arquivo, caminho[nivel - 1]);

        printf("RRN Pai: %d\n", caminho[nivel - 1]);
        printf("Registro Pai: \n");
        imprimirRegistroArvoreB(registroPai);
        printf("\n");
        printf("RRN Esquerdo: %d\n", rrnAtual);
        printf("Registro Esquerdo: \n");
        imprimirRegistroArvoreB(registroEsq);
        printf("\n");
        printf("RRN Direito: %d\n", proxRrn);
        printf("Registro Direito: \n");
        imprimirRegistroArvoreB(registroDir);
        printf("\n\n");


        apagarRegistroArvoreB(registroEsq);
        apagarRegistroArvoreB(registroDir);
        apagarRegistroArvoreB(registroPai);
    }
    else // raiz
    {
        REGISTRO_ARVORE_B *novaRaiz = criarRegistroArvoreBVazio();
        int chaves[ORDEM_ARVORE_B]; // pega todas as chaves do registro + a chave a inserir
        int byteOffsets[ORDEM_ARVORE_B];

        bool inserido = false;
        int index = 0;

        for (int i = 0; i < ORDEM_ARVORE_B; i++)
        {
            int chaveLida = getChave(registro, index);
            if(!inserido && chave < chaveLida)
            {
                inserido = true;
                chaves[i] = chave;
                byteOffsets[i] = byteOffset;
                continue;
            }
            chaves[i] = chaveLida;
            byteOffsets[i] = getByteOffsetRegistroArvoreB(registro, index);
            index++;
        }

        REGISTRO_ARVORE_B *registroEsq = criarRegistroArvoreBVazio();
        int maiorChaveEsq = -1;
        REGISTRO_ARVORE_B *registroDir = criarRegistroArvoreBVazio();
        int menorChaveDir = -1;

        for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
        {
            REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
            int chaveDescendente = getChave(registroDescendente, 0);
            inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
            apagarRegistroArvoreB(registroDescendente);
            inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
        }
        for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
        {
            REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
            int chaveDescendente = getChave(registroDescendente, 0);
            inserirChaveRegistroArvoreB(registroDir, chaves[i], byteOffsets[i]);
            apagarRegistroArvoreB(registroDescendente);
            inserirDescendenteRegistroArvoreB(registroDir, getDescendente(registro, i), chaveDescendente);
        }

        // escreve os registros particionados
        escreverRegistroArvoreB(registroEsq, arquivo, rrnAtual);
        escreverRegistroArvoreB(registroDir, arquivo, proxRrn);

        // chave a ser promovida
        int chaveMeio = chaves[ORDEM_ARVORE_B / 2];
        int byteOffsetMeio = byteOffsets[ORDEM_ARVORE_B / 2];
        int rrnRaiz = proxRrn + 1;

        maiorChaveEsq = getChave(registroEsq, ORDEM_ARVORE_B / 2 - 1);
        menorChaveDir = getChave(registroDir, 0);

        // escreve a nova raiz
        inserirChaveRegistroArvoreB(novaRaiz, chaveMeio, byteOffsetMeio);
        inserirDescendenteRegistroArvoreB(novaRaiz, rrnAtual, maiorChaveEsq);
        inserirDescendenteRegistroArvoreB(novaRaiz, proxRrn, menorChaveDir);
        escreverRegistroArvoreB(novaRaiz, arquivo, rrnRaiz);

        // reescreve o cabecalho
        CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);
        setNoRaizCabecalhoArvoreB(cabecalho, rrnRaiz);
        setProxRRNCabecalhoArvoreB(cabecalho, rrnRaiz + 1);
        setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
        escreverCabecalhoArvoreB(arquivo, cabecalho);

        // aumenta a altura dos nos
        aumentarAlturaRecursivamente(arquivo, rrnRaiz);

        printf("RRN Raiz: %d\n", rrnRaiz);
        printf("Nova Raiz: \n");
        imprimirRegistroArvoreB(novaRaiz);
        printf("\n");
        printf("RRN Esquerdo: %d\n", rrnAtual);
        printf("Registro Esquerdo: \n");
        imprimirRegistroArvoreB(registroEsq);
        printf("\n");
        printf("RRN Direito: %d\n", proxRrn);
        printf("Registro Direito: \n");
        imprimirRegistroArvoreB(registroDir);
        printf("\n\n");

        apagarRegistroArvoreB(registroEsq);
        apagarRegistroArvoreB(registroDir);
        apagarRegistroArvoreB(novaRaiz);
        apagarCabecalhoArvoreB(cabecalho);
    }
}

// insere em uma Arvore B recursivamente
bool insercaoArvoreBRecursiva(FILE *arquivo, int rrnAtual, int chave, int nivel, int proxRrn, int *caminho, long long int byteOffset, CABECALHO_ARVORE_B *cabecalho)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnAtual);

    int nroChaves = getNroChavesRegistroArvoreB(registro);

    int nroDescendentes = 0;

    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        if(getDescendente(registro, i) != -1)
        {
            nroDescendentes++;
        }
    }

    if(nivel == 0 && nroChaves == 0) // arvore vazia
    {
        apagarRegistroArvoreB(registro);
        REGISTRO_ARVORE_B *registro = criarRegistroArvoreBVazio();
        setAlturaNoRegistroArvoreB(registro, 0);
        inserirChaveRegistroArvoreB(registro, chave, byteOffset);
        rrnAtual = 1;
        proxRrn = 2;
        escreverRegistroArvoreB(registro, arquivo, rrnAtual);
        setNroChavesCabecalhoArvoreB(cabecalho, 1);
        setProxRRNCabecalhoArvoreB(cabecalho, proxRrn);
        setNoRaizCabecalhoArvoreB(cabecalho, rrnAtual);
        escreverCabecalhoArvoreB(arquivo, cabecalho);
        
        printf("Arvore vazia\n");
        printf("RRN: %d\n", rrnAtual);
        imprimirRegistroArvoreB(registro);
        printf("\n");

        apagarRegistroArvoreB(registro);
        return true;
    }

    if(nroDescendentes == 0 && nroChaves < ORDEM_ARVORE_B - 1) // no folha com espaço sobrando
    {
        inserirChaveRegistroArvoreB(registro, chave, byteOffset);
        escreverRegistroArvoreB(registro, arquivo, rrnAtual);

        printf("No folha com espaco\n");
        printf("RRN: %d\n", rrnAtual);
        imprimirRegistroArvoreB(registro);
        printf("\n");

        setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
        apagarRegistroArvoreB(registro);

        return true;
    }

    caminho = realloc(caminho, sizeof(int) * (nivel + 1));
    caminho[nivel] = rrnAtual;

    if(nroDescendentes == 0 && nroChaves == ORDEM_ARVORE_B - 1) // no folha cheio
    {
        printf("No folha sem espaco\n");
        particionarNo(arquivo, registro, rrnAtual, chave, nivel, proxRrn, caminho, byteOffset, cabecalho);
        apagarRegistroArvoreB(registro);
        printf("\n");

        return true;
    }

    if(nroDescendentes != 1){ // caso geral
        printf("Caso geral\n");
        printf("RRN: %d\n", rrnAtual);
        imprimirRegistroArvoreB(registro);
        int posicao = 0;
        for(int i = 0; i < nroChaves; i++)
        {
            if(chave == getChave(registro, i)) // chave ja existe
            {
                return false;
            }
            if(chave < getChave(registro, i)) // busca a posicao da chave
            {
                posicao = i;
                break;
            }
            posicao++;
        }

        int rrnDescendente = getDescendente(registro, posicao);
        insercaoArvoreBRecursiva(arquivo, rrnDescendente, chave, nivel + 1, proxRrn, caminho, byteOffset, cabecalho);
    } 

    return true;
}

void imprimirArvoreBRecursiva(FILE *arquivo, long long int rrnAtual, int nivel)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnAtual);

    int nroChaves = getNroChavesRegistroArvoreB(registro);
    int altura = getAlturaNoRegistroArvoreB(registro);

    printf("Nivel %d: ", nivel);
    imprimirRegistroArvoreB(registro);
    printf("\n");

    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        if(getDescendente(registro, i) != -1)
        {
            imprimirArvoreBRecursiva(arquivo, getDescendente(registro, i), nivel + 1);
        }
    }

    apagarRegistroArvoreB(registro);
}

void imprimirArvoreB(FILE *arquivo)
{
    CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);

    int rrnAtual = getNoRaizCabecalhoArvoreB(cabecalho);

    imprimirArvoreBRecursiva(arquivo, rrnAtual, 0);

    apagarCabecalhoArvoreB(cabecalho);
}

void inserirArvoreB(FILE *arquivo, int chave, long long int byteOffset)
{
    CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);

    printf("Inserindo %d: \n", chave);
    printf("Cabecalho: \n");
    imprimirCabecalhoArvoreB(cabecalho);

    int *caminho = malloc(sizeof(int));
    long long int rrnAtual = getNoRaizCabecalhoArvoreB(cabecalho);
    long long int proxRrn = getProxRRNCabecalhoArvoreB(cabecalho);

    insercaoArvoreBRecursiva(arquivo, rrnAtual, chave, 0, proxRrn, caminho, byteOffset, cabecalho);

    apagarCabecalhoArvoreB(cabecalho);
    free(caminho);
}