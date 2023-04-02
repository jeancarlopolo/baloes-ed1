#include "retangulo.h"

struct retangulo
{
    enum TipoForma tipo;
    int id;
    double x;
    double y;
    double w;
    double h;
    char *corBorda;
    char *corPreenchimento;
    double rotacao;
};

Retangulo criaRetangulo(int id, double x, double y, double largura, double altura, char *corBorda, char *corPreenchimento)
{
    struct retangulo *r = (struct retangulo *)malloc(sizeof(struct retangulo));
    r->tipo = RETANGULO;
    r->id = id;
    r->x = x;
    r->y = y;
    r->w = largura;
    r->h = altura;
    r->corBorda = corBorda;
    r->corPreenchimento = corPreenchimento;
    return r;
}

int getRetanguloId(Retangulo r)
{
    return ((struct retangulo *)r)->id;
}

double getRetanguloLargura(Retangulo r)
{
    return ((struct retangulo *)r)->w;
}

double getRetanguloAltura(Retangulo r)
{
    return ((struct retangulo *)r)->h;
}

char *getRetanguloCorBorda(Retangulo r)
{
    return ((struct retangulo *)r)->corBorda;
}

char *getRetanguloCorPreenchimento(Retangulo r)
{
    return ((struct retangulo *)r)->corPreenchimento;
}

double getRetanguloX(Retangulo r)
{
    return ((struct retangulo *)r)->x;
}

double getRetanguloY(Retangulo r)
{
    return ((struct retangulo *)r)->y;
}

double getRetanguloRotacao(Retangulo r)
{
    return ((struct retangulo *)r)->rotacao;
}

void setRetanguloId(Retangulo r, int id)
{
    ((struct retangulo *)r)->id = id;
}

void setRetanguloLargura(Retangulo r, double largura)
{
    ((struct retangulo *)r)->w = largura;
}

void setRetanguloAltura(Retangulo r, double altura)
{
    ((struct retangulo *)r)->h = altura;
}

void setRetanguloCorBorda(Retangulo r, char *corBorda)
{
    ((struct retangulo *)r)->corBorda = corBorda;
}

void setRetanguloCorPreenchimento(Retangulo r, char *corPreenchimento)
{
    ((struct retangulo *)r)->corPreenchimento = corPreenchimento;
}

void setRetanguloX(Retangulo r, double x)
{
    ((struct retangulo *)r)->x = x;
}

void setRetanguloY(Retangulo r, double y)
{
    ((struct retangulo *)r)->y = y;
}

void setRetanguloRotacao(Retangulo r, double rotacao)
{
    ((struct retangulo *)r)->rotacao = rotacao;
}

void liberaRetangulo(Retangulo r)
{
    struct retangulo *retangulo = (struct retangulo *)r;
    free(retangulo->corBorda);
    free(retangulo->corPreenchimento);
    free(retangulo);
}

double getRetanguloArea(Retangulo r)
{
    return ((struct retangulo *)r)->w * ((struct retangulo *)r)->h;
}