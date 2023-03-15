#include "headers.h"

#define MAX 150

struct clausuraSvg
{
    FILE *svg;
};

void escreveSvg(Item item, Clausura c)
{
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        svg_circle(((struct clausuraSvg *)c)->svg,
                   getCirculoX(item),
                   getCirculoY(item),
                   getCirculoR(item),
                   getCirculoCorp(item),
                   getCirculoCorb(item),
                   NULL);
        break;
    case RETANGULO:
        svg_rect(((struct clausuraSvg *)c)->svg,
                 getRetanguloX(item),
                 getRetanguloY(item),
                 getRetanguloLargura(item),
                 getRetanguloAltura(item),
                 getRetanguloCorPreenchimento(item),
                 getRetanguloCorBorda(item),
                 NULL);
        break;
    case TEXTO:
        svg_text(((struct clausuraSvg *)c)->svg,
                 getTextoX(item),
                 getTextoY(item),
                 getTextoConteudo(item),
                 getTextoCorPreenchimento(item),
                 getTextoCorBorda(item),
                 getTextoRotacao(item),
                 textoFamilia,
                 textoPeso,
                 textoTamanho,
                 NULL);
        break;
    case LINHA:
        svg_line(((struct clausuraSvg *)c)->svg,
                 getLinhaX1(item),
                 getLinhaY1(item),
                 getLinhaX2(item),
                 getLinhaY2(item),
                 getLinhaCor(item),
                 NULL);
        break;
    }
}

int main(int argc, char *argv[])
{
    Path pathEntrada = path_create("");
    Path pathSaida = path_create("");
    Path nomeGeo, nomeQry;
    FILE *qry;
    char pathGeo[MAX], pathQry[MAX], nomeSvg[MAX], nomeTxt[MAX];
    struct clausuraSvg c;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            path_set_dir(pathEntrada, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            nomeGeo = path_create(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            nomeQry = path_create(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            path_set_dir(pathSaida, argv[i + 1]);
        }
    }

    if (nomeQry == NULL)
    {
        nomeQry = path_create("");
    }

    snprintf(pathGeo, MAX, "%s%s.%s",
             path_get_dir(pathEntrada),
             path_get_filename(nomeGeo),
             path_get_extension(nomeGeo));

    snprintf(nomeSvg, MAX, "%s%s-%s.%s",
             path_get_dir(pathSaida),
             path_get_filename(nomeGeo),
             path_get_filename(nomeQry),
             "svg");

    snprintf(nomeTxt, MAX, "%s%s-%s.%s",
             path_get_dir(pathSaida),
             path_get_filename(nomeGeo),
             path_get_filename(nomeQry),
             "txt");

    Lista db = createLst(-1);
    FILE *geo = fopen(pathGeo, "r");
    FILE *svg = fopen(nomeSvg, "w");
    c.svg = svg;
    svg_init(svg);
    ler_geo(geo, db);
    if (strcmp(path_get_filename(nomeQry), "") == 0)
    {
        snprintf(pathQry, MAX, "%s/%s.%s",
                 path_get_dir(pathEntrada),
                 path_get_filename(nomeQry),
                 path_get_extension(nomeQry));
        qry = fopen(pathQry, "r");
    }
    // printa lista no svg
    fold(db, escreveSvg, &c);
    svg_finalize(svg);

    fclose(geo);
    fclose(svg);
    if (nomeQry != NULL)
    {
        fclose(qry);
    }
    killLst(db);
    path_destroy(pathEntrada);
    path_destroy(pathSaida);
    path_destroy(nomeGeo);
    path_destroy(nomeQry);
    return 0;
}