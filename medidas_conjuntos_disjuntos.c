#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_conjuntos_disjuntos(int tam, int** a, int** b)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		a[i] = malloc(tam*sizeof(int));
		b[i] = malloc(tam*sizeof(int));
	}

	aleatorio_seed(1);

	for (i = 0; i < tam; i++)
	{
		a[0][i] = 2*(aleatorio()/2);
		b[0][i] = 2*(aleatorio()/2) + 1;
	}

	for (i = 0; i < tam-1; i++)
	{
		a[1][i] = 2*(aleatorio()/2);
		b[1][i] = 2*(aleatorio()/2) + 1;
	}

	a[1][i] = b[1][i] = aleatorio();

	for (i = 0; i < tam-1; i++)
	{
		a[2][i] = aleatorio() % (100*tam);
		b[2][i] = aleatorio() % (100*tam);
	}

	for (i = 0; i < 3; i++)
	{
		qsort(a[i], tam, sizeof(int), intcmp);
		qsort(b[i], tam, sizeof(int), intcmp);
	}
}

static void destruicao_conjuntos_disjuntos(int** a, int** b)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		free(a[i]);
		free(b[i]);
	}
}

typedef struct
{
	int tam, repeticoes1, repeticoes2;
} parametros_conjuntos_disjuntos_t;

static int obtem_n_conjuntos_disjuntos(const void* p, int i)
{
	const parametros_conjuntos_disjuntos_t* param = p;

	return param[i].tam;
}

#define VARIAVEIS_CONJUNTOS_DISJUNTOS \
	int *a[3], *b[3];                 \
	volatile int temp;                \
	int k;                            \
	int tam = param->tam;

#define INICIALIZACAO_CONJUNTOS_DISJUNTOS \
	inicializacao_conjuntos_disjuntos(tam, a, b);

#define CHAMADA_FUNCAO_CONJUNTOS_DISJUNTOS(FUNCAO)   \
			for (k = 0; k < 3; k++)                  \
			{                                        \
				temp = FUNCAO(a[k], tam, b[k], tam); \
			}

#define DESTRUICAO_CONJUNTOS_DISJUNTOS \
 	destruicao_conjuntos_disjuntos(a, b);

#define ITERACOES_CONJUNTOS_DISJUNTOS (double)repeticoes2*3.0

#define FUNCAO_MEDIDA_CONJUNTOS_DISJUNTOS(FUNCAO) \
FUNCAO_MEDIDA(                                    \
	medidas_ ## FUNCAO,                           \
	parametros_conjuntos_disjuntos_t,             \
	VARIAVEIS_CONJUNTOS_DISJUNTOS,                \
	INICIALIZACAO_CONJUNTOS_DISJUNTOS,            \
	,                                             \
	CHAMADA_FUNCAO_CONJUNTOS_DISJUNTOS(FUNCAO),   \
	DESTRUICAO_CONJUNTOS_DISJUNTOS,               \
	ITERACOES_CONJUNTOS_DISJUNTOS                 \
)

FUNCAO_MEDIDA_CONJUNTOS_DISJUNTOS(conjuntos_disjuntos_simples)

FUNCAO_MEDIDA_CONJUNTOS_DISJUNTOS(conjuntos_disjuntos_eficiente)

void medidas_conjuntos_disjuntos()
{
	const parametros_conjuntos_disjuntos_t parametros_conjuntos_disjuntos_simples[4] =
	{
		{ 10,    50, 20000 },
		{ 100,   50,   500 },
		{ 1000,  50,    10 },
		{ 10000,  5,     1 },
	};

	const parametros_conjuntos_disjuntos_t parametros_conjuntos_disjuntos_eficiente[6] =
	{
		{ 10,      50, 100000 },
		{ 100,     50,   5000 },
		{ 1000,    50,    500 },
		{ 10000,   50,     50 },
		{ 100000,  50,      5 },
		{ 1000000, 20,      1 },
	};
	
	medida(
		medidas_conjuntos_disjuntos_simples,
		"conjuntos_disjuntos_simples()",
		parametros_conjuntos_disjuntos_simples,
		sizeof(parametros_conjuntos_disjuntos_simples)/sizeof(parametros_conjuntos_disjuntos_t),
		obtem_n_conjuntos_disjuntos
	);

	medida(
		medidas_conjuntos_disjuntos_eficiente,
		"conjuntos_disjuntos_eficiente()",
		parametros_conjuntos_disjuntos_eficiente,
		sizeof(parametros_conjuntos_disjuntos_eficiente)/sizeof(parametros_conjuntos_disjuntos_t),
		obtem_n_conjuntos_disjuntos
	);

	printf("\n");
}