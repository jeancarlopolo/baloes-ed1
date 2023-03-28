#ifndef _FOTOS_H
#define _FOTOS_H

#include "../estruturas/lista.h"
#include "../estruturas/fila.h"
#include "../estruturas/clausuras.h"
#include "../estruturas/check.h"
#include "../estruturas/map.h"
#include "../arquivos/svg.h"
#include <stdio.h>
#include <stdlib.h>

// Funções para lidar com as fotos que os balões tiram

// Estrutura que representa uma foto
// Filas do balão vão guardar isso
typedef void* Foto;

// Função que cria uma foto
// (a lista é o banco de dados geral)
Foto tirarFoto(Lista lista, FILE *svg, Texto balao);

// Função que imprime uma foto
// (a lista é a foto tirada)
void imprimeFoto(Foto f, FILE *svg, Texto balao, double *dx);

// Verifica se a foto foi enviada para a base
bool fotoEnviada(Foto f);

// Função que libera a memória de uma foto
void liberaFoto(Foto f);

#endif