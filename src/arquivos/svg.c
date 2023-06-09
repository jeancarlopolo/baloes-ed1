#include "svg.h"
#include <stdio.h>
#include <stdlib.h>

void svg_init(FILE *svg)
{
    //<svg xmlns:svg="http://www.w3.org/2000/svg"
    // xmlns="http://www.w3.org/2000/svg"
    // version="1.1">
    fprintf(svg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" \
xmlns=\"http://www.w3.org/2000/svg\" \
version=\"1.1\">\n");
}

void svg_finalize(FILE *svg)
{
    fprintf(svg, "</svg>\n");
}

void svg_rect(FILE *svg,
              int x,
              int y,
              int w,
              int h,
              double transform,
              char *fill,
              char *stroke,
              char *style)
{
    style = style == NULL ? "" : style;
    fprintf(svg, "<rect \
x=\"%d\" \
y=\"%d\" \
width=\"%d\" \
height=\"%d\" \
fill=\"%s\" \
stroke=\"%s\" \
transform=\"rotate(%f %d %d)\" \
%s \
/>\n",
            x,
            y,
            w,
            h,
            fill,
            stroke,
            transform,
            x,
            y,
            style);
}

void svg_text(FILE *svg,
              int x,
              int y,
              char *text,
              char *fill,
              char *stroke,
              double transform,
              char *family,
              char *weight,
              char *size,
              char *ancora,
              char *style)
{
    style = style == NULL ? "" : style;
    fprintf(svg, "<text \
x=\"%d\" \
y=\"%d\" \
fill=\"%s\" \
stroke=\"%s\" \
transform=\"rotate(%f %d %d)\" \
font-family=\"%s\" \
font-weight=\"%s\" \
font-size=\"%s\" \
text-anchor=\"%s\" \
%s \
>%s</text>\n",
            x,
            y,
            fill,
            stroke,
            transform,
            x,
            y,
            family,
            weight,
            size,
            ancora,
            style,
            text);
}

void svg_line(FILE *svg,
              int x1,
              int y1,
              int x2,
              int y2,
                double transform,
                char *stroke,
                char *style)
{
    style = style == NULL ? "" : style;
    // calcula o centro da linha
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;
    fprintf(svg, "<line \
x1=\"%d\" \
y1=\"%d\" \
x2=\"%d\" \
y2=\"%d\" \
stroke=\"%s\" \
transform=\"rotate(%f %d %d)\" \
%s \
/>\n",
            x1,
            y1,
            x2,
            y2,
            stroke,
            transform,
            cx,
            cy,
            style);
}

void svg_circle(FILE *svg,
                int cx,
                int cy,
                int r,
                double transform,
                char *fill,
                char *stroke,
                char *style)
{
    style = style == NULL ? "" : style;
    fprintf(svg, "<circle \
cx=\"%d\" \
cy=\"%d\" \
r=\"%d\" \
fill=\"%s\" \
stroke=\"%s\" \
transform=\"rotate(%f %d %d)\" \
%s \
/>\n",
            cx,
            cy,
            r,
            fill,
            stroke,
            transform,
            cx,
            cy,
            style);
}
