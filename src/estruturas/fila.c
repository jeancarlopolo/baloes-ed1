#include "fila.h"
#include <stdlib.h>

struct fila {
    int tamanho;
    int quantidade;
    int inicio;
    int fim;
    Item *elementos;
};

Fila criaFila(int tamanho) {
    struct fila *f = malloc(sizeof(struct fila));
    f->tamanho = tamanho;
    f->quantidade = 0;
    f->inicio = 0;
    f->fim = 0;
    f->elementos = malloc(tamanho * sizeof(Item));
    return f;
}

bool insereFila(Fila fila, Item elemento) {
    struct fila *f = (struct fila *) fila;
    if (isCheiaFila(f)) {
        return false;
    }
    f->elementos[f->fim] = elemento;
    f->fim = (f->fim + 1) % f->tamanho;
    f->quantidade++;
    return true;
}

bool removeFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    if (isVaziaFila(f)) {
        return false;
    }
    f->inicio = (f->inicio + 1) % f->tamanho;
    f->quantidade--;
    return true;
}

Item getInicioFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    if (isVaziaFila(f)) {
        return NULL;
    }
    return f->elementos[f->inicio];
}

Item getFimFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    if (isVaziaFila(f)) {
        return NULL;
    }
    return f->elementos[f->fim];
}

int getTamanhoFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    return f->tamanho;
}

int getQuantidadeFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    return f->quantidade;
}

bool isVaziaFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    return f->quantidade == 0;
}

bool isCheiaFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    return f->quantidade == f->tamanho;
}

void destroiFila(Fila fila) {
    struct fila *f = (struct fila *) fila;
    free(f->elementos);
    free(f);
}