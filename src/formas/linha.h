#ifndef _LINHA_H_
#define _LINHA_H_

#include "tipos.h"

/** Uma linha possui id, x1, y1, x2, y2 e cor.*/
typedef void* Linha;

/** Cria uma linha com os parâmetros dados. */
Linha criaLinha(int id, double x1, double y1, double x2, double y2, char *cor);

/** Retorna o id da linha. */
int getLinhaId(Linha l);

/** Retorna o x1 da linha. */
double getLinhaX1(Linha l);

/** Retorna o y1 da linha. */
double getLinhaY1(Linha l);

/** Retorna o x2 da linha. */
double getLinhaX2(Linha l);

/** Retorna o y2 da linha. */
double getLinhaY2(Linha l);

/** Retorna a cor da linha. */
char* getLinhaCor(Linha l);

/** Retorna o comprimento da linha. */
double getLinhaComprimento(Linha l);

/** Retorna a rotação da linha*/
double getLinhaRotacao(Linha l);

/** Define o id da linha. */
void setLinhaId(Linha l, int id);

/** Define o x1 da linha. */
void setLinhaX1(Linha l, double x1);

/** Define o y1 da linha. */
void setLinhaY1(Linha l, double y1);

/** Define o x2 da linha. */
void setLinhaX2(Linha l, double x2);

/** Define o y2 da linha. */
void setLinhaY2(Linha l, double y2);

/** Define a cor da linha. */
void setLinhaCor(Linha l, char *cor);

/** Define a rotação da linha*/
void setLinhaRotacao(Linha l, double rotacao);

/** Libera a memória alocada para a linha. */
void liberaLinha(Linha l);

#endif