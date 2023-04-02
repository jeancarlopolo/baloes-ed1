#include "texto.h"
#include "../estruturas/lista.h"

struct texto
{
    enum TipoForma tipo;
    enum TipoVeiculo tipoVeiculo;
    struct balao *balaoDados; // só é alocado se o texto for um balão
    struct caca *cacaDados;   // só é alocado se o texto for um caça
    int id;
    double x;
    double y;
    char conteudo[50]; // por favor, não coloque mais de 50 caracteres Evandro eu IMPLORO
    char *corBorda;
    char *corPreenchimento;
    char *ancora;
    double rotacao;
    char *textoFamilia;
    char *textoPeso;
    char *textoTamanho;
};

struct balao
{
    double r;
    double p;
    double h;
    Fila *filaFotos[9]; // 10 filas de fotos
};

struct caca
{
    int disparosEfetuados;
    Lista *idsAcertados;
};

Texto criaTexto(int id, double x, double y, char *corBorda, char *corPreenchimento, char *ancora, char *conteudo, char *textoFamilia, char *textoPeso, char *textoTamanho)
{
    struct texto *t = (struct texto *)malloc(sizeof(struct texto));
    t->tipo = TEXTO;
    t->id = id;
    t->x = x;
    t->y = y;
    t->corBorda = corBorda;
    t->corPreenchimento = corPreenchimento;
    t->ancora = ancora;
    strncpy(t->conteudo, conteudo, 50);
    if (strlen(conteudo) > 50)
    {
        t->conteudo[49] = '\0';
    }
    if (strncmp(conteudo, "v_O_v", 5) == 0)
    {
        t->tipoVeiculo = BALAO;
        t->balaoDados = (struct balao *)malloc(sizeof(struct balao));
        t->balaoDados->r = 0;
        t->balaoDados->p = 0;
        t->balaoDados->h = 0;
        for (int i = 0; i < 10; i++)
        {
            t->balaoDados->filaFotos[i] = criaFila(15);
        }
    }
    else if (strncmp(conteudo, "|-T-|", 5) == 0)
    {
        t->tipoVeiculo = CACA;
        t->cacaDados = (struct caca *)malloc(sizeof(struct caca));
        t->cacaDados->disparosEfetuados = 0;
        t->cacaDados->idsAcertados = createLst(-1);
    }
    else
    {
        t->tipoVeiculo = NENHUM;
    }
    t->rotacao = 0;
    t->textoFamilia = textoFamilia;
    t->textoPeso = textoPeso;
    t->textoTamanho = textoTamanho;
    return t;
}

int getTextoId(Texto t)
{
    return ((struct texto *)t)->id;
}

double getTextoX(Texto t)
{
    return ((struct texto *)t)->x;
}

double getTextoY(Texto t)
{
    return ((struct texto *)t)->y;
}

char *getTextoCorBorda(Texto t)
{
    return ((struct texto *)t)->corBorda;
}

char *getTextoCorPreenchimento(Texto t)
{
    return ((struct texto *)t)->corPreenchimento;
}

char *getTextoAncora(Texto t)
{
    return ((struct texto *)t)->ancora;
}

char *getTextoConteudo(Texto t)
{
    return ((struct texto *)t)->conteudo;
}

int getTextoLength(Texto t)
{
    return strlen(((struct texto *)t)->conteudo);
}

char *getTextoFamilia(Texto t)
{
    return ((struct texto *)t)->textoFamilia;
}

char *getTextoPeso(Texto t)
{
    return ((struct texto *)t)->textoPeso;
}

char *getTextoTamanho(Texto t)
{
    return ((struct texto *)t)->textoTamanho;
}

void setTextoId(Texto t, int id)
{
    ((struct texto *)t)->id = id;
}

void setTextoX(Texto t, double x)
{
    ((struct texto *)t)->x = x;
}

void setTextoY(Texto t, double y)
{
    ((struct texto *)t)->y = y;
}

void setTextoCorBorda(Texto t, char *corBorda)
{
    ((struct texto *)t)->corBorda = corBorda;
}

void setTextoCorPreenchimento(Texto t, char *corPreenchimento)
{
    ((struct texto *)t)->corPreenchimento = corPreenchimento;
}

void setTextoAncora(Texto t, char *ancora)
{
    ((struct texto *)t)->ancora = ancora;
}

void setTextoConteudo(Texto t, char *conteudo)
{
    strncpy(((struct texto *)t)->conteudo, conteudo, 50);
}

void setTextoFamilia(Texto t, char *textoFamilia)
{
    ((struct texto *)t)->textoFamilia = textoFamilia;
}

void setTextoPeso(Texto t, char *textoPeso)
{
    ((struct texto *)t)->textoPeso = textoPeso;
}

void setTextoTamanho(Texto t, char *textoTamanho)
{
    ((struct texto *)t)->textoTamanho = textoTamanho;
}

void liberaTexto(Texto t)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
    {
        for (int i = 0; i < 9; i++)
        {
            destroiFila(texto->balaoDados->filaFotos[i]);
        }
        free(texto->balaoDados);
    }
    else if (texto->tipoVeiculo == CACA)
    {
        killLst(texto->cacaDados->idsAcertados);
        free(texto->cacaDados);
    }
    free(texto);
}

void rotacionaTexto(Texto t, double theta)
{
    ((struct texto *)t)->rotacao += theta;
}

double getTextoRotacao(Texto t)
{
    return ((struct texto *)t)->rotacao;
}

bool setBalaoParametros(Texto t, double r, double p, double h)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
    {
        texto->balaoDados->r = r;
        texto->balaoDados->p = p;
        texto->balaoDados->h = h;
        return true;
    }
    return false;
}

double getBalaoR(Texto t)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
    {
        return texto->balaoDados->r;
    }
    return 0;
}

double getBalaoP(Texto t)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
    {
        return texto->balaoDados->p;
    }
    return 0;
}

double getBalaoH(Texto t)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
    {
        return texto->balaoDados->h;
    }
    return 0;
}

bool cacaAcertou(Texto t, int i)
{
    struct texto *texto = (struct texto *)t;
    Item item = &i;
    if (texto->tipoVeiculo == CACA)
    {
        insertLst(texto->cacaDados->idsAcertados, item);
        return true;
    }
    return false;
}

bool cacaDisparou(Texto t)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == CACA)
    {
        texto->cacaDados->disparosEfetuados++;
        return true;
    }
    return false;
}

bool getCacaInfo(Texto t, int *disparos, Lista *acertos)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == CACA)
    {
        int disparosEfetuados = texto->cacaDados->disparosEfetuados; // copia para evitar problemas de concorrencia
        if (disparos != NULL)
            *disparos = disparosEfetuados;
        if (acertos != NULL)
            *acertos = texto->cacaDados->idsAcertados;
        return true;
    }
    return false;
}

Fila getBalaoFilaI(Texto t, int i)
{
    struct texto *texto = (struct texto *)t;
    if (texto->tipoVeiculo == BALAO)
        return texto->balaoDados->filaFotos[i];
    return NULL;
}
