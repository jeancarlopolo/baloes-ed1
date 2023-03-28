#include "fila.h"
#include <stdlib.h>

struct fila
{
    void **elementos;
    int tamanho;
    int quantidade;
    int inicio;
    int fim;
};

Fila criaFila(int tamanho)
{
    struct fila *fila = (struct fila *)malloc(sizeof(struct fila));
    fila->elementos = (void **)malloc(tamanho * sizeof(void *));
    fila->tamanho = tamanho;
    fila->quantidade = 0;
    fila->inicio = 0;
    fila->fim = 0;
    return fila;
}

bool insereFila(Fila fila, void *elemento)
{
    struct fila *f = (struct fila *)fila;
    if (isCheiaFila(fila))
    {
        return false;
    }
    f->elementos[f->fim] = elemento;
    f->fim = (f->fim + 1) % f->tamanho;
    f->quantidade++;
    return true;
}

bool removeFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    if (isVaziaFila(fila))
    {
        return false;
    }
    f->inicio = (f->inicio + 1) % f->tamanho;
    f->quantidade--;
    return true;
}

void *getInicioFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    if (isVaziaFila(fila))
    {
        return NULL;
    }
    return f->elementos[f->inicio];
}

void *getFimFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    if (isVaziaFila(fila))
    {
        return NULL;
    }
    return f->elementos[f->fim];
}

void *getProximoFila(Fila fila, void *elemento)
{
    struct fila *f = (struct fila *)fila;
    if (isVaziaFila(fila))
    {
        return NULL;
    }
    int i = f->inicio;
    while (i != f->fim)
    {
        if (f->elementos[i] == elemento)
        {
            return f->elementos[(i + 1) % f->tamanho];
        }
        i = (i + 1) % f->tamanho;
    }
    return NULL;
}

int getTamanhoFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    return f->tamanho;
}

int getQuantidadeFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    return f->quantidade;
}

bool isVaziaFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    return f->quantidade == 0;
}

bool isCheiaFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    return f->quantidade == f->tamanho;
}

void destroiFila(Fila fila)
{
    struct fila *f = (struct fila *)fila;
    free(f->elementos);
    free(f);
}