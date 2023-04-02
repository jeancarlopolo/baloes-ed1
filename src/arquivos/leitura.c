#include "leitura.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/linha.h"
#include "../comandos/fotos.h"
#include "../comandos/txt.h"
#include "../comandos/bomba.h"
#include "../estruturas/clausuras.h"
#include "../estruturas/check.h"
#include "../estruturas/map.h"

#define MAX 100

void ler_linha(FILE *arq, char *palavras[], int *n)
{
	char linha[MAX];
	char *token;
	const char *delim = " \t\n";
	int i = 0;
	*n = i;
	// lê uma linha do arquivo
	if (fgets(linha, MAX, arq) != NULL)
	{
		// separa a primeira palavra da linha
		token = strtok(linha, delim);
		// enquanto houver palavras na linha
		while (token != NULL)
		{
			// aloca memória para armazenar a palavra
			palavras[i] = (char *)malloc(strlen(token) + 1);
			// copia a palavra para a variável
			strcpy(palavras[i], token);
			// incrementa o contador de palavras
			i++;
			// separa a próxima palavra da linha
			token = strtok(NULL, delim);
		}
		// atualiza o número de palavras na linha
		*n = i;
	}
	else
	{
		// atualiza o número de palavras na linha
		*n = 0;
	}
}

void ler_geo(FILE *geo, Lista *lista)
{
	char *palavras[MAX];
	char *textoFamilia = "sans (sans-serif)";
	char *textoPeso = "normal";
	char *textoTamanho = "20px";
	int n;
	char **ponteiro = NULL; // strtod
	char texto[MAX];
	// enquanto não chegar ao final do arquivo
	while (true)
	{
		// lê uma linha do arquivo
		ler_linha(geo, palavras, &n);
		if (n > 0)
		{
			if (strcmp(palavras[0], "c") == 0)
			{
				Circulo c = criaCirculo(atoi(palavras[1]),
										strtod(palavras[2], ponteiro),
										strtod(palavras[3], ponteiro),
										strtod(palavras[4], ponteiro),
										palavras[5],
										palavras[6]);
				insertLst(lista, c);
			}
			else if (strcmp(palavras[0], "r") == 0)
			{
				Retangulo r = criaRetangulo(atoi(palavras[1]),
											strtod(palavras[2], ponteiro),
											strtod(palavras[3], ponteiro),
											strtod(palavras[4], ponteiro),
											strtod(palavras[5], ponteiro),
											palavras[6],
											palavras[7]);
				insertLst(lista, r);
			}
			else if (strcmp(palavras[0], "t") == 0)
			{
				strcpy(texto, palavras[7]);
				for (int i = 8; i < n; i++)
				{
					strcat(texto, " ");
					strcat(texto, palavras[i]);
				}
				Texto t = criaTexto(atoi(palavras[1]),
									strtod(palavras[2], ponteiro),
									strtod(palavras[3], ponteiro),
									palavras[4],
									palavras[5],
									palavras[6],
									texto,
									textoFamilia,
									textoPeso,
									textoTamanho);
				insertLst(lista, t);
			}
			else if (strcmp(palavras[0], "l") == 0)
			{
				Linha l = criaLinha(atoi(palavras[1]),
									strtod(palavras[2], ponteiro),
									strtod(palavras[3], ponteiro),
									strtod(palavras[4], ponteiro),
									strtod(palavras[5], ponteiro),
									palavras[6]);
				insertLst(lista, l);
			}
			else if (strcmp(palavras[0], "ts") == 0)
			{
				textoFamilia = palavras[1];
				if (strcmp(palavras[2], "n") == 0)
					textoPeso = "normal";
				else if (strcmp(palavras[2], "b") == 0)
					textoPeso = "bold";
				else if (strcmp(palavras[2], "b+") == 0)
					textoPeso = "bolder";
				else if (strcmp(palavras[2], "l") == 0)
					textoPeso = "lighter";
				textoTamanho = palavras[3];
			}
		}
		else
		{
			break;
		}
	}
}

void moveForma(Item item, double dx, double dy)
{
	enum TipoForma tipo = getTipoForma(item);
	switch (tipo)
	{
	case CIRCULO:; // SÓ DEUS SABE PORQUE EU PRECISO COLOCAR ESSE PONTO E VÍRGULA AQUI
		Circulo c = (Circulo)item;
		setCirculoX(c, getCirculoX(c) + dx);
		setCirculoY(c, getCirculoY(c) + dy);
		break;
	case RETANGULO:;
		Retangulo r = (Retangulo)item;
		setRetanguloX(r, getRetanguloX(r) + dx);
		setRetanguloY(r, getRetanguloY(r) + dy);
		break;
	case TEXTO:;
		Texto t = (Texto)item;
		setTextoX(t, getTextoX(t) + dx);
		setTextoY(t, getTextoY(t) + dy);
		break;
	case LINHA:;
		Linha l = (Linha)item;
		setLinhaX1(l, getLinhaX1(l) + dx);
		setLinhaY1(l, getLinhaY1(l) + dy);
		setLinhaX2(l, getLinhaX2(l) + dx);
		setLinhaY2(l, getLinhaY2(l) + dy);
		break;
	}
}

void giraForma(Item item, double rotacao)
{
	enum TipoForma tipo = getTipoForma(item);
	switch (tipo)
	{
	case CIRCULO:;
		Circulo c = (Circulo)item;
		setCirculoRotacao(c, getCirculoRotacao(c) + rotacao);
		break;
	case RETANGULO:;
		Retangulo r = (Retangulo)item;
		setRetanguloRotacao(r, getRetanguloRotacao(r) + rotacao);
		break;
	case TEXTO:;
		Texto t = (Texto)item;
		rotacionaTexto(t, rotacao); // preguiça de mudar a função
		break;
	case LINHA:;
		Linha l = (Linha)item;
		setLinhaRotacao(l, getLinhaRotacao(l) + rotacao);
		break;
	}
}

void ler_qry(FILE *qry, FILE *svg, FILE *txt, Lista *lista, char *nomeSvg)
{
	char *palavras[MAX];
	int n;
	char **ponteiro = NULL; // strtod
	int id;
	Item itemEncontrado = NULL;
	// enquanto não chegar ao final do arquivo
	while (true)
	{
		// lê uma linha do arquivo
		ler_linha(qry, palavras, &n);
		if (n > 0)
		{
			// escreve no txt a linha lida
			fprintf(txt, "[*] ");
			for (int i = 0; i < n; i++)
			{
				fprintf(txt, "%s ", palavras[i]);
			}
			fprintf(txt, "\n\n");
			if (strcmp(palavras[0], "mv") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				reportarAtributos(itemEncontrado, txt);
				moveForma(itemEncontrado, strtod(palavras[2], ponteiro), strtod(palavras[3], ponteiro));
				fprintf(svg, "APÓS MOVIMENTO\n");
				reportarAtributos(itemEncontrado, txt);
			}
			else if (strcmp(palavras[0], "g") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				reportarAtributos(itemEncontrado, txt);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				reportarAtributos(itemEncontrado, txt);
				giraForma(itemEncontrado, strtod(palavras[2], ponteiro));
				fprintf(svg, "APÓS MOVIMENTO\n");
				reportarAtributos(itemEncontrado, txt);
			}
			else if (strcmp(palavras[0], "ff") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				reportarAtributos(itemEncontrado, txt);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				if (getTipoVeiculo(itemEncontrado) != BALAO)
				{
					fprintf(txt, "ERRO: Forma com id %d não é um balão.\n\n", id);
					continue;
				}
				else
				{
					setBalaoParametros(itemEncontrado, strtod(palavras[2], ponteiro), strtod(palavras[3], ponteiro), strtod(palavras[4], ponteiro));
				}
				reportarAtributos(itemEncontrado, txt);
			}
			else if (strcmp(palavras[0], "tf") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				if (getTipoVeiculo(itemEncontrado) != BALAO)
				{
					fprintf(txt, "ERRO: Forma com id %d não é um balão.\n\n", id);
					continue;
				}
				else
				{
					Fila fila = getBalaoFilaI(itemEncontrado, atoi(palavras[2]));
					if (fila == NULL)
					{
						fprintf(txt, "ERRO: Fila %d não encontrada.\n\n", atoi(palavras[2]));
						continue;
					}
					Foto foto = tirarFoto(lista, svg, itemEncontrado, txt);
					insereFila(fila, foto);
				}
			}
			else if (strcmp(palavras[0], "df") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				if (getTipoVeiculo(itemEncontrado) != BALAO)
				{
					fprintf(txt, "ERRO: Forma com id %d não é um balão.\n\n", id);
					continue;
				}
				else
				{
					char nomeArquivo[100];
					sprintf(nomeArquivo, "%s-%s.svg", nomeSvg, palavras[3]);
					FILE *novoSvg = fopen(nomeArquivo, "w");
					if (novoSvg == NULL)
					{
						fprintf(txt, "ERRO: Arquivo %s não pode ser aberto.\n\n", nomeArquivo);
						continue;
					}

					Fila fila = getBalaoFilaI(itemEncontrado, atoi(palavras[2]));
					if (fila == NULL)
					{
						fprintf(txt, "ERRO: Fila %d não encontrada.\n\n", atoi(palavras[2]));
						continue;
					}
					double *dx = malloc(sizeof(double));
					*dx = 0;
					double *pontuacao = malloc(sizeof(double));
					*pontuacao = 0;
					Foto elementoInicial, elementoAtual;
					Fila filaBalao = getBalaoFilaI(itemEncontrado, atoi(palavras[2]));
					elementoInicial = getInicioFila(filaBalao);
					reportarAtributos(itemEncontrado, txt);

					do // percorre a fila ao remover o elemento atual e inserindo-o no final até que o elemento atual seja o elemento inicial
					{
						imprimeFoto(elementoAtual, novoSvg, itemEncontrado, dx, pontuacao);
						fprintf(txt, "Pontuação: %lf\n", *pontuacao);
						*pontuacao = 0;
						removeFila(filaBalao);
						insereFila(filaBalao, elementoInicial);
						elementoAtual = getInicioFila(filaBalao);
					} while (elementoAtual != elementoInicial);
					free(dx);
					free(pontuacao);
				}
			}
			else if (strcmp(palavras[0], "d") == 0)
			{
				id = atoi(palavras[1]);
				// procura o elemento na lista
				ClausuraId acharIdC = criaClausuraId(id);
				fold(lista, acharId, acharIdC);
				itemEncontrado = getClausuraItem(acharIdC);
				liberaClausuraId(acharIdC);
				if (itemEncontrado == NULL)
				{
					fprintf(txt, "ERRO: Forma com id %d não encontrada.\n\n", id);
					continue;
				}
				if (getTipoVeiculo(itemEncontrado) != CACA)
				{
					fprintf(txt, "ERRO: Forma com id %d não é um caça.\n\n", id);
					continue;
				}
				else
				{
					double xbomba, ybomba;
					enum tipoBomba tipo;
					switch (palavras[2][0])
					{
					case 'A':
						tipo = A;
						break;
					case 'B':
						tipo = B;
						break;
					case 'C':
						tipo = C;
						break;
					default:
						fprintf(txt, "ERRO: Tipo de bomba inválido.\n\n");
					}
					posicaoBomba(getTextoX(itemEncontrado), getTextoY(itemEncontrado), getTextoRotacao(itemEncontrado), tipo, &xbomba, &ybomba);
					explodeBomba(lista, xbomba, ybomba, tipo, strtod(palavras[5], ponteiro), itemEncontrado, atoi(palavras[4]), svg, txt);
				}
			}
			else if (strcmp(palavras[0], "b?") == 0)
			{
				Iterador iterador = createIterador(lista, false);
				while (!isIteratorEmpty(iterador))
				{
					itemEncontrado = getIteratorNext(iterador);
					if (getTipoVeiculo(itemEncontrado) == BALAO)
					{
						reportarAtributos(itemEncontrado, txt);
					}
				}
			}
			else if (strcmp(palavras[0], "c?") == 0)
			{
				Iterador iterador = createIterador(lista, false);
				while (!isIteratorEmpty(iterador))
				{
					itemEncontrado = getIteratorNext(iterador);
					if (getTipoVeiculo(itemEncontrado) == BALAO)
					{
						reportarAtributos(itemEncontrado, txt);
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}