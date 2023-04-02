#include "txt.h"

void reportarCirculo(void *forma, FILE *txt)
{
    Circulo circulo = (Circulo)forma;
    fprintf(txt, "\
Círculo\n\
id: %d\n\
x: %lf\n\
y: %lf\n\
r: %lf\n\
cor de borda: %s\n\
cor de preenchimento: %s\n\
rotação: %lf\n\n",
            getCirculoId(circulo),
            getCirculoX(circulo),
            getCirculoY(circulo),
            getCirculoR(circulo),
            getCirculoCorb(circulo),
            getCirculoCorp(circulo),
            getCirculoRotacao(circulo));
}

void reportarRetangulo(void *forma, FILE *txt)
{
    Retangulo retangulo = (Retangulo)forma;
    fprintf(txt, "\
Retângulo\n\
id: %d\n\
x: %lf\n\
y: %lf\n\
largura: %lf\n\
altura: %lf\n\
cor de borda: %s\n\
cor de preenchimento: %s\n\
rotação: %lf\n\n",
            getRetanguloId(retangulo),
            getRetanguloX(retangulo),
            getRetanguloY(retangulo),
            getRetanguloLargura(retangulo),
            getRetanguloAltura(retangulo),
            getRetanguloCorBorda(retangulo),
            getRetanguloCorPreenchimento(retangulo),
            getRetanguloRotacao(retangulo));
}

void reportarLinha(void *forma, FILE *txt)
{
    Linha linha = (Linha)forma;
    fprintf(txt, "\
Linha\n\
id: %d\n\
x1: %lf\n\
y1: %lf\n\
x2: %lf\n\
y2: %lf\n\
cor: %s\n\
rotação: %lf\n\n",
            getLinhaId(linha),
            getLinhaX1(linha),
            getLinhaY1(linha),
            getLinhaX2(linha),
            getLinhaY2(linha),
            getLinhaCor(linha),
            getLinhaRotacao(linha));
}

void reportarBalao(void *forma, FILE *txt)
{
    Texto texto = (Texto)forma;
    Fila filaAtual;
    for (int i = 0; i < 10; i++)
    {
        filaAtual = getBalaoFilaI(texto, i);
        if (filaAtual != NULL)
        {
            fprintf(txt, "Fila %d - %d fotos\n", i, getQuantidadeFila(filaAtual));
        }
    }
    fprintf(txt, "Atributos da câmera:\nR: %lf\nP: %lf\nH: %lf\n",
            getBalaoR(texto),
            getBalaoP(texto),
            getBalaoH(texto));
}

void printListaInt(Lista lista, FILE *txt)
{
    Iterador iterador = createIterador(lista, false);
    int *valor;
    while (!isIteratorEmpty(iterador))
    {
        valor = (int *)getIteratorNext(iterador);
        fprintf(txt, "%d ", *valor);
    }
}

void reportarCaca(void *forma, FILE *txt)
{
    int disparos;
    Texto caca = (Texto)forma;
    Lista idsAtingidos;
    getCacaInfo(caca, &disparos, &idsAtingidos);
    fprintf(txt, "Disparou %d vezes\n\
Ids dos balões atingidos: ",
            disparos);
    printListaInt(idsAtingidos, txt);
    fprintf(txt, "\n");
}

void reportarTexto(void *forma, FILE *txt)
{
    Texto texto = (Texto)forma;
    fprintf(txt, "\
Texto \"%s\"\n\
id: %d\n\
x: %lf\n\
y: %lf\n\
cor de borda: %s\n\
cor de preenchimento: %s\n\
rotação: %lf\n\n\
âncora: %s\n\
família: %s\n\
tamanho: %s\n",
            getTextoConteudo(texto),
            getTextoId(texto),
            getTextoX(texto),
            getTextoY(texto),
            getTextoCorBorda(texto),
            getTextoCorPreenchimento(texto),
            getTextoRotacao(texto),
            getTextoAncora(texto),
            getTextoFamilia(texto),
            getTextoTamanho(texto));
    if (getTipoVeiculo(texto) == CACA)
        reportarCaca(texto, txt);
    if (getTipoVeiculo(texto) == BALAO)
        reportarBalao(texto, txt);
    fprintf(txt, "\n");
}

void reportarAtributos(void *forma, FILE *txt)
{
    enum TipoForma tipo = getTipoForma(forma);
    switch (tipo)
    {
    case CIRCULO:
        reportarCirculo(forma, txt);
        break;
    case RETANGULO:
        reportarRetangulo(forma, txt);
        break;
    case LINHA:
        reportarLinha(forma, txt);
        break;
    case TEXTO:
        reportarTexto(forma, txt);
        break;
    }
}

void reportarAtributosElemento(void *elemento, FILE *txt)
{
    reportarAtributos(getLst(elemento), txt);
}

void reportarAtributosFold(Item item, Clausura c)
{
    reportarAtributos(item, c);
}