#include "fotos.h"
#include "../estruturas/lista.h"
#include "../estruturas/map.h"
#include "../comandos/txt.h"

struct foto
{
    Lista lista;
    bool enviado;
    double xOffset, yOffset; // offset da foto em relação ao mapa, é usado para "desrelativizar" as formas clonadas
};

struct clausuraFotoTxt
{
    FILE *txt;
};

// a foto já precisa estar com as posições relativas
void reportarFotoTirada(Item item, Clausura c)
{
    Item lista = item;
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
    fprintf(txt, "\n");
}

Foto tirarFoto(Lista lista, FILE *svg, Texto balao, FILE *txt, int i)
{
    ClausuraRetangulo cRetangulo = criaClausuraRetangulo(getTextoX(balao) - getBalaoR(balao),
                                                         getTextoY(balao) + getBalaoP(balao),
                                                         2 * getBalaoR(balao),
                                                         getBalaoH(balao));
    svg_rect(svg, getTextoX(balao) - getBalaoR(balao),
             getTextoY(balao) + getBalaoP(balao),
             2 * getBalaoR(balao),
             getBalaoH(balao),
             0,
             "none",
             "red",
             "stroke-dasharray=\"5,3\"");
    struct foto *foto = malloc(sizeof(struct foto));
    Lista listatemp = filter(lista, checkInRect, cRetangulo); // elementos são uma cópia dos originais
    Lista listanova = map(listatemp, copiaItem, NULL);        // copia a lista para não alterar a original
    killLst(listatemp);
    foto->enviado = false;
    struct clausuraFotoTxt cFotoTxt;
    cFotoTxt.txt = txt;

    ClausuraFoto cFoto = criaClausuraFoto(getTextoX(balao),
                                          getTextoY(balao),
                                          getBalaoR(balao),
                                          getBalaoP(balao),
                                          getBalaoH(balao));
    fold(listanova, moveElementosFoto, cFoto); // move os elementos para o início do svg baseado nas posições relativas
    foto->xOffset = getTextoX(balao) - getBalaoR(balao);
    foto->yOffset = getTextoY(balao) + getBalaoP(balao);
    liberaClausuraFoto(cFoto);
    Fila fila = getBalaoFilaI(balao, i);
    insereFila(fila, foto);
    reportarAtributos(balao, txt);
    fold(listanova, reportarFotoTirada, &cFotoTxt);
    foto->lista = listanova;
    return foto;
}

void imprimeFoto(Foto f, FILE *svg, Texto balao, double *dx, double *pontuacao)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    Lista lista = map(fotoDereferenciada->lista, copiaItem, NULL); // copia a lista para não alterar a original

    ClausuraDeslocaDireita cDesloca = criaClausuraDeslocaDireita(*dx);
    fold(lista, deslocaDireita, cDesloca); // desloca os elementos para a direita pra caber no svg
    liberaClausuraDeslocaDireita(cDesloca);

    ClausuraSvg cSvg = criaClausuraSvg(svg);
    fold(lista, escreveSvg, cSvg); // insere os elementos no svg
    liberaClausuraSvg(cSvg);

    char id[20];
    sprintf(id, "Balão: %d", getTextoId(balao));

    ClausuraPontuacao cPontuacao = criaClausuraPontuacao(0);
    fold(lista, calculaPontuacao, cPontuacao);
    char pontuacaoString[20];
    sprintf(pontuacaoString, "Pontuação: %.2lf", getClausuraPontuacao(cPontuacao));
    *pontuacao = getClausuraPontuacao(cPontuacao);
    liberaClausuraPontuacao(cPontuacao);

    char r[20];
    sprintf(r, "r: %lf", getBalaoR(balao));

    char h[20];
    sprintf(h, "h: %lf", getBalaoH(balao));

    char p[20];
    sprintf(p, "p: %lf", getBalaoP(balao));

    int distancia = 15; // distancia entre as linhas de texto

    // id do balao, pontuação, r, h, p
    svg_text(svg, *dx, getBalaoH(balao) + distancia, id, "black", "none", 0, "sans (sans-serif)", "normal", "15px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 2 * distancia, pontuacaoString, "black", "none", 0, "sans (sans-serif)", "normal", "15px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 3 * distancia, r, "black", "none", 0, "sans (sans-serif)", "normal", "15px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 4 * distancia, h, "black", "none", 0, "sans (sans-serif)", "normal", "15px", "start", NULL);
    svg_text(svg, *dx, getBalaoH(balao) + 5 * distancia, p, "black", "none", 0, "sans (sans-serif)", "normal", "15px", "start", NULL);

    // desenha o retangulo da foto
    svg_rect(svg,
             *dx,
             0,
             getBalaoR(balao) * 2,
             getBalaoH(balao),
             0,
             "none",
             "black",
             NULL);

    ClausuraMaiorX cMaiorX = criaClausuraMaiorX();
    fold(lista, achaMaiorX, cMaiorX);
    double raioBalao = getBalaoR(balao);
    *dx += raioBalao * 2;
    *dx = getClausuraMaiorX(cMaiorX) > *dx ? getClausuraMaiorX(cMaiorX) : *dx; // se alguma forma extrapolar o retangulo, atualiza a posição do retangulo
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

// Retorna o xOffset da foto
double getXOffsetFoto(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    return fotoDereferenciada->xOffset;
}

// Retorna o yOffset da foto
double getYOffsetFoto(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    return fotoDereferenciada->yOffset;
}