#include "svg.h"
#include <stdio.h>
#include <stdlib.h>

void svg_init(FILE *svg)
{
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
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
              char *fill,
              char *stroke,
              char *style)
{
    fprintf(svg, "\
    <rect x=\"%d\" \
    y=\"%d\" \
    width=\"%d\" \
    height=\"%d\" \
    fill=\"%s\" \
    stroke=\"%s\" \
    style=\"%s\" \
    />\n",
            x,
            y,
            w,
            h,
            fill,
            stroke,
            style);
}

void svg_text(FILE *svg,
              int x,
              int y,
              char *text,
              char *fill,
              char *stroke,
              char *style)
{
    fprintf(svg, "\
    <text x=\"%d\" \
    y=\"%d\" \
    fill=\"%s\" \
    stroke=\"%s\" \
    style=\"%s\" \
    >%s</text>\n",
            x,
            y,
            fill,
            stroke,
            style,
            text);
}

void svg_line(FILE *svg,
              int x1,
              int y1,
              int x2,
              int y2,
              char *stroke,
              char *style)
{
    fprintf(svg, "\
    <line x1=\"%d\" \
    y1=\"%d\" \
    x2=\"%d\" \
    y2=\"%d\" \
    stroke=\"%s\" \
    style=\"%s\" \
    />\n",
            x1,
            y1,
            x2,
            y2,
            stroke,
            style);
}

void svg_circle(FILE *svg,
                int cx,
                int cy,
                int r,
                char *fill,
                char *stroke,
                char *style)
{
    fprintf(svg, "\
    <circle cx=\"%d\" \
    cy=\"%d\" \
    r=\"%d\" \
    fill=\"%s\" \
    stroke=\"%s\" \
    style=\"%s\" \
    />\n",
            cx,
            cy,
            r,
            fill,
            stroke,
            style);
}

