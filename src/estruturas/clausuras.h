#ifndef _CLASURAS_H
#define _CLASURAS_H

#include "lista.h"
#include "stdio.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

// Funções do tipo ApplyClosure para usar na função fold

//------------------------------------------------------------

// Escreve no arquivo svg (clausura) o item atual
void escreveSvg(Item item, Clausura c);

// Clausura usada na função ApplyClosure escreveSvg
typedef void *ClausuraSvg;

// Cria uma clausura que guarda o arquivo svg
ClausuraSvg criaClausuraSvg(FILE *svg);

// Libera a memória alocada para a clausura
void liberaClausuraSvg(Clausura c);


//------------------------------------------------------------

// Clausura guarda o id do item a ser encontrado
// Se o id do item atual for igual ao id guardado, o item atual é guardado na clausura
void acharId(Item item, Clausura c);

// Clausura usada na função ApplyClosure acharId
typedef void *ClausuraId;

// Cria uma clausura que guarda o id do item a ser encontrado
ClausuraId criaClausuraId(int id);

// Retorna o item encontrado
// Se não foi encontrado o item, retorna NULL
Item getClausuraItem(Clausura c);

// Libera a memória alocada para a clausura
void liberaClausuraId(Clausura c);

//------------------------------------------------------------

// Escreve no arquivo txt (clausura) o item atual (int)
// Usado para escrever a lista de ids acertados pelo caça
void escreveTxt(Item item, Clausura c);

// Clausura usada na função ApplyClosure escreveTxt
typedef void *ClausuraTxt;

// Cria uma clausura que guarda o arquivo txt
ClausuraTxt criaClausuraTxt(FILE *txt);

// Libera a memória alocada para a clausura
void liberaClausuraTxt(Clausura c);

//------------------------------------------------------------

// Calcula a pontuação do item atual e guarda na clausura (pontuação total)
void calculaPontuacao(Item item, Clausura c);

// Clausura usada na função ApplyClosure calculaPontuacao
typedef void *ClausuraPontuacao;

// Cria uma clausura que guarda a pontuação total
ClausuraPontuacao criaClausuraPontuacao(double pontuacao);

// Retorna a pontuação total
double getClausuraPontuacao(Clausura c);

// Libera a memória alocada para a clausura
void liberaClausuraPontuacao(Clausura c);

//------------------------------------------------------------

// Acha o ponto com maior x das formas da lista
void achaMaiorX(Item item, Clausura c);

// Clausura usada na função ApplyClosure achaMaiorX
typedef void *ClausuraMaiorX;

// Cria uma clausura que guarda o maior x
ClausuraMaiorX criaClausuraMaiorX();

// Retorna o maior x
double getClausuraMaiorX(Clausura c);

// Libera a memória alocada para a clausura
void liberaClausuraMaiorX(Clausura c);

//------------------------------------------------------------

// Desloca o item atual para a direita (pra encaixar no svg gerado com as fotos)
void deslocaDireita(Item item, Clausura c);

// Clausura usada na função ApplyClosure deslocaDireita
typedef void *ClausuraDeslocaDireita;

// Cria uma clausura que guarda o deslocamento
ClausuraDeslocaDireita criaClausuraDeslocaDireita(double deslocamento);

// Libera a memória alocada para a clausura
void liberaClausuraDeslocaDireita(Clausura c);

//------------------------------------------------------------

// Move os x e y dos elementos da posição original para a posição relativa da foto
void moveElementosFoto(Item item, Clausura c);

// Clausura que guarda os parâmetros da foto
typedef void *ClausuraFoto;

// Cria uma clausura que guarda os parâmetros da foto
ClausuraFoto criaClausuraFoto(double xbalao, double ybalao, double r, double p, double h);

// Libera a memória alocada para a clausura
void liberaClausuraFoto(Clausura c);

#endif