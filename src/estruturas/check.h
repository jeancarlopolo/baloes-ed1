#ifndef _CHECK_H_
#define _CHECK_H_

#include "lista.h"
#include "stdbool.h"
#include "../formas/checkgeo.h"

// Funções do tipo Check para usar na função filter

//------------------------------------------------------------

// Clausura guarda o retângulo a ser verificado
typedef void *ClausuraRetangulo;

// Cria uma clausura que guarda o retângulo a ser verificado
ClausuraRetangulo criaClausuraRetangulo(double x, double y, double w, double h);

// Libera a memória alocada para a clausura
void liberaClausuraRetangulo(ClausuraRetangulo c);

// Verifica se a forma está dentro de um retângulo
bool checkInRect(Item item, Clausura c);

//------------------------------------------------------------

// Clausura guarda o círculo a ser verificado
typedef void *ClausuraCirculo;

// Cria uma clausura que guarda o círculo a ser verificado
ClausuraCirculo criaClausuraCirculo(double x, double y, double r);

// Libera a memória alocada para a clausura
void liberaClausuraCirculo(ClausuraCirculo c);

// Verifica se a forma está dentro de um círculo
bool checkInCircle(Item item, Clausura c);

#endif