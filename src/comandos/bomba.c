#include "bomba.h"
#include <math.h>
#include "../estruturas/check.h"
#include "fotos.h"

struct clausuraBomba
{
    Lista db;
};

struct clausuraClone
{
    Lista db;
    double dx;
};

// função fold para remover os elementos da lista 1 (clausura) que estão na lista 2 (item)
void removeIntersecao(Item item, Clausura c)
{
    struct clausuraBomba *cb = (struct clausuraBomba *)c;
    Lista db = cb->db;
    removeLst(db, item);
}

bool checkBalao(Item item, Clausura c)
{
    return getTipoVeiculo(item) == BALAO;
}

void posicaoBomba(double xcaca, double ycaca, double rotacao, double distancia,
                  double *xbomba, double *ybomba)
{
    double radianos = (rotacao + 90) * PI / 180;
    *xbomba = xcaca + distancia * cos(radianos);
    *ybomba = ycaca + distancia * sin(radianos);
}

void clonaElementos(Item item, Clausura c)
{
    struct clausuraClone *cl = (struct clausuraClone *)c;
    Lista db = cl->db;
    double dx = cl->dx;
    Fila filaAtual;
    Foto fotoAtual;
    for (int i = 0; i <= 9; i++)
    {
        filaAtual = getBalaoFilaI(db, i);
        if (filaAtual != NULL)
        {
            fotoAtual = getFilaItem(filaAtual);
        }
    }
}


void explodeBomba(Lista db, double xbomba, double ybomba, enum tipoBomba tipo, double dx, Texto caca)
{
    struct clausuraBomba cb;
    cb.db = db;
    double raio = tipo;
    ClausuraCirculo cc = criaClausuraCirculo(xbomba, ybomba, raio);
    struct clausuraClone cl;
    cl.db = db;
    cl.dx = dx;
    Lista atingidos = filter(db, checkInCircle, cc);
    Lista baloesAtingidos = filter(atingidos, checkBalao, NULL);
    fold(baloesAtingidos, clonaElementos, &cl);
}