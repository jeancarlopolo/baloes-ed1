#ifndef _BOMBA_H
#define _BOMBA_H

#include "../estruturas/lista.h"
#include "../formas/texto.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../comandos/txt.h"


// Funções relativas a bombas lançadas por caças

// Tipos de bombas com seus respectivos raios
enum tipoBomba
{
    A = 10,
    B = 15,
    C = 30,
};

// Calcula a posição da bomba lançada pelo caça
void posicaoBomba(double xcaca, double ycaca, double rotacao, double distancia,
                  double *xbomba, double *ybomba);

// Explode a bomba
// dx é a distância que os elementos clonados devem ser transladados
void explodeBomba(Lista db, double xbomba, double ybomba, enum tipoBomba tipo, double dx, Texto caca, int j, FILE *txt, FILE *svg);

#endif