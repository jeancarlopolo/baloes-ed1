#include <stdio.h>
#include <stdlib.h>
#include "path.h"

#define MAX 150

struct fullpath
{
    char caminho[MAX];
    char nome[MAX];
    char ext[MAX];
};

void updatePath(Path path, char *dir, char *filename, char *ext)
{
    struct fullpath *p = (struct fullpath *)path;
    char *fullpath = malloc(sizeof(char) * 3 * MAX);
    if (strlen(dir) > 0 && dir[strlen(dir) - 1] != '/')
        strcat(dir, "/");
    snprintf(fullpath, 3 * MAX, "%s%s%s",
             dir,
             filename,
             ext);
    char *caminho = malloc(sizeof(char) * MAX);
    char *nome = malloc(sizeof(char) * MAX);
    char *extensao = malloc(sizeof(char) * MAX);
    strcpy(caminho, "");
    strcpy(nome, "");
    strcpy(extensao, "");
    if (fullpath != NULL)
    {
        if (strcmp(fullpath, "") == 0) // tem nada
            goto end;                  // não tem nada
        char *token = strtok(fullpath, "/");
        while (token != NULL) // tem caminho
        {
            strcat(caminho, nome);
            strcat(caminho, "/");
            strcpy(nome, token);
            token = strtok(NULL, "/");
        }
        token = strtok(nome, ".");
        if (token != NULL) // tem nome e extensão
        {
            strcpy(nome, token);
            token = strtok(NULL, ".");
            if (token != NULL) // tem nome e extensão
            {
                strcpy(extensao, token);
            }
        }
        else // só tem caminho
        {
            strcpy(caminho, nome);
            strcpy(nome, "");
            strcpy(extensao, "");
        }
    }
end:
    strcpy(p->caminho, caminho);
    strcpy(p->nome, nome);
    strcpy(p->ext, extensao);
    free(caminho);
    free(nome);
    free(extensao);
}

Path path_create(char *path)
{
    struct fullpath *p = malloc(sizeof(struct fullpath));
    updatePath(p, path, "", "");
    return p;
}

void path_destroy(Path path)
{
    free(path);
}

char *path_get_full(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    char *fullpath = malloc(sizeof(char) * 3 * MAX);
    snprintf(fullpath, 3 * MAX, "%s%s.%s",
             p->caminho,
             p->nome,
             p->ext);
    return fullpath;
}

char *path_get_dir(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    return p->caminho;
}

char *path_get_filename(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    return p->nome;
}

char *path_get_extension(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    return p->ext;
}

void path_set_dir(Path path, char *dir)
{
    struct fullpath *p = (struct fullpath *)path;
    if (dir[strlen(dir) - 1] != '/')
        strcat(dir, "/");
    strcpy(p->caminho, dir);
}

void path_set_filename(Path path, char *filename)
{
    struct fullpath *p = (struct fullpath *)path;
    strcpy(p->nome, filename);
}

void path_set_extension(Path path, char *ext)
{
    struct fullpath *p = (struct fullpath *)path;
    strcpy(p->ext, ext);
}
