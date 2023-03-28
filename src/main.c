#include "headers.h"

#define MAX 150

int main(int argc, char *argv[])
{
    Path pathEntrada = path_create("");
    Path pathSaida = path_create("");
    Path nomeGeo = NULL, nomeQry = NULL;
    FILE *qry;
    char pathGeo[MAX], pathQry[MAX], nomeSvg[MAX], nomeTxt[MAX];
    Clausura csvg;
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
    csvg = criaClausuraSvg(svg);
    svg_init(svg);

    // COMANDOS DO GEO
    ler_geo(geo, db);

    if (strcmp(path_get_filename(nomeQry), "") == 0)
    {
        snprintf(pathQry, MAX, "%s/%s.%s",
                 path_get_dir(pathEntrada),
                 path_get_filename(nomeQry),
                 path_get_extension(nomeQry));
        qry = fopen(pathQry, "r");
    }

    // COMANDOS DO QRY
    // txt e svgs de fotos são gerados aqui
    // ler_qry(blablabla);

    // printa lista no svg
    // FINAL DO TRABALHO
    fold(db, escreveSvg, csvg);
    svg_finalize(svg);

    // libera memoria hahhahahahhahhahhahahhahahhahaha
    fclose(geo);
    fclose(svg);
    if (nomeQry != NULL)
    {
        fclose(qry);
        path_destroy(nomeQry);
    }
    killLst(db);
    path_destroy(pathEntrada);
    path_destroy(pathSaida);
    path_destroy(nomeGeo);
    return 0;
}