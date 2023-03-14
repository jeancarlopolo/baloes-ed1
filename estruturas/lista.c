#include "lista.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

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
        elem->proximo->anterior = elem->anterior;
    }

    free(elem);
}

Item getLst(Lista L, Posic p)
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

Posic insertAfterLst(Lista L, Posic p, Item info)
{
    struct lista *lst = (struct lista *)L;
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

Posic getNextLst(Lista L, Posic p)
{
    struct elemento *elem = (struct elemento *)p;
    return elem->proximo;
}

Posic getLastLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = lst->inicio;

    for (; elem->proximo != NULL; elem = elem->proximo)
    {
    }

    return elem;
}

Posic getPreviousLst(Lista L, Posic p)
{
    struct elemento *elem = (struct elemento *)p;
    return elem->anterior;
}

void liberaForma(Item info)
{
    enum TipoForma tipo = getTipoForma(info);
    switch (tipo)
    {
    case CIRCULO:
        liberaCirculo(info);
        break;
    case RETANGULO:
        liberaRetangulo(info);
        break;
    case TEXTO:
        liberaTexto(info);
        break;
    case LINHA:
        liberaLinha(info);
        break;
    default:
        break;
    }
}

void killLst(Lista L)
{
    struct lista *lst = (struct lista *)L;
    struct elemento *elem = lst->inicio;

    for (elem = lst->inicio; elem != NULL; elem = lst->inicio)
    {
        liberaForma(elem->item);
        lst->inicio = elem->proximo;
        free(elem);
    }

    free(lst);
}
