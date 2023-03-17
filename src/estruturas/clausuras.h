#ifndef _CLASURAS_H
#define _CLASURAS_H

#include "lista.h"
#include "stdio.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

// High-order functions (iteradores)

//------------------------------------------------------------

// Clausura usada na função ApplyClosure escreveSvg
typedef void *ClausuraSvg;

// Cria uma clausura que guarda o arquivo svg
void *criaClausuraSvg(FILE *svg);

// Escreve no arquivo svg (clausura) o item atual
void escreveSvg(Item item, Clausura c);

//------------------------------------------------------------



//------------------------------------------------------------

// Clausura usada na função ApplyClosure acharId
typedef void *ClausuraId;

// Cria uma clausura que guarda o id do item a ser encontrado
void *criaClausuraId(int *id);

// Retorna o item encontrado
// Se não foi encontrado o item, retorna NULL
Item getClausuraItem(Clausura c);

// Clausura guarda o id do item a ser encontrado
// Se o id do item atual for igual ao id guardado, o item atual é guardado na clausura
void acharId(Item item, Clausura c);

//------------------------------------------------------------

#endif