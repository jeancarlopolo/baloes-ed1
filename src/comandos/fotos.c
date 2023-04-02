#include "fotos.h"
#include "../estruturas/lista.h"
#include "../estruturas/map.h"
#include "../comandos/txt.h"

struct foto
{
    Lista lista;
    bool enviado;
};

struct clausuraFotoTxt
{
    FILE *txt;
};

// a foto já precisa estar com as posições relativas
void reportarFotoTirada(Item item, Clausura c)
{
    Lista lista = (Lista)item;
    enum TipoForma tipo = getTipoForma(lista);
    struct clausuraFotoTxt *cFotoTxt = (struct clausuraFotoTxt *)c;
    FILE *txt = cFotoTxt->txt;
    switch (tipo)
    {
    case CIRCULO:
        fprintf(txt, "Círculo %d fotografado!\n\
X relativo: %lf\n\
Y relativo: %lf\n",
                getCirculoId(lista),
                getCirculoX(lista),
                getCirculoY(lista));
        break;
    case RETANGULO:
        fprintf(txt, "Retângulo %d fotografado!\n\
X relativo: %lf\n\
Y relativo: %lf\n",
                getRetanguloId(lista),
                getRetanguloX(lista),
                getRetanguloY(lista));
        break;
    case LINHA:
        fprintf(txt, "Linha %d fotografada!\n\
X1 relativo: %lf\n\
Y1 relativo: %lf\n\
X2 relativo: %lf\n\
Y2 relativo: %lf\n",
                getLinhaId(lista),
                getLinhaX1(lista),
                getLinhaY1(lista),
                getLinhaX2(lista),
                getLinhaY2(lista));
        break;
    case TEXTO:
        fprintf(txt, "Texto %d fotografado!\n\
X relativo: %lf\n\
Y relativo: %lf\n",
                getTextoId(lista),
                getTextoX(lista),
                getTextoY(lista));
        break;
    }
}

Foto tirarFoto(Lista lista, FILE *svg, Texto balao, FILE *txt)
{
    ClausuraRetangulo cRetangulo = criaClausuraRetangulo(getTextoX(balao) - getBalaoR(balao),
                                                         getTextoY(balao) + getBalaoP(balao),
                                                         2 * getBalaoR(balao),
                                                         getBalaoH(balao));
    svg_rect(svg, getRetanguloX(cRetangulo),
             getRetanguloY(cRetangulo),
             getRetanguloLargura(cRetangulo),
             getRetanguloAltura(cRetangulo),
             "none",
             "red",
             "stroke-dasharray=\"5,3\"");
    liberaClausuraRetangulo(cRetangulo);
    struct foto *foto = malloc(sizeof(struct foto));
    foto->lista = filter(lista, checkInRect, cRetangulo); // elementos são uma cópia dos originais
    foto->enviado = false;
    struct clausuraFotoTxt cFotoTxt;
    cFotoTxt.txt = txt;
    reportarAtributos(balao, txt);
    Lista lista = map(foto->lista, copiaItem, NULL);
    ClausuraFoto cFoto = criaClausuraFoto(getTextoX(balao),
                                          getTextoY(balao),
                                          getBalaoR(balao),
                                          getBalaoH(balao),
                                          getBalaoP(balao));
    fold(lista, moveElementosFoto, cFoto); // move os elementos para o início do svg baseado nas posições relativas
    liberaClausuraFoto(cFoto);
    reportarFotoTirada(lista, &cFotoTxt);
    return foto;
}

void imprimeFoto(Foto f, FILE *svg, Texto balao, double *dx, double *pontuacao)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    Lista lista = map(fotoDereferenciada->lista, copiaItem, NULL); // copia a lista para não alterar a original
    ClausuraFoto cFoto = criaClausuraFoto(getTextoX(balao),
                                          getTextoY(balao),
                                          getBalaoR(balao),
                                          getBalaoH(balao),
                                          getBalaoP(balao));
    fold(lista, moveElementosFoto, cFoto); // move os elementos para o início do svg baseado nas posições relativas
    liberaClausuraFoto(cFoto);

    ClausuraDeslocaDireita cDesloca = criaClausuraDeslocaDireita(*dx);
    fold(lista, deslocaDireita, cDesloca); // desloca os elementos para a direita pra caber no svg
    liberaClausuraDeslocaDireita(cDesloca);

    svg_init(svg);
    ClausuraSvg cSvg = criaClausuraSvg(svg);
    fold(lista, escreveSvg, cSvg); // insere os elementos no svg
    liberaClausuraSvg(cSvg);
    svg_finalize(svg);
    
    char id[20];
    sprintf(id, "Balão: %d", getTextoId(balao));

    ClausuraPontuacao cPontuacao = criaClausuraPontuacao(0);
    fold(lista, calculaPontuacao, cPontuacao);
    char pontuacao[20];
    sprintf(pontuacao, "Pontuação: %.2lf", getClausuraPontuacao(cPontuacao));
    liberaClausuraPontuacao(cPontuacao);

    char r[20];
    sprintf(r, "r: %lf", getBalaoR(balao));

    char h[20];
    sprintf(h, "h: %lf", getBalaoH(balao));

    char p[20];
    sprintf(p, "p: %lf", getBalaoP(balao));

    int distancia = 30; // distancia entre as linhas de texto

    // id do balao, pontuação, r, h, p
    svg_text(svg, *dx, getBalaoH(balao) + distancia, id, "black", "none", 0, "sans (sans-serif)", "normal", "20px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 2 * distancia, pontuacao, "black", "none", 0, "sans (sans-serif)", "normal", "20px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 3 * distancia, r, "black", "none", 0, "sans (sans-serif)", "normal", "20px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 4 * distancia, h, "black", "none", 0, "sans (sans-serif)", "normal", "20px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 5 * distancia, p, "black", "none", 0, "sans (sans-serif)", "normal", "20px", "start", NULL);

    // desenha o retangulo da foto
    svg_rect(svg,
             *dx,
             0,
             getBalaoR(balao) * 2,
             getBalaoH(balao),
             "none",
             "black",
             NULL);

    ClausuraMaiorX cMaiorX = criaClausuraMaiorX();
    fold(lista, achaMaiorX, cMaiorX);
    *dx = getClausuraMaiorX(cMaiorX) > getTextoX(balao) + 2 * getBalaoR(balao) ? getClausuraMaiorX(cMaiorX) : getTextoX(balao) + 2 * getBalaoR(balao);
    liberaClausuraMaiorX(cMaiorX);
    fotoDereferenciada->enviado = true; // marca a foto como enviada
    killLst(lista);
}

bool fotoEnviada(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    return fotoDereferenciada->enviado;
}

Lista getElementosFoto(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    return fotoDereferenciada->lista;
}

void liberaFoto(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    free(fotoDereferenciada);
}