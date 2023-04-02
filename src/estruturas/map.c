#include "map.h"
#include "check.h"
#include "../formas/checkgeo.h"

Circulo copiaCirculo(Item item)
{
    Circulo circulo = criaCirculo(getCirculoId(item),
                                  getCirculoX(item),
                                  getCirculoY(item),
                                  getCirculoR(item),
                                  getCirculoCorb(item),
                                  getCirculoCorp(item));
    return circulo;
}

Retangulo copiaRetangulo(Item item)
{
    Retangulo retangulo = criaRetangulo(getRetanguloId(item),
                                        getRetanguloX(item),
                                        getRetanguloY(item),
                                        getRetanguloLargura(item),
                                        getRetanguloAltura(item),
                                        getRetanguloCorBorda(item),
                                        getRetanguloCorPreenchimento(item));
    return retangulo;
}

Texto copiaTexto(Item item)
{
    Texto texto = criaTexto(getTextoId(item),
                            getTextoX(item),
                            getTextoY(item),
                            getTextoCorBorda(item),
                            getTextoCorPreenchimento(item),
                            getTextoAncora(item),
                            getTextoConteudo(item),
                            getTextoFamilia(item),
                            getTextoPeso(item),
                            getTextoTamanho(item));
    return texto;
}

Linha copiaLinha(Item item)
{
    Linha linha = criaLinha(getLinhaId(item),
                            getLinhaX1(item),
                            getLinhaY1(item),
                            getLinhaX2(item),
                            getLinhaY2(item),
                            getLinhaCor(item));
    return linha;
}

Item copiaItem(Item item, Clausura c)
{
    if (c != NULL)
    {
    }
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        return copiaCirculo(item);
    case RETANGULO:
        return copiaRetangulo(item);
    case TEXTO:
        return copiaTexto(item);
    case LINHA:
        return copiaLinha(item);
    }
    return NULL;
}
