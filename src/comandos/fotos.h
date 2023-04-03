#ifndef _FOTOS_H
#define _FOTOS_H

#include "../estruturas/lista.h"
#include "../estruturas/fila.h"
#include "../estruturas/clausuras.h"
#include "../estruturas/check.h"
#include "../arquivos/svg.h"
#include <stdio.h>
#include <stdlib.h>

// Funções para lidar com as fotos que os balões tiram

// Estrutura que representa uma foto
// Filas do balão vão guardar isso
typedef void* Foto;

// Função que cria uma foto
// (a lista é o banco de dados geral)
Foto tirarFoto(Lista lista, FILE *svg, Texto balao, FILE *txt, int i);

// Função que imprime uma foto
// (a lista é a foto tirada)
void imprimeFoto(Foto f, FILE *svg, Texto balao, double *dx, double *pontuacao);

// Verifica se a foto foi de base
bool fotoEnviada(Foto f);

// Retorna os elementos em si da foto
Lista getElementosFoto(Foto f);

// Retorna o xOffset da foto
double getXOffsetFoto(Foto f);

// Retorna o yOffset da foto
double getYOffsetFoto(Foto f);

// Função que libera a memória de uma foto
void liberaFoto(Foto f);

#endif