#ifndef _TXT_H
#define _TXT_H

#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"
#include "../estruturas/lista.h"

// Funções relacionadas ao relatório de texto gerado ao longo da execução do programa

// Escreve no arquivo de texto os atributos de uma forma
void reportarAtributos(void* forma, FILE *txt);

#endif