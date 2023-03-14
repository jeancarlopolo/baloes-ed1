#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct no
{
    void *elemento;
};

struct fila_circular
{
    struct no *elementos; /* vetor de elementos da fila */
    int tamanho;          /* tamanho máximo da fila */
    int inicio;           /* índice do elemento no início da fila */
    int fim;              /* índice do elemento no final da fila */
    int quantidade;       /* número de elementos na fila */
};

Fila criaFila(int tamanho)
{
    struct fila_circular *fila = (struct fila_circular *)malloc(sizeof(struct fila_circular));

    fila->elementos = (struct no *)malloc(tamanho * sizeof(struct no));

    fila->tamanho = tamanho;
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;

    return fila;
}

bool insereFila(Fila fila, void *elemento)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    if (fc->quantidade == fc->tamanho)
    {
        return false;
    }

    fc->fim = (fc->fim + 1) % fc->tamanho;

    fc->elementos[fc->fim].elemento = elemento;

    fc->quantidade++;

    return true;
}

bool removeFila(Fila fila)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    if (fc->quantidade == 0)
    {
        return false;
    }

    fc->elementos[fc->inicio].elemento = NULL;

    fc->inicio = (fc->inicio + 1) % fc->tamanho;

    fc->quantidade--;

    return true;
}

void *inicioFila(Fila fila)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    if (fc->quantidade == 0)
    {
        return NULL;
    }

    return fc->elementos[fc->inicio].elemento;
}

void *finalFila(Fila fila)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    if (fc->quantidade == 0)
    {
        return NULL;
    }

    return fc->elementos[fc->fim].elemento;
}

int tamanhoFila(Fila fila)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    return fc->quantidade;
}

void destroiFila(Fila fila)
{
    struct fila_circular *fc = (struct fila_circular *)fila;

    free(fc->elementos);

    free(fc);
}