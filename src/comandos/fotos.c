#include "fotos.h"
#include "../estruturas/lista.h"

struct foto
{
    Lista lista;
    bool enviado;
};

Foto tirarFoto(Lista lista, FILE *svg, Texto balao)
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
    foto->lista = filter(lista, checkInRect, cRetangulo);
    foto->enviado = false;
    return foto;
}

void imprimeFoto(Foto f, FILE *svg, Texto balao, double *dx)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    Lista lista = fotoDereferenciada->lista;
    ClausuraFoto cFoto = criaClausuraFoto(getTextoX(balao),
                                          getTextoY(balao),
                                          getBalaoR(balao),
                                          getBalaoH(balao),
                                          getBalaoP(balao));
    fold(lista, moveElementosFoto, cFoto);
    liberaClausuraFoto(cFoto);

    ClausuraDeslocaDireita cDesloca = criaClausuraDeslocaDireita(*dx);
    fold(lista, deslocaDireita, cDesloca);
    liberaClausuraDeslocaDireita(cDesloca);

    ClausuraSvg cSvg = criaClausuraSvg(svg);
    fold(lista, escreveSvg, cSvg);
    liberaClausuraSvg(cSvg);

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
    if (getClausuraMaiorX(cMaiorX) > getTextoX(balao) + getBalaoR(balao))
        *dx = getClausuraMaiorX(cMaiorX);
    else
        *dx = getTextoX(balao) + getBalaoR(balao);
    liberaClausuraMaiorX(cMaiorX);
    fotoDereferenciada->enviado = true;
}

bool fotoEnviada(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    return fotoDereferenciada->enviado;
}

void liberaFoto(Foto f)
{
    struct foto *fotoDereferenciada = (struct foto *)f;
    free(fotoDereferenciada);
}