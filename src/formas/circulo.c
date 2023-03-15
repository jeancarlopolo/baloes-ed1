#include "circulo.h"

struct circulo
{
    enum TipoForma tipo;
    int id;
    double x;
    double y;
    double r;
    char *corBorda;
    char *corPreenchimento;
};

Circulo criaCirculo(int id, double x, double y, double r, char* corb, char* corp)
{
    struct circulo *c = (struct circulo *)malloc(sizeof(struct circulo));
    c->tipo = CIRCULO;
    c->id = id;
    c->x = x;
    c->y = y;
    c->r = r;
    c->corBorda = corb;
    c->corPreenchimento = corp;
    return c;
}

int getCirculoId(Circulo c)
{
    return ((struct circulo *)c)->id;
}

double getCirculoX(Circulo c)
{
    return ((struct circulo *)c)->x;
}

double getCirculoY(Circulo c)
{
    return ((struct circulo *)c)->y;
}

double getCirculoR(Circulo c)
{
    return ((struct circulo *)c)->r;
}

char* getCirculoCorb(Circulo c)
{
    return ((struct circulo *)c)->corBorda;
}

char* getCirculoCorp(Circulo c)
{
    return ((struct circulo *)c)->corPreenchimento;
}

void setCirculoId(Circulo c, int id)
{
    ((struct circulo *)c)->id = id;
}

void setCirculoX(Circulo c, double x)
{
    ((struct circulo *)c)->x = x;
}

void setCirculoY(Circulo c, double y)
{
    ((struct circulo *)c)->y = y;
}

void setCirculoR(Circulo c, double r)
{
    ((struct circulo *)c)->r = r;
}

void setCirculoCorb(Circulo c, char* corb)
{
    ((struct circulo *)c)->corBorda = corb;
}

void setCirculoCorp(Circulo c, char* corp)
{
    ((struct circulo *)c)->corPreenchimento = corp;
}

void liberaCirculo(Circulo c)
{
    struct circulo *circ = (struct circulo *)c;
    free(circ->corBorda);
    free(circ->corPreenchimento);
    free(circ);
}

double getCirculoArea(Circulo c)
{
    return PI * pow(((struct circulo *)c)->r, 2);
}