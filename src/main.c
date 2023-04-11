#include "headers.h"

#define MAX 150

int main(int argc, char *argv[])
{
    Path pathGeoStruct = path_create("");
    Path pathQryStruct = path_create("");
    Path pathSvgStruct = path_create("");
    Path pathTxtStruct = path_create("");
    char *pathGeo, *pathQry, *nomeSvg, *nomeTxt;
    char *entrada, *saida, *nomeGeo, *nomeQry = "SEM-QRY";
    Clausura csvg;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            entrada = argv[i + 1];
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            nomeGeo = argv[i + 1];
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            nomeQry = argv[i + 1];
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            saida = argv[i + 1];
        }
    }
    updatePath(pathGeoStruct, entrada, nomeGeo, "");
    if (strcmp(path_get_filename(pathGeoStruct), "") == 0)
    {
        printf("Erro: Nome do arquivo geo não informado.\n");
        return 1;
    }
    pathGeo = path_get_full(pathGeoStruct);
    FILE *geo = fopen(pathGeo, "r");
    updatePath(pathQryStruct, entrada, nomeQry, "");

    char *NomeGeoQry = malloc(sizeof(char) * (strlen(path_get_filename(pathGeoStruct)) + strlen(path_get_filename(pathQryStruct)) + 2));
    strcpy(NomeGeoQry, path_get_filename(pathGeoStruct));
    strcat(NomeGeoQry, "-");
    strcat(NomeGeoQry, path_get_filename(pathQryStruct));
    updatePath(pathSvgStruct, saida, NomeGeoQry, ".svg");
    nomeSvg = path_get_full(pathSvgStruct);
    FILE *svg = fopen(nomeSvg, "w");
    updatePath(pathTxtStruct, saida, NomeGeoQry, ".txt");

    Lista db = createLst(-1);
    csvg = criaClausuraSvg(svg);
    svg_init(svg);

    // COMANDOS DO GEO
    ler_geo(geo, db);

    if (strcmp(path_get_filename(pathQryStruct), "SEM-QRY") != 0)
    {
        pathQry = path_get_full(pathQryStruct);
        nomeTxt = path_get_full(pathTxtStruct);
        FILE *qry = fopen(pathQry, "r");
        FILE *txt = fopen(nomeTxt, "w");
        // COMANDOS DO QRY
        ler_qry(qry, svg, txt, db, nomeSvg);
        fclose(qry);
        fclose(txt);
    }

    // printa lista no svg
    // FINAL DO TRABALHO
    fold(db, escreveSvg, csvg);
    svg_finalize(svg);

    // libera memoria hahhahahahhahhahhahahhahahhahaha
    fclose(geo);
    fclose(svg);
    free(pathGeo);
    free(nomeSvg);
    free(nomeTxt);
    free(pathQry);
    path_destroy(pathGeoStruct);
    path_destroy(pathQryStruct);
    path_destroy(pathSvgStruct);
    path_destroy(pathTxtStruct);
    killLst(db);
    return 0;
}