#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_mdc(int tam, int** a, int** b, int num_mdcs)
{
	int i;
	*a = malloc(num_mdcs*sizeof(int));
	*b = malloc(num_mdcs*sizeof(int));

	aleatorio_seed(1);

	for (i = 0; i < num_mdcs; i++)
	{
		(*a)[i] = tam + (aleatorio() % tam);
		(*b)[i] = tam + (aleatorio() % tam);
	}
}

static void destruicao_mdc(int* a, int* b)
{
	free(a);
	free(b);
}

typedef struct
{
	int tam, repeticoes1, repeticoes2, num_mdcs;
} parametros_mdc_t;

static int obtem_n_mdc(const void* p, int i)
{
	const parametros_mdc_t* param = p;

	return param[i].tam;
}

#define VARIAVEIS_MDC               \
	int *a, *b;                     \
	volatile int temp;              \
	int k;                          \
	int tam = param->tam;           \
	int num_mdcs = param->num_mdcs;

#define INICIALIZACAO_MDC \
	inicializacao_mdc(tam, &a, &b, num_mdcs);

#define CHAMADA_FUNCAO_MDC(FUNCAO)            \
			for (k = 0; k < num_mdcs; k++)    \
			{                                 \
				temp = FUNCAO(a[k], b[k]);    \
			}

#define DESTRUICAO_MDC \
 	destruicao_mdc(a, b);

#define ITERACOES_MDC (double)repeticoes2*(double)num_mdcs

#define FUNCAO_MEDIDA_MDC(FUNCAO) \
FUNCAO_MEDIDA(                    \
	medidas_ ## FUNCAO,           \
	parametros_mdc_t,             \
	VARIAVEIS_MDC,                \
	INICIALIZACAO_MDC,            \
	,                             \
	CHAMADA_FUNCAO_MDC(FUNCAO),   \
	DESTRUICAO_MDC,               \
	ITERACOES_MDC                 \
)

FUNCAO_MEDIDA_MDC(mdc_simples)

FUNCAO_MEDIDA_MDC(mdc_euclides)

void medidas_mdc()
{
	const parametros_mdc_t parametros_mdc_simples[7] =
	{
		{ 10,       50, 1000, 100 },
		{ 100,      50,  200, 100 },
		{ 1000,     50,   20, 100 },
		{ 10000,    50,   10, 100 },
		{ 100000,   50,    1, 100 },
		{ 1000000,  10,    1, 100 },
		{ 10000000, 2,     1, 100 },
	};

	const parametros_mdc_t parametros_mdc_euclides[9] =
	{
		{ 10,         50,  500, 1000 },
		{ 100,        50,  200, 1000 },
		{ 1000,       50,  100, 1000 },
		{ 10000,      50,  100, 1000 },
		{ 100000,     50,   50, 1000 },
		{ 1000000,    50,   50, 1000 },
		{ 10000000,   50,   50, 1000 },
		{ 100000000,  50,   50, 1000 },
		{ 1000000000, 50,   50, 1000 },
	};
	
	medida(
		medidas_mdc_simples,
		"mdc_simples()",
		parametros_mdc_simples,
		sizeof(parametros_mdc_simples)/sizeof(parametros_mdc_t),
		obtem_n_mdc
	);

	medida(
		medidas_mdc_euclides,
		"mdc_euclides()",
		parametros_mdc_euclides,
		sizeof(parametros_mdc_euclides)/sizeof(parametros_mdc_t),
		obtem_n_mdc
	);

	printf("\n");
}