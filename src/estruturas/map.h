#ifndef _MAP_H
#define _MAP_H

#include "lista.h"
#include "stdio.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

// Funções do tipo Apply para usar na função map

//------------------------------------------------------------

// Copia o elemento atual para uma nova lista sem nenhuma alteração
Item copiaItem(Item item, Clausura c);

#endif