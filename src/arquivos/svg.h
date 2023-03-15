#ifndef _SVG_H_
#define _SVG_H_

#include <stdio.h>

/** Conjunto de funções para facilitar a criação de arquivos SVG. */

/** Inicia um arquivo SVG. */
void svg_init(FILE *svg);

/** Finaliza um arquivo SVG. */
void svg_finalize(FILE *svg);

/** Escreve um retângulo no arquivo SVG. */
void svg_rect(FILE *svg,
              int x,
              int y,
              int w,
              int h,
              char *fill,
              char *stroke,
              char *style);

/** Escreve um círculo no arquivo SVG. */
void svg_circle(FILE *svg,
                int cx,
                int cy,
                int r,
                char *fill,
                char *stroke,
                char *style);

/** Escreve um texto no arquivo SVG. */
void svg_text(FILE *svg,
              int x,
              int y,
              char *text,
              char *fill,
              char *stroke,
              char *style);

/** Escreve uma linha no arquivo SVG. */
void svg_line(FILE *svg,
              int x1,
              int y1,
              int x2,
              int y2,
              char *stroke,
              char *style);

#endif