#include <stdio.h>
#include <stdlib.h>
#include "path.h"

struct fullpath
{
    char *caminho;
    char *nome;
    char *ext;
};

Path path_create(char *path)
{
    struct fullpath *p = malloc(sizeof(struct fullpath));
    // Encontrar a última ocorrência de '/' no path completo
    char *ultimo_slash = strrchr(path, '/');
    // Se não houver '/', o path é vazio e o nome do arquivo é o path completo
    if (ultimo_slash == NULL)
    {
        strcpy(p->caminho, "");
        strcpy(p->nome, path);
    }
    else
    {
        // Copiar a parte do path completo antes do último '/' para o path
        int len = ultimo_slash - path;
        strncpy(p->caminho, path, len);
        p->caminho[len] = '\0';
        // Copiar a parte do path completo depois do último '/' para o nome do arquivo
        strcpy(p->nome, ultimo_slash + 1);
    }
    // Encontrar a última ocorrência de '.' no nome do arquivo
    char *ultimo_ponto = strrchr(p->nome, '.');
    // Se não houver '.', a extensão é vazia e o nome do arquivo não muda
    if (ultimo_ponto == NULL)
    {
        strcpy(p->ext, "");
    }
    else
    {
        // Copiar a parte do nome do arquivo depois do último '.' para a extensão
        strcpy(p->ext, ultimo_ponto + 1);
        // Remover a extensão do nome do arquivo
        *ultimo_ponto = '\0';
    }
}

void path_destroy(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    free(p->caminho);
    free(p->nome);
    free(p->ext);
    free(p);
}

char *path_get_full(Path path)
{
    struct fullpath *p = (struct fullpath *)path;
    char *path_completo = malloc(sizeof(char) * (strlen(p->caminho) + strlen(p->nome) + strlen(p->ext) + 2));
    // Copiar o path para o path completo
    strcpy(path_completo, p->caminho);
    // Se o path não for vazio e não terminar com '/', adicionar um '/'
    int len = strlen(p->caminho);
    if (len > 0 && p->caminho[len - 1] != '/')
    {
        strcat(path_completo, "/");
    }
    // Concatenar o nome do arquivo ao path completo
    strcat(path_completo, p->nome);
    // Se a extensão não for vazia, adicionar um '.' e concatenar a extensão ao path completo
    if (strlen(p->ext) > 0)
    {
        strcat(path_completo, ".");
        strcat(path_completo, p->ext);
    }
    return path_completo;
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