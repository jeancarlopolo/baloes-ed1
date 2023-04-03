#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct elemento
{
    Item item;
    struct elemento *proximo;
    struct elemento *anterior;
};

struct lista
{
    struct elemento *inicio;
    int capacidade;
};

struct iterador
{
    struct elemento *atual;
    bool reverso;
};

Lista createLst(int capacidade)
{
    struct lista *lst = (struct lista *)malloc(sizeof(struct lista));
    lst->inicio = NIL;
    if (capacidade < 0)
    {
        lst->capacidade = CAPAC_ILIMITADA;
    }
    else
    {
        lst->capacidade = capacidade;
    }
    return lst;
}

int lengthLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = lst->inicio;

    int i = 0;
    for (; elem != NULL; elem = elem->proximo)
        i++;

    return i;
}

int maxLengthLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    return lst->capacidade;
}

bool isEmptyLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    return lst->inicio == NULL;
}

bool isFullLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    return lengthLst(lst) == lst->capacidade;
}

Posic insertLst(Lista L, Item info)
{
    if (isFullLst(L))
        return NULL;

    struct lista *lst = (struct lista *)L;
    struct elemento *elem = (struct elemento *)malloc(sizeof(struct elemento));

    if (lst->inicio == NULL)
    {
        lst->inicio = elem;
        elem->item = info;
        elem->proximo = NIL;
        elem->anterior = NIL;
        return elem;
    }

    struct elemento *aux = lst->inicio;
    for (; aux->proximo != NULL; aux = aux->proximo)
    {
    }
    aux->proximo = elem;

    elem->item = info;
    elem->proximo = NIL;
    elem->anterior = aux;

    return elem;
}

Item popLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = lst->inicio;

    if (elem == NULL)
        return NULL;

    lst->inicio = elem->proximo;
    elem->proximo->anterior = NULL;

    Item info = elem->item;
    free(elem);

    return info;
}

void removeLst(Lista L, Posic p)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = (struct elemento *)p;

    if (elem == lst->inicio)
    {
        lst->inicio = elem->proximo;
        elem->proximo->anterior = NULL;
    }
    else
    {
        elem->anterior->proximo = elem->proximo;
        if (elem->proximo != NULL)
            elem->proximo->anterior = elem->anterior;
    }
}

Item getLst(Posic p)
{
    struct elemento *elem = (struct elemento *)p;
    return elem->item;
}

Posic insertBefore(Lista L, Posic p, Item info)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = (struct elemento *)p;
    struct elemento *novoElem = (struct elemento *)malloc(sizeof(struct elemento));

    novoElem->item = info;
    novoElem->proximo = elem;
    novoElem->anterior = elem->anterior;

    if (elem->anterior == NULL)
    {
        lst->inicio = novoElem;
    }
    else
    {
        elem->anterior->proximo = novoElem;
    }
    elem->anterior = novoElem;

    return novoElem;
}

Posic insertAfterLst(Posic p, Item info)
{
    struct elemento *elem = (struct elemento *)p;
    struct elemento *novoElem = (struct elemento *)malloc(sizeof(struct elemento));

    novoElem->item = info;
    novoElem->proximo = elem->proximo;
    novoElem->anterior = elem;

    if (elem->proximo != NULL)
        elem->proximo->anterior = novoElem;
    elem->proximo = novoElem;

    return novoElem;
}

Posic getFirstLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    return lst->inicio;
}

Posic getNextLst(Posic p)
{
    struct elemento *elem = (struct elemento *)p;
    return elem->proximo;
}

Posic getLastLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    if (lst->inicio == NULL)
        return NULL;
    struct elemento *elem = lst->inicio;

    for (; elem->proximo != NULL; elem = elem->proximo)
    {
    }

    return elem;
}

Posic getPreviousLst(Posic p)
{
    struct elemento *elem = (struct elemento *)p;
    return elem->anterior;
}

void killLst(Lista L)
{
    if (L == NULL)
        return;

    struct lista *lst = (struct lista *)L;
    struct elemento *elem = lst->inicio;

    while (elem != NULL)
    {
        struct elemento *aux = elem;
        elem = elem->proximo;
        free(aux);
    }

    free(lst);
}

Iterador createIterador(Lista L, bool reverso)
{
    struct lista *lst = (struct lista *)L;
    struct iterador *iter = (struct iterador *)malloc(sizeof(struct iterador));

    if (reverso)
    {
        iter->atual = getLastLst(lst);
    }
    else
    {
        iter->atual = getFirstLst(lst);
    }

    iter->reverso = reverso;

    return iter;
}

bool isIteratorEmpty(Iterador it)
{
    if (it == NULL)
        return true;
    struct iterador *iter = (struct iterador *)it;
    if (iter->atual == NULL)
        return true;
    return false;
}

Item getIteratorNext(Iterador it)
{
    struct iterador *iter = (struct iterador *)it;
    if (isIteratorEmpty(iter))
        return NULL;
    struct elemento *elem = (struct elemento *)iter->atual;

    if (iter->reverso)
    {
        iter->atual = elem->anterior;
    }
    else
    {
        iter->atual = elem->proximo;
    }

    return elem->item;
}

Posic getIteratorNextPosic(Iterador it)
{
    struct iterador *iter = (struct iterador *)it;
    if (isIteratorEmpty(iter))
        return NULL;
    struct elemento *elem = (struct elemento *)iter->atual;
    if (iter->reverso)
    {
        iter->atual = elem->anterior;
    }
    else
    {
        iter->atual = elem->proximo;
    }
    return elem;
}

void killIterator(Iterador it)
{
    free(it);
}

Lista map(Lista L, Apply f, Clausura c)
{
    Lista novaLst = createLst(-1);
    Iterador it = createIterador(L, false);

    while (!isIteratorEmpty(it))
    {
        Item info = getIteratorNext(it);
        Item novoInfo = f(info, c);
        insertLst(novaLst, novoInfo);
    }

    killIterator(it);

    return novaLst;
}

Lista filter(Lista L, Check f, Clausura c)
{
    Lista novaLst = createLst(-1);
    Iterador it = createIterador(L, false);

    while (!isIteratorEmpty(it))
    {
        Item info = getIteratorNext(it);
        if (f(info, c))
        {
            insertLst(novaLst, info);
        }
    }

    killIterator(it);

    return novaLst;
}

void fold(Lista L, ApplyClosure f, Clausura c)
{
    Iterador it = createIterador(L, false);

    while (!isIteratorEmpty(it))
    {
        Item info = getIteratorNext(it);
        f(info, c);
    }

    killIterator(it);
}

Posic insertPosicLst(Lista L, Posic p, Lista ListaP)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *final = (struct elemento *)getLastLst(lst);
    struct elemento *elemento = (struct elemento *)p;

    if (final == NULL)
    {
        lst->inicio = elemento;
    }
    else
    {
        final->proximo = elemento;
        if (elemento != NULL)
            elemento->anterior = final;
    }

    if (ListaP != NULL)
        free(ListaP);

    return elemento;
}