#ifndef _FILA_CIRCULAR_ESTATICA_H
#define _FILA_CIRCULAR_ESTATICA_H

#include <stdbool.h>

// Estrutura de dados da fila circular estática
typedef void *Fila;

// Cria uma fila com o tamanho máximo dado
Fila criaFila(int tamanho);

// Insere um elemento na fila
bool insereFila(Fila fila, void *elemento);

// Remove um elemento da fila
bool removeFila(Fila fila);

// Retorna o elemento do início da fila
void *getInicioFila(Fila fila);

// Retorna o elemento do fim da fila
void *getFimFila(Fila fila);

// Retorna o próximo elemento da fila
void *getProximoFila(Fila fila, void *elemento);

// Retorna o tamanho máximo da fila
int getTamanhoFila(Fila fila);

// Retorna o número de elementos na fila
int getQuantidadeFila(Fila fila);

// Retorna se a fila está vazia
bool isVaziaFila(Fila fila);

// Retorna se a fila está cheia
bool isCheiaFila(Fila fila);

// Libera a memória alocada para a fila
void destroiFila(Fila fila);

#endif