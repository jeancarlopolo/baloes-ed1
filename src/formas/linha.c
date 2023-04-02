#include "linha.h"

struct linha
{
    enum TipoForma tipo;
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char *corBorda;
    double rotacao;
};

Linha criaLinha(int id, double x1, double y1, double x2, double y2, char *cor)
{
    struct linha *l = (struct linha *)malloc(sizeof(struct linha));
    l->tipo = LINHA;
    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->corBorda = cor;
    return l;
}

int getLinhaId(Linha l)
{
    return ((struct linha *)l)->id;
}

double getLinhaX1(Linha l)
{
    return ((struct linha *)l)->x1;
}

double getLinhaY1(Linha l)
{
    return ((struct linha *)l)->y1;
}

double getLinhaX2(Linha l)
{
    return ((struct linha *)l)->x2;
}

double getLinhaY2(Linha l)
{
    return ((struct linha *)l)->y2;
}

char *getLinhaCor(Linha l)
{
    return ((struct linha *)l)->corBorda;
}

double getLinhaRotacao(Linha l)
{
    return ((struct linha *)l)->rotacao;
}

void setLinhaId(Linha l, int id)
{
    ((struct linha *)l)->id = id;
}

void setLinhaX1(Linha l, double x1)
{
    ((struct linha *)l)->x1 = x1;
}

void setLinhaY1(Linha l, double y1)
{
    ((struct linha *)l)->y1 = y1;
}

void setLinhaX2(Linha l, double x2)
{
    ((struct linha *)l)->x2 = x2;
}

void setLinhaY2(Linha l, double y2)
{
    ((struct linha *)l)->y2 = y2;
}

void setLinhaCor(Linha l, char *cor)
{
    ((struct linha *)l)->corBorda = cor;
}

void setLinhaRotacao(Linha l, double rotacao)
{
    ((struct linha *)l)->rotacao = rotacao;
}

void liberaLinha(Linha l)
{
    struct linha *li = (struct linha *)l;
    free(li->corBorda);
    free(li);
}

double getLinhaComprimento(Linha l)
{
    struct linha *li = (struct linha *)l;
    return sqrt(pow(li->x2 - li->x1, 2) + pow(li->y2 - li->y1, 2));
}