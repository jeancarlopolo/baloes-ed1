#include "texto.h"

struct texto
{
    enum TipoForma tipo;
    int id;
    double x;
    double y;
    char *conteudo;
    char *corBorda;
    char *corPreenchimento;
    char *ancora;
    double rotacao;
};

char *textoFamilia = "sans (sans-serif)";
char *textoPeso = "normal";
char *textoTamanho = "16px";

Texto criaTexto(int id, double x, double y, char *corBorda, char *corPreenchimento, char *ancora, char *conteudo)
{
    struct texto *t = (struct texto *)malloc(sizeof(struct texto));
    t->tipo = TEXTO;
    t->id = id;
    t->x = x;
    t->y = y;
    t->corBorda = corBorda;
    t->corPreenchimento = corPreenchimento;
    t->ancora = ancora;
    t->conteudo = conteudo;
    t->rotacao = 0;
    return t;
}

int getTextoId(Texto t)
{
    return ((struct texto *)t)->id;
}

double getTextoX(Texto t)
{
    return ((struct texto *)t)->x;
}

double getTextoY(Texto t)
{
    return ((struct texto *)t)->y;
}

char *getTextoCorBorda(Texto t)
{
    return ((struct texto *)t)->corBorda;
}

char *getTextoCorPreenchimento(Texto t)
{
    return ((struct texto *)t)->corPreenchimento;
}

char *getTextoAncora(Texto t)
{
    return ((struct texto *)t)->ancora;
}

char *getTextoConteudo(Texto t)
{
    return ((struct texto *)t)->conteudo;
}

int getTextoLength(Texto t)
{
    return strlen(((struct texto *)t)->conteudo);
}

void setTextoId(Texto t, int id)
{
    ((struct texto *)t)->id = id;
}

void setTextoX(Texto t, double x)
{
    ((struct texto *)t)->x = x;
}

void setTextoY(Texto t, double y)
{
    ((struct texto *)t)->y = y;
}

void setTextoCorBorda(Texto t, char *corBorda)
{
    ((struct texto *)t)->corBorda = corBorda;
}

void setTextoCorPreenchimento(Texto t, char *corPreenchimento)
{
    ((struct texto *)t)->corPreenchimento = corPreenchimento;
}

void setTextoAncora(Texto t, char *ancora)
{
    ((struct texto *)t)->ancora = ancora;
}

void setTextoConteudo(Texto t, char *conteudo)
{
    ((struct texto *)t)->conteudo = conteudo;
}

void liberarTexto(Texto t)
{
    struct texto *texto = (struct texto *)t;
    free(texto->corBorda);
    free(texto->corPreenchimento);
    free(texto->ancora);
    free(texto->conteudo);
    free(texto);
}

void rotacionaTexto(Texto t, double theta)
{
    ((struct texto *)t)->rotacao += theta;
}

double getTextoRotacao(Texto t)
{
    return ((struct texto *)t)->rotacao;
}