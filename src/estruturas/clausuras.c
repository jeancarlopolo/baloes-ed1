#include "clausuras.h"
#include "../arquivos/svg.h"
#include <string.h>
#include <ctype.h>

struct clausuraSvg
{
    FILE *svg; // arquivo svg
};

struct clausuraId
{
    int id;    // id do item a ser encontrado
    Item item; // item encontrado
};

struct clausuraTxt
{
    FILE *txt; // arquivo txt
};

struct clausuraPontuacao
{
    double pontuacao;
};

struct clausuraMaiorX
{
    double maiorX;
};

struct clausuraDeslocaDireita
{
    double deslocamento;
};

struct clausuraFoto
{
    double xbalao;
    double ybalao;
    double r;
    double p;
    double h;
};

ClausuraSvg criaClausuraSvg(FILE *svg)
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
                 getTextoAncora(item),
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

ClausuraId criaClausuraId(int id)
{
    struct clausuraId *c = malloc(sizeof(struct clausuraId));
    c->id = id;
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

void escreveTxt(Item item, Clausura c)
{
    struct clausuraTxt *clausura = (struct clausuraTxt *)c;
    int *num = item;
    fprintf(clausura->txt, "%d ", *num);
}

// Cria uma clausura que guarda o arquivo txt
ClausuraTxt criaClausuraTxt(FILE *txt)
{
    struct clausuraTxt *c = malloc(sizeof(struct clausuraTxt));
    c->txt = txt;
    return c;
}

// Calcula a pontuação de um círculo
double calculaPontuacaoCirculo(Item item)
{
    double pontuacao = getCirculoArea(item) / 2;
    char *corp = getCirculoCorp(item);
    char *corb = getCirculoCorb(item);
    // converte as cores para uppercase
    for (int i = 0; i < 7; i++)
    {
        corp[i] = toupper(corp[i]);
        corb[i] = toupper(corb[i]);
    }
    if (strncmp(corp, "#FFFF00", 7) == 0 &&
        strncmp(corb, "#FFFFFF", 7) == 0) // planta nuclear
    {
        pontuacao *= 8;
    }
    else if (strncmp(corp, "#FF7F2A", 7) == 0 &&
             strncmp(corb, "#D45500", 7) == 0) // prédio público
    {
        pontuacao *= 2;
    }
    else if (strncmp(corp, "#DE8787", 7) == 0 &&
             strncmp(corb, "#AA0000", 7) == 0) // hospital
    {
        pontuacao *= 4;
    }
    else if (strncmp(corp, "#B3B3B3", 7) == 0 &&
             strncmp(corb, "#FFFFFF", 7) == 0) // ignorar
    {
        pontuacao = 0;
    }
    return pontuacao;
}

// Calcula a pontuação de um retângulo
double calculaPontuacaoRetangulo(Item item)
{
    double pontuacao = getRetanguloArea(item) / 4;
    char *corp = getRetanguloCorPreenchimento(item);
    char *corb = getRetanguloCorBorda(item);
    // converte as cores para uppercase
    for (int i = 0; i < 7; i++)
    {
        corp[i] = toupper(corp[i]);
        corb[i] = toupper(corb[i]);
    }

    if (strncmp(corb, "#80080", 7) == 0)
    {
        pontuacao += 10;
    }
    else if (strncmp(corb, "#AA0088", 7) == 0)
    {
        pontuacao += 15;
    }

    if (strncmp(corb, "#008033", 7) == 0)
    {
        pontuacao += 20;
    }
    else if (strncmp(corb, "#FFCC00", 7) == 0)
    {
        pontuacao += 30;
    }
    return pontuacao;
}

// Calcula a pontuação de uma linha
double calculaPontuacaoLinha(Item item)
{
    double pontuacao = getLinhaComprimento(item);
    char *cor = getLinhaCor(item);
    // converte as cores para uppercase
    for (int i = 0; i < 7; i++)
    {
        cor[i] = toupper(cor[i]);
    }

    if (strncmp(cor, "#FFFF00", 7) == 0) // energia alta potência (eita)
    {
        pontuacao *= 3;
    }
    else if (strncmp(cor, "#DDFF55", 7) == 0) // energia baixa potência (paia)
    {
        pontuacao *= 2;
    }
    else if (strncmp(cor, "#0000FF", 7) == 0) // dados
    {
        pontuacao *= 4;
    }
    return pontuacao;
}

// Calcula a pontuação de um texto
double calculaPontuacaoTexto(Item item)
{
    if (getTipoVeiculo(item) == CACA)
        return 100;
    return getTextoLength(item);
}

ClausuraPontuacao criaClausuraPontuacao(double pontuacao)
{
    struct clausuraPontuacao *c = malloc(sizeof(struct clausuraPontuacao));
    c->pontuacao = pontuacao;
    return c;
}

double getClausuraPontuacao(Clausura c)
{
    return ((struct clausuraPontuacao *)c)->pontuacao;
}

void calculaPontuacao(Item item, Clausura c)
{
    double pontuacao = ((struct clausuraPontuacao *)c)->pontuacao;
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        pontuacao += calculaPontuacaoCirculo(item);
        break;
    case RETANGULO:
        pontuacao += calculaPontuacaoRetangulo(item);
        break;
    case TEXTO:
        pontuacao += calculaPontuacaoTexto(item);
        break;
    case LINHA:
        pontuacao += calculaPontuacaoLinha(item);
        break;
    }
    ((struct clausuraPontuacao *)c)->pontuacao = pontuacao;
}

ClausuraMaiorX criaClausuraMaiorX()
{
    struct clausuraMaiorX *c = malloc(sizeof(struct clausuraMaiorX));
    c->maiorX = 0;
    return c;
}

double getClausuraMaiorX(Clausura c)
{
    return ((struct clausuraMaiorX *)c)->maiorX;
}

void achaMaiorX(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    double maiorX = ((struct clausuraMaiorX *)c)->maiorX;
    switch (tipo)
    {
    case CIRCULO:
        if (getCirculoX(item) + getCirculoR(item) > maiorX)
            maiorX = getCirculoX(item) + getCirculoR(item);
        break;
    case RETANGULO:
        if (getRetanguloX(item) + getRetanguloLargura(item) > maiorX)
            maiorX = getRetanguloX(item) + getRetanguloLargura(item);
        break;
    case TEXTO:
        if (getTextoX(item) > maiorX)
            maiorX = getTextoX(item);
        break;
    case LINHA:
        if (getLinhaX1(item) > maiorX)
            maiorX = getLinhaX1(item);
        if (getLinhaX2(item) > maiorX)
            maiorX = getLinhaX2(item);
        break;
    }
    ((struct clausuraMaiorX *)c)->maiorX = maiorX;
}

ClausuraDeslocaDireita criaClausuraDeslocaDireita(double deslocamento)
{
    struct clausuraDeslocaDireita *c = malloc(sizeof(struct clausuraDeslocaDireita));
    c->deslocamento = deslocamento;
    return c;
}

void deslocaDireita(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    double deslocamento = ((struct clausuraDeslocaDireita *)c)->deslocamento;
    switch (tipo)
    {
    case CIRCULO:
        setCirculoX(item, getCirculoX(item) + deslocamento);
        break;
    case RETANGULO:
        setRetanguloX(item, getRetanguloX(item) + deslocamento);
        break;
    case TEXTO:
        setTextoX(item, getTextoX(item) + deslocamento);
        break;
    case LINHA:
        setLinhaX1(item, getLinhaX1(item) + deslocamento);
        setLinhaX2(item, getLinhaX2(item) + deslocamento);
        break;
    }
}

void moveElementosFoto(Item item, Clausura c)
{
    struct clausuraFoto *clausura = (struct clausuraFoto *)c;
    enum TipoForma tipo = getTipoForma(item);
    double xfoto, yfoto;
    xfoto = clausura->xbalao - clausura->r;
    yfoto = clausura->ybalao + clausura->p;
    switch (tipo)
    {
    case CIRCULO:
        setCirculoX(item, getCirculoX(item) - xfoto);
        setCirculoY(item, getCirculoY(item) - yfoto);
        break;
    case RETANGULO:
        setRetanguloX(item, getRetanguloX(item) - xfoto);
        setRetanguloY(item, getRetanguloY(item) - yfoto);
        break;
    case TEXTO:
        setTextoX(item, getTextoX(item) - xfoto);
        setTextoY(item, getTextoY(item) - yfoto);
        break;
    case LINHA:
        setLinhaX1(item, getLinhaX1(item) - xfoto);
        setLinhaY1(item, getLinhaY1(item) - yfoto);
        setLinhaX2(item, getLinhaX2(item) - xfoto);
        setLinhaY2(item, getLinhaY2(item) - yfoto);
        break;
    }
}

ClausuraFoto criaClausuraFoto(double xbalao, double ybalao, double r, double p, double h)
{
    struct clausuraFoto *c = malloc(sizeof(struct clausuraFoto));
    c->xbalao = xbalao;
    c->ybalao = ybalao;
    c->r = r;
    c->p = p;
    c->h = h;
    return c;
}

void liberaClausuraDeslocaDireita(Clausura c)
{
    free(c);
}

void liberaClausuraSvg(Clausura c)
{
    free(c);
}

void liberaClausuraId(Clausura c)
{
    free(c);
}

void liberaClausuraTxt(Clausura c)
{
    free(c);
}

void liberaClausuraPontuacao(Clausura c)
{
    free(c);
}

void liberaClausuraMaiorX(Clausura c)
{
    free(c);
}

void liberaClausuraFoto(Clausura c)
{
    free(c);
}