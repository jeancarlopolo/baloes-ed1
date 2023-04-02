#include "bomba.h"
#include <math.h>
#include "../estruturas/check.h"
#include "../formas/retangulo.h"
#include "../formas/circulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"
#include "fotos.h"

struct clausuraBomba
{
    Lista db;
};

struct clausuraClone
{
    FILE *txt;
    Lista db;
    Lista atingidos;
    double dx;
    double x, y, r; // coordenadas do centro da bomba e raio
    int *j;
};

struct clausuraInverte
{
    double dx;
    int *j;
};

struct clausuraX
{
    FILE *svg;
};

// tipo um filter, mas retorna uma lista com os endereços dos elementos que estão dentro do raio da bomba
// se fosse um filter, a lista criada seria uma cópia dos elementos e não os endereços
Lista checkInCirculoLista(Lista db, double xbomba, double ybomba, double raio)
{
    Lista lista = createLst(-1);
    Iterador it = createIterador(db, false);
    ClausuraCirculo c = criaClausuraCirculo(xbomba, ybomba, raio);
    while (isIteratorEmpty(it) == false)
    {
        Posic posic = getIteratorNextPosic(it);
        if (checkInCircle(getLst(posic), c))
            insertLst(lista, (Item)posic);
    }
    killIterator(it);
    liberaClausuraCirculo(c);
    return lista;
}

// função fold para remover os elementos da lista 2 (item) que estão na lista 1 que contém os endereços (clausura)
void removeIntersecao(Item item, Clausura c)
{
    struct clausuraBomba *cb = (struct clausuraBomba *)c;
    Lista db = cb->db;
    removeLst(db, item);
}

// função map que faz uma lista com os ids das formas atingidas
// item é o endereço Posic da forma
// c não é usado
Item getIds(Item item, Clausura c)
{
    Posic posic = (Posic)item;
    Item forma = getLst(posic);
    switch (getTipoForma(forma))
    {
    case CIRCULO:
        return (Item)getCirculoId(forma);
    case RETANGULO:
        return (Item)getRetanguloId(forma);
    case LINHA:
        return (Item)getLinhaId(forma);
    case TEXTO:
        return (Item)getTextoId(forma);
    }
    return (Item)-1;
}

// função map que desloca o elemento em dx e inverte as cores
// item é uma Foto
// c é a clausura que contém o deslocamento dx e o id que começa a ser usado para as fotos clonadas
Item deslocaInverte(Item item, Clausura c)
{
    struct clausuraInverte *ci = (struct clausuraInverte *)c;
    double dx = ci->dx;
    int *j = ci->j;
    enum TipoForma tipo = getTipoForma(item);
    switch (tipo)
    {
    case CIRCULO:
        Circulo circulo = criaCirculo(*j,
                                      getCirculoX(item) + dx,
                                      getCirculoY(item),
                                      getCirculoR(item),
                                      getCirculoCorp(item),
                                      getCirculoCorb(item));
        return circulo;
    case RETANGULO:
        Retangulo retangulo = criaRetangulo(*j,
                                            getRetanguloX(item) + dx,
                                            getRetanguloY(item),
                                            getRetanguloAltura(item),
                                            getRetanguloAltura(item),
                                            getRetanguloCorPreenchimento(item),
                                            getRetanguloCorBorda(item));
        return retangulo;
    case LINHA:
        Linha linha = criaLinha(*j,
                                getLinhaX1(item) + dx,
                                getLinhaY1(item),
                                getLinhaX2(item) + dx,
                                getLinhaY2(item),
                                getLinhaCor(item));
        return linha;
    case TEXTO:
        Texto texto = criaTexto(*j,
                                getTextoX(item) + dx,
                                getTextoY(item),
                                getTextoCorPreenchimento(item),
                                getTextoCorBorda(item),
                                getTextoAncora(item),
                                getTextoConteudo(item),
                                getTextoFamilia(item),
                                getTextoPeso(item),
                                getTextoTamanho(item));
        return texto;
    }
    (*j)++;
    return item;
}

// função fold para clonar as fotos não enviadas dos balões que estão dentro do raio da bomba, deslocando-as em dx e invertendo as cores
// e inserir o endereço das fotos clonadas na lista db.
// além disso, insere o endereço das fotos clonadas que estão dentro do raio da bomba na lista de elementos que serão removidos.
// item é o endereço Posic de um balão
// c é a clausura que contém a lista db, o deslocamento dx, lista de elementos que serão removidos e o círculo da bomba
void clonaNaoEnviados(Item item, Clausura c)
{
    struct clausuraClone *cl = (struct clausuraClone *)c;
    Lista db = cl->db;
    Lista atingidos = cl->atingidos;
    double dx = cl->dx;
    Fila filaBalao;
    Foto elementoInicial, elementoAtual;
    Lista elementosFoto, clonados, clonadosEnderecos;
    Texto balaoAtual = getLst(item);
    if (getTipoVeiculo(balaoAtual) == BALAO)
    {
        // percorre as filas do balão atual
        for (int filaAtual = 0; filaAtual < 10; filaAtual++)
        {
            filaBalao = getBalaoFilaI(balaoAtual, filaAtual);
            if (filaBalao == NULL)
                continue;
            elementoInicial = getInicioFila(filaBalao);

            // percorre as fotos da fila atual
            // se a foto não foi enviada, clona a foto e insere na lista db
            // se a foto não foi enviada e está dentro do raio da bomba, insere o endereço da foto na lista de elementos que serão removidos
            do // percorre a fila ao remover o elemento atual e inserindo-o no final até que o elemento atual seja o elemento inicial
            {
                if (fotoEnviada(elementoAtual) == false)
                {
                    elementosFoto = getElementosFoto(elementoAtual);
                    clonados = map(elementosFoto, deslocaInverte, cl);
                    fold(clonados, reportarAtributos, cl->txt);
                    // é meio confuso, mas o que tá acontecendo é o seguinte:
                    // balões -> filas -> fotos -> listas de formas -> formas
                    // clonados é uma lista de formas criadas a partir de uma foto
                    // elas tem o x e as cores mudados
                    // como db também é uma lista de formas, é possível inserir as formas de clonados em db diretamente
                    // então é só inserir clonados inteiro em db
                    // porém, a bomba pode atingir um elemento clonado
                    // então ao invés de percorrer db inteiro de novo pra ver quais clones foram atingidos
                    // é mais fácil percorrer clonados e inserir os elementos atingidos na lista de atingidos

                    /** no entanto, a lista de atingidos é uma lista de endereços, pra dar pra remover da lista db
                     (se fosse uma lista de formas o tempo de execução ia ser O(n²) ao invés de O(n))
                     (visto que teria que percorrer db inteiro pra CADA elemento atingido pra achar ele e remover)
                     (usando endereços dá pra remover direto da lista db usando removeIntersecao) */

                    // então, percorre clonados e insere os endereços dos elementos atingidos na lista de atingidos
                    // por consequência, eles são os mesmos elementos que estão em db, já que inserimos a lista clonados em db

                    // o procedimento é complexo, mas ele faz *exatamente* o que foi pedido da maneira mais eficiente que eu encontrei
                    // poxa sao 5 structs uma dentro da outra, pra percorrer tudo precisa de 5 loops fica feio mas fazer o que né
                    clonadosEnderecos = checkInCirculoLista(clonados, cl->x, cl->y, cl->r);
                    insertPosicLst(db, getFirstLst(clonados), clonados);
                }
                removeFila(filaBalao);
                insereFila(filaBalao, elementoInicial);
                elementoAtual = getInicioFila(filaBalao);
            } while (elementoAtual != elementoInicial);
        }
    }
}

// função filter para filtrar os balões que estão em uma lista de endereços
bool checkBalao(Item item, Clausura c)
{
    if (c == NULL) // pro compilador não reclamar rsrs
        return getTipoVeiculo(getLst(item)) == BALAO;
    return getTipoVeiculo(getLst(item)) == BALAO;
}

void posicaoBomba(double xcaca, double ycaca, double rotacao, double distancia,
                  double *xbomba, double *ybomba)
{
    double radianos = (rotacao + 90) * PI / 180;
    *xbomba = xcaca + distancia * cos(radianos);
    *ybomba = ycaca + distancia * sin(radianos);
}

// função fold para escrever um X vermelho em cada âncora dos elementos atingidos
// item é o endereço Posic de uma forma
// c é a clausura que contém o arquivo svg
void xVermelhoAncoras(Item item, Clausura c)
{
    struct clausuraX *cl = (struct clausuraX *)c;
    enum TipoForma tipo = getTipoForma(getLst(item));
    Item forma = getLst(item);
    double x, y;
    FILE *svg = cl->svg;
    switch (tipo)
    {
    case RETANGULO:
        x = getRetanguloX(forma);
        y = getRetanguloY(forma);
        break;
    case CIRCULO:
        x = getCirculoX(forma);
        y = getCirculoY(forma);
        break;
    case TEXTO:
        x = getTextoX(forma);
        y = getTextoY(forma);
        break;
    case LINHA:
        x = getLinhaX1(forma);
        y = getLinhaY1(forma);
    }
    svg_text(svg, x, y, "X", "FF0000", "FF0000", 0, "sans (sans-serif)", "normal", "20px", "middle", NULL);
    if (tipo == LINHA)
    {
        x = getLinhaX2(forma);
        y = getLinhaY2(forma);
        svg_text(svg, x, y, "X", "FF0000", "FF0000", 0, "sans (sans-serif)", "normal", "20px", "middle", NULL);
    }
}

void explodeBomba(Lista db, double xbomba, double ybomba, enum tipoBomba tipo, double dx, Texto caca, int j, FILE *txt, FILE *svg)
{
    // 1 - cria uma lista com o endereço Posic todos os elementos que estão dentro do raio da bomba
    // 2 - acha os balões que estão dentro do raio da bomba
    // 3 - clona as fotos não enviadas dos balões que estão dentro do raio da bomba, deslocando-as em dx e invertendo as cores
    // 3.5 - escreve os clones no txt
    // 4 - insere o endereço das fotos clonadas na lista db
    // 5 - insere o endereço das fotos clonadas que estão dentro do raio da bomba na lista de elementos que serão removidos
    // 6 - atualiza os dados do caça com o número de disparos e ids atingidos
    // 7 - escreve as coisas no txt
    // 7.5 - X vermelho na ancora das figuras atingidas
    // 8 - remove os elementos da lista db que estão na lista de elementos que serão removidos
    struct clausuraBomba cb;
    cb.db = db;
    double raio = tipo;
    ClausuraCirculo cc = criaClausuraCirculo(xbomba, ybomba, raio);
    struct clausuraClone cl;
    cl.db = db;
    cl.dx = dx;
    cl.x = xbomba;
    cl.y = ybomba;
    cl.r = raio;
    cl.j = &j;
    cl.txt = txt;
    cl.atingidos = NULL;
    struct clausuraX cx;
    cx.svg = svg;
    Lista acertosIdsAntes, acertosIdsAgora;
    Lista atingidos = checkInCirculoLista(db, xbomba, ybomba, raio); // 1
    cl.atingidos = atingidos;
    Lista baloesAtingidos = filter(atingidos, checkBalao, NULL); // 2
    // baloesAtingidos tem os endereços dos balões que estão dentro do raio da bomba
    fprintf(txt, "Clones:\n");                    // 7
    fold(baloesAtingidos, clonaNaoEnviados, &cl); // 3, 4, 5
    getCacaInfo(caca, NULL, &acertosIdsAntes);
    acertosIdsAgora = map(atingidos, getIds, NULL);
    insertPosicLst(acertosIdsAntes, getFirstLst(acertosIdsAgora), acertosIdsAgora); // 6
    cacaDisparou(caca);                                                             // 6
    fprintf(txt, "\nElementos atingidos:\n");                                       // 7
    fold(atingidos, reportarAtributos, txt);                                        // 7
    fold(atingidos, xVermelhoAncoras, &cx);                                         // 7.5
    fold(atingidos, removeIntersecao, &cb);                                         // 8
}