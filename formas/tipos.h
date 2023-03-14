#ifndef _TIPOS_H_
#define _TIPOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Conjunto de ferramentas para lidar com o fato de todas as structs serem privadas*/

/** Enumeração com os tipos possíveis de structs na lista principal do programa*/
enum TipoForma {CIRCULO, RETANGULO, TEXTO, LINHA};

/** Função que retorna o tipo de uma forma geométrica*/
enum TipoForma getTipoForma(void* forma);

#endif