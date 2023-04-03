#include "check.h"
#include "../formas/tipos.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

struct clausuraRetangulo
{
    double x;
    double y;
    double largura;
    double altura;
};

struct clausuraCirculo
{
    double x;
    double y;
    double r;
};

ClausuraRetangulo criaClausuraRetangulo(double x, double y, double w, double h)
{
    struct clausuraRetangulo *c = malloc(sizeof(struct clausuraRetangulo));
    c->x = x;
    c->y = y;
    c->largura = w;
    c->altura = h;
    return c;
}

void liberaClausuraRetangulo(ClausuraRetangulo c)
{
    free(c);
}

ClausuraCirculo criaClausuraCirculo(double x, double y, double r)
{
    struct clausuraCirculo *c = malloc(sizeof(struct clausuraCirculo));
    c->x = x;
    c->y = y;
    c->r = r;
    return c;
}

void liberaClausuraCirculo(ClausuraCirculo c)
{
    free(c);
}

// Item é um texto e clausura é um círculo
bool checkPontoCirculoItem(Item item, Clausura c)
{
    struct clausuraCirculo *circulo = (struct clausuraCirculo *)c;
    return checkPontoCirculo(getTextoX(item),
                             getTextoY(item),
                             circulo->r,
                             circulo->x,
                             circulo->y);
}

// Item é um texto e clausura é um retângulo
bool checkPontoRetanguloItem(Item item, Clausura c)
{
    struct clausuraRetangulo *retangulo = (struct clausuraRetangulo *)c;
    return checkPontoRetangulo(getTextoX(item),
                               getTextoY(item),
                               retangulo->largura,
                               retangulo->altura,
                               retangulo->x,
                               retangulo->y);
}

// Item é um retângulo e clausura é um círculo
bool checkRetanguloCirculoItem(Item item, Clausura c)
{
    struct clausuraCirculo *circulo = (struct clausuraCirculo *)c;
    return checkRetanguloCirculo(getRetanguloX(item),
                                 getRetanguloY(item),
                                 getRetanguloLargura(item),
                                 getRetanguloAltura(item),
                                 circulo->x,
                                 circulo->y,
                                 circulo->r);
}

// Item é um círculo e clausura é um retângulo
bool checkCirculoRetanguloItem(Item item, Clausura c)
{
    struct clausuraRetangulo *retangulo = (struct clausuraRetangulo *)c;
    return checkCirculoRetangulo(getCirculoX(item),
                                 getCirculoY(item),
                                 getCirculoR(item),
                                 retangulo->x,
                                 retangulo->y,
                                 retangulo->largura,
                                 retangulo->altura);
}

// Item é um círculo e clausura é um círculo
bool checkCirculoCirculoItem(Item item, Clausura c)
{
    struct clausuraCirculo *circulo = (struct clausuraCirculo *)c;
    return checkCirculoCirculo(getCirculoX(item),
                               getCirculoY(item),
                               getCirculoR(item),
                               circulo->x,
                               circulo->y,
                               circulo->r);
}

// Item é um retângulo e clausura é um retângulo
bool checkRetanguloRetanguloItem(Item item, Clausura c)
{
    struct clausuraRetangulo *retangulo = (struct clausuraRetangulo *)c;
    return checkRetanguloRetangulo(getRetanguloX(item),
                                   getRetanguloY(item),
                                   getRetanguloLargura(item),
                                   getRetanguloAltura(item),
                                   retangulo->x,
                                   retangulo->y,
                                   retangulo->largura,
                                   retangulo->altura);
}

// Item é uma linha e clausura é um círculo
bool checkLinhaCirculoItem(Item item, Clausura c)
{
    struct clausuraCirculo *circulo = (struct clausuraCirculo *)c;
    return checkLinhaCirculo(getLinhaX1(item),
                             getLinhaY1(item),
                             getLinhaX2(item),
                             getLinhaY2(item),
                             circulo->x,
                             circulo->y,
                             circulo->r);
}

// Item é uma linha e clausura é um retângulo
bool checkLinhaRetanguloItem(Item item, Clausura c)
{
    struct clausuraRetangulo *retangulo = (struct clausuraRetangulo *)c;
    return checkLinhaRetangulo(getLinhaX1(item),
                               getLinhaY1(item),
                               getLinhaX2(item),
                               getLinhaY2(item),
                               retangulo->x,
                               retangulo->y,
                               retangulo->largura,
                               retangulo->altura);
}

bool checkInRect(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        return checkCirculoRetanguloItem(item, c);
    case RETANGULO:
        return checkRetanguloRetanguloItem(item, c);
    case TEXTO:
        return checkPontoRetanguloItem(item, c);
    case LINHA:
        return checkLinhaRetanguloItem(item, c);
    default:
        return false;
    }
}

bool checkInCircle(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        return checkCirculoCirculoItem(item, c);
    case RETANGULO:
        return checkRetanguloCirculoItem(item, c);
    case TEXTO:
        return checkPontoCirculoItem(item, c);
    case LINHA:
        return checkLinhaCirculoItem(item, c);
    default:
        return false;
    }
}