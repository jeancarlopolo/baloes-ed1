#ifndef _FILA_CIRCULAR_ESTATICA_H
#define _FILA_CIRCULAR_ESTATICA_H

#include <stdbool.h>

/* Uma Fila Circular Estática é uma estrutura de dados que armazena elementos em uma fila
circular, ou seja, o primeiro elemento inserido é o primeiro a ser removido, e assim por
diante. A fila circular estática é implementada com um vetor de tamanho fixo, e possui
uma capacidade máxima de armazenamento. */
typedef void *Fila;

/* Cria uma nova fila circular estática com capacidade para armazenar 'tamanho' elementos */
Fila criaFila(int tamanho);

/* Insere um elemento na fila circular estática
   Retorna true se a inserção foi realizada com sucesso, e false caso contrário */
bool insereFila(Fila fila, void *elemento);

/* Remove um elemento da fila circular estática
   Retorna true se a remoção foi realizada com sucesso, e false caso contrário */
bool removeFila(Fila fila);

/* Retorna o elemento que está no início da fila circular estática */
void *inicioFila(Fila fila);

/* Retorna o elemento que está no final da fila circular estática */
void *finalFila(Fila fila);

/* Retorna o número de elementos armazenados na fila circular estática */
int tamanhoFila(Fila fila);

/* Libera a memória alocada para a fila circular estática */
void destroiFila(Fila fila);

#endif