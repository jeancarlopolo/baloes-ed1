#ifndef _LEITURA_H_
#define _LEITURA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** Conjunto de funções para leitura de arquivos. */

/** Função que lê uma linha de um arquivo e separa as palavras em um vetor de strings.
n é o número de palavras na linha. */
void ler_linha(FILE *arq, char *palavras[], int *n);

#endif