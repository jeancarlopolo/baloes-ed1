#ifndef _RETANGULO_H_
#define _RETANGULO_H_

#include "tipos.h"

/** Um retângulo possui id, x, y, largura, altura, cor de borda e cor de preenchimento. */
typedef void *Retangulo;

/** Cria um retângulo com os parâmetros dados. */
Retangulo criaRetangulo(int id, double x, double y, double largura, double altura, char *corBorda, char *corPreenchimento);

/** Retorna o id do retângulo. */
int getRetanguloId(Retangulo r);

/** Retorna a largura do retângulo. */
double getRetanguloLargura(Retangulo r);

/** Retorna a altura do retângulo. */
double getRetanguloAltura(Retangulo r);

/** Retorna a cor de borda do retângulo. */
char *getRetanguloCorBorda(Retangulo r);

/** Retorna a cor de preenchimento do retângulo. */
char *getRetanguloCorPreenchimento(Retangulo r);

/** Retorna o x do retângulo. */
double getRetanguloX(Retangulo r);

/** Retorna o y do retângulo. */
double getRetanguloY(Retangulo r);

/** Retorna a área do retângulo. */
double getRetanguloArea(Retangulo r);

/** Define o id do retângulo. */
void setRetanguloId(Retangulo r, int id);

/** Define a largura do retângulo. */
void setRetanguloLargura(Retangulo r, double largura);

/** Define a altura do retângulo. */
void setRetanguloAltura(Retangulo r, double altura);

/** Define a cor de borda do retângulo. */
void setRetanguloCorBorda(Retangulo r, char *corBorda);

/** Define a cor de preenchimento do retângulo. */
void setRetanguloCorPreenchimento(Retangulo r, char *corPreenchimento);

/** Define o x do retângulo. */
void setRetanguloX(Retangulo r, double x);

/** Define o y do retângulo. */
void setRetanguloY(Retangulo r, double y);

/** Libera a memória alocada para o retângulo. */
void liberaRetangulo(Retangulo r);

#endif