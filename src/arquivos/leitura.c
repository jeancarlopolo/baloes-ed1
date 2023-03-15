#include "leitura.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"

#define MAX 100

void ler_linha(FILE *arq, char *palavras[], int *n)
{
  char linha[MAX];             // variável para armazenar a linha
  char *token;                 // variável para armazenar cada palavra
  const char *delim = " \t\n"; // delimitadores de palavras
  int i = 0;                   // contador de palavras

  // lê uma linha do arquivo
  if (fgets(linha, MAX, arq) != NULL)
  {
    // separa a primeira palavra da linha
    token = strtok(linha, delim);
    // enquanto houver palavras na linha
    while (token != NULL)
    {
      // aloca memória para armazenar a palavra
      palavras[i] = (char *)malloc(strlen(token) + 1);
      // copia a palavra para a variável
      strcpy(palavras[i], token);
      // incrementa o contador de palavras
      i++;
      // separa a próxima palavra da linha
      token = strtok(NULL, delim);
    }
    // atualiza o número de palavras na linha
    *n = i;
  }
}

void ler_geo(FILE *geo, Lista *lista)
{
  char *palavras[MAX];
  int n;
  char *ponteiro;
  // enquanto não chegar ao final do arquivo
  while (!feof(geo))
  {
    // lê uma linha do arquivo
    ler_linha(geo, palavras, &n);
    if (n > 0)
    {
      if (strcmp(palavras[0], "c") == 0)
      {
        Circulo c = criaCirculo(palavras[1],
                                strtod(palavras[2], ponteiro),
                                strtod(palavras[3], ponteiro),
                                strtod(palavras[4], ponteiro),
                                palavras[5],
                                palavras[6]);
        insertLst(lista, c);
      }
      else if (strcmp(palavras[0], "r") == 0)
      {
        Retangulo r = criaRetangulo(palavras[1],
                                    strtod(palavras[2], ponteiro),
                                    strtod(palavras[3], ponteiro),
                                    strtod(palavras[4], ponteiro),
                                    strtod(palavras[5], ponteiro),
                                    palavras[6],
                                    palavras[7]);
        insertLst(lista, r);
      }
      else if (strcmp(palavras[0], "t") == 0)
      {
        Texto t = criaTexto(palavras[1],
                            strtod(palavras[2], ponteiro),
                            strtod(palavras[3], ponteiro),
                            palavras[4],
                            palavras[5],
                            palavras[6],
                            palavras[7]);
        insertLst(lista, t);
      }
      else if (strcmp(palavras[0], "l") == 0)
      {
        Linha l = criaLinha(palavras[1],
                            strtod(palavras[2], ponteiro),
                            strtod(palavras[3], ponteiro),
                            strtod(palavras[4], ponteiro),
                            strtod(palavras[5], ponteiro),
                            palavras[6]);
        insertLst(lista, l);
      }
      else if (strcmp(palavras[0], "ts") == 0)
      {
        textoFamilia = palavras[1];
        if (strcmp(palavras[2], "n") == 0)
          textoPeso = "normal";
        else if (strcmp(palavras[2], "b") == 0)
          textoPeso = "bold";
        else if (strcmp(palavras[2], "b+") == 0)
          textoPeso = "bolder";
        else if (strcmp(palavras[2], "l") == 0)
          textoPeso = "lighter";
        textoTamanho = palavras[3];
      }
    }
  }