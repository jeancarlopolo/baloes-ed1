#include "headers.h"

int main(int argc, char *argv[])
{
    Path pathEntrada, pathSaida, nomeGeo, nomeQry;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            pathEntrada = path_create(argv[i + 1]);
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
            pathSaida = path_create(argv[i + 1]);
        }
    }
    return 0;
}