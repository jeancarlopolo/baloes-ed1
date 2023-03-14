#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* Define a estrutura de um nó da fila circular estática */
struct no
{
    void *elemento;
};

/* Define a estrutura da fila circular estática */
struct fila_circular
{
    struct no *elementos; /* vetor de elementos da fila */
    int tamanho;          /* tamanho máximo da fila */
    int inicio;           /* índice do elemento no início da fila */
    int fim;              /* índice do elemento no final da fila */
    int quantidade;       /* número de elementos na fila */
};

/* Cria uma nova fila circular estática com capacidade para armazenar 'tamanho' elementos */
Fila criaFila(int tamanho)
{
    /* Aloca espaço para a fila */
    struct fila_circular *fila = (struct fila_circular *)malloc(sizeof(struct fila_circular));
    if (fila == NULL)
    {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }

    /* Aloca espaço para os elementos da fila */
    fila->elementos = (struct no *)malloc(tamanho * sizeof(struct no));
    if (fila->elementos == NULL)
    {
        printf("Erro ao alocar memória para os elementos da fila.\n");
        exit(1);
    }

    /* Inicializa os campos da fila */
    fila->tamanho = tamanho;
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;

    /* Retorna a fila criada */
    return fila;
}

/* Insere um elemento na fila circular estática
   Retorna true se a inserção foi realizada com sucesso, e false caso contrário */
bool insereFila(Fila fila, void *elemento)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Verifica se a fila está cheia */
    if (fc->quantidade == fc->tamanho)
    {
        return false;
    }

    /* Atualiza o índice do fim da fila */
    fc->fim = (fc->fim + 1) % fc->tamanho;

    /* Insere o elemento no final da fila */
    fc->elementos[fc->fim].elemento = elemento;

    /* Atualiza o número de elementos na fila */
    fc->quantidade++;

    return true;
}

/* Remove um elemento da fila circular estática
   Retorna true se a remoção foi realizada com sucesso, e false caso contrário */
bool removeFila(Fila fila)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Verifica se a fila está vazia */
    if (fc->quantidade == 0)
    {
        return false;
    }

    /* Remove o elemento do início da fila */
    fc->elementos[fc->inicio].elemento = NULL;

    /* Atualiza o índice do início da fila */
    fc->inicio = (fc->inicio + 1) % fc->tamanho;

    /* Atualiza o número de elementos na fila */
    fc->quantidade--;

    return true;
}

/* Retorna o elemento que está no início da fila circular estática */
void *inicioFila(Fila fila)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Verifica se a fila está vazia */
    if (fc->quantidade == 0)
    {
        return NULL;
    }

    /* Retorna o elemento no início da fila */
    return fc->elementos[fc->inicio].elemento;
}

/* Retorna o elemento que está no final da fila circular estática */
void *finalFila(Fila fila)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Verifica se a fila está vazia */
    if (fc->quantidade == 0)
    {
        return NULL;
    }

    /* Retorna o elemento no final da fila */
    return fc->elementos[fc->fim].elemento;
}

/* Retorna o número de elementos armazenados na fila circular estática */
int tamanhoFila(Fila fila)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Retorna o número de elementos na fila */
    return fc->quantidade;
}

/* Libera a memória alocada para a fila circular estática */
void destroiFila(Fila fila)
{
    /* Converte o ponteiro void para o tipo apropriado */
    struct fila_circular *fc = (struct fila_circular *)fila;

    /* Libera a memória alocada para os elementos da fila */
    free(fc->elementos);

    /* Libera a memória alocada para a fila */
    free(fc);
}