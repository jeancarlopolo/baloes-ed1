#ifndef _CHECKGEOMETRY_H
#define _CHECKGEOMETRY_H

#include <math.h>
#include <stdbool.h>

// Funções de verificação da geometria

// Verifica se o ponto está dentro do círculo
bool checkPontoCirculo(double x, double y,
                       double r, double cx, double cy);

// Verifica se o ponto está dentro do retângulo
bool checkPontoRetangulo(double x, double y,
                         double w, double h, double rx, double ry);

// Verifica se o retângulo está dentro do círculo
bool checkRetanguloCirculo(double x, double y, double w, double h,
                           double cx, double cy, double r);

// Verifica se o círculo está dentro do retângulo
bool checkCirculoRetangulo(double cx, double cy, double r,
                           double x, double y, double w, double h);

// Verifica se a linha está dentro do círculo
bool checkLinhaCirculo(double x1, double y1, double x2, double y2,
                       double cx, double cy, double r);

// Verifica se a linha intercepta a linha
bool checkLinhaLinha(double x1, double y1, double x2, double y2,
                     double x3, double y3, double x4, double y4);

// Verifica se a linha está dentro do retângulo
bool checkLinhaRetangulo(double x1, double y1, double x2, double y2,
                         double rx, double ry, double w, double h);

// Verifica se o círculo está dentro do círculo
bool checkCirculoCirculo(double x1, double y1, double r1,
                         double x2, double y2, double r2);

// Verifica se o retângulo está dentro do retângulo
bool checkRetanguloRetangulo(double x1, double y1, double w1, double h1,
                             double x2, double y2, double w2, double h2);

#endif