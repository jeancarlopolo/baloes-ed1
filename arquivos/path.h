#ifndef _PATH_H_
#define _PATH_H_

#include <string.h>

/** Uma estrutura para representar o caminho de um arquivo. */
typedef void *Path;

/** Cria um novo caminho a partir de uma string. */
Path path_create(char *path);

/** Libera a memória alocada para o caminho. */
void path_destroy(Path path);

/** Retorna o caminho completo como uma string. */
char *path_get_full(Path path);

/** Retorna o diretório do arquivo. */
char *path_get_dir(Path path);

/** Retorna o nome do arquivo. */
char *path_get_filename(Path path);

/** Retorna a extensão do arquivo. */
char *path_get_extension(Path path);

#endif