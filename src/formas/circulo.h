#ifndef _CIRCULO_H_
#define _CIRCULO_H_

#include "tipos.h"

/** Um círculo possui id, x, y, raio, cor de borda e cor de preenchimento. */
typedef void* Circulo;

/** Define o valor de PI. */
#define PI 3.14159265358979323846

/** Cria um círculo com os parâmetros dados. */
Circulo criaCirculo(int id, double x, double y, double r, char* corb, char* corp);

/** Retorna o id do círculo. */
int getCirculoId(Circulo c);

/** Retorna a coordenada x do círculo. */
double getCirculoX(Circulo c);

/** Retorna a coordenada y do círculo. */
double getCirculoY(Circulo c);

/** Retorna o raio do círculo. */
double getCirculoR(Circulo c);

/** Retorna a cor de borda do círculo. */
char* getCirculoCorb(Circulo c);

/** Retorna a cor de preenchimento do círculo. */
char* getCirculoCorp(Circulo c);

/** Retorna a área do círculo. */
double getCirculoArea(Circulo c);

/** Define o id do círculo. */
void setCirculoId(Circulo c, int id);

/** Define a coordenada x do círculo. */
void setCirculoX(Circulo c, double x);

/** Define a coordenada y do círculo. */
void setCirculoY(Circulo c, double y);

/** Define o raio do círculo. */
void setCirculoR(Circulo c, double r);

/** Define a cor de borda do círculo. */
void setCirculoCorb(Circulo c, char* corb);

/** Define a cor de preenchimento do círculo. */
void setCirculoCorp(Circulo c, char* corp);

/** Define a rotação do círculo. */
void setCirculoRotacao(Circulo c, double rotacao);

/** Retorna a rotação do círculo. */
double getCirculoRotacao(Circulo c);

/** Libera a memória alocada para o círculo. */
void liberaCirculo(Circulo c);

#endif