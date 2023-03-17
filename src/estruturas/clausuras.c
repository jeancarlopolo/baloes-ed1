#include "clausuras.h"

struct clausuraSvg
{
    FILE *svg; // arquivo svg
};

struct clausuraId
{
    int id;    // id do item a ser encontrado
    Item item; // item encontrado
};

void *criaClausuraSvg(FILE *svg)
{
    struct clausuraSvg *c = malloc(sizeof(struct clausuraSvg));
    c->svg = svg;
    return c;
}

void escreveSvg(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        svg_circle(((struct clausuraSvg *)c)->svg,
                   getCirculoX(item),
                   getCirculoY(item),
                   getCirculoR(item),
                   getCirculoCorp(item),
                   getCirculoCorb(item),
                   NULL);
        break;
    case RETANGULO:
        svg_rect(((struct clausuraSvg *)c)->svg,
                 getRetanguloX(item),
                 getRetanguloY(item),
                 getRetanguloLargura(item),
                 getRetanguloAltura(item),
                 getRetanguloCorPreenchimento(item),
                 getRetanguloCorBorda(item),
                 NULL);
        break;
    case TEXTO:
        svg_text(((struct clausuraSvg *)c)->svg,
                 getTextoX(item),
                 getTextoY(item),
                 getTextoConteudo(item),
                 getTextoCorPreenchimento(item),
                 getTextoCorBorda(item),
                 getTextoRotacao(item),
                 textoFamilia,
                 textoPeso,
                 textoTamanho,
                 NULL);
        break;
    case LINHA:
        svg_line(((struct clausuraSvg *)c)->svg,
                 getLinhaX1(item),
                 getLinhaY1(item),
                 getLinhaX2(item),
                 getLinhaY2(item),
                 getLinhaCor(item),
                 NULL);
        break;
    }
}

void *criaClausuraId(int *id)
{
    struct clausuraId *c = malloc(sizeof(struct clausuraId));
    c->id = *id;
    c->item = NULL;
    return c;
}

Item getClausuraItem(Clausura c)
{
    return ((struct clausuraId *)c)->item;
}

void acharId(Item item, Clausura c)
{
    int id = ((struct clausuraId *)c)->id;
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        if (getCirculoId(item) == id)
        {
            ((struct clausuraId *)c)->item = item;
        }
        break;
    case RETANGULO:
        if (getRetanguloId(item) == id)
        {
            ((struct clausuraId *)c)->item = item;
        }
        break;
    case TEXTO:
        if (getTextoId(item) == id)
        {
            ((struct clausuraId *)c)->item = item;
        }
        break;
    case LINHA:
        if (getLinhaId(item) == id)
        {
            ((struct clausuraId *)c)->item = item;
        }
        break;
    }
}