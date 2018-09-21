#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_embaralhamento(int** v, int tam)
{
	*v = malloc(tam*sizeof(int));

	aleatorio_seed(1);
}

static void destruicao_embaralhamento(int* v)
{
	free(v);
}

typedef struct
{
	int tam, repeticoes1, repeticoes2;
} parametros_embaralhamento_t;

static int obtem_n_embaralhamento(const void* p, int i)
{
	const parametros_embaralhamento_t* param = p;

	return param[i].tam;
}

#define VARIAVEIS_EMBARALHAMENTO \
	int *v;                      \
	int tam = param->tam;

#define INICIALIZACAO_EMBARALHAMENTO \
	inicializacao_embaralhamento(&v, tam);

#define CHAMADA_FUNCAO_EMBARALHAMENTO(FUNCAO) \
			FUNCAO(v, tam);

#define DESTRUICAO_EMBARALHAMENTO \
 	destruicao_embaralhamento(v);

#define ITERACOES_EMBARALHAMENTO (double)repeticoes2

#define FUNCAO_MEDIDA_EMBARALHAMENTO(FUNCAO) \
FUNCAO_MEDIDA(                               \
	medidas_ ## FUNCAO,                      \
	parametros_embaralhamento_t,             \
	VARIAVEIS_EMBARALHAMENTO,                \
	INICIALIZACAO_EMBARALHAMENTO,            \
	,                                        \
	CHAMADA_FUNCAO_EMBARALHAMENTO(FUNCAO),   \
	DESTRUICAO_EMBARALHAMENTO,               \
	ITERACOES_EMBARALHAMENTO                 \
)

FUNCAO_MEDIDA_EMBARALHAMENTO(embaralhamento_simples)

FUNCAO_MEDIDA_EMBARALHAMENTO(embaralhamento_fisher_yates)

void medidas_embaralhamento()
{
	parametros_embaralhamento_t parametros_embaralhamento_simples[4] =
	{
		{ 10,    50, 10000 },
		{ 100,   50,   200 },
		{ 1000,  20,    10 },
		{ 10000,  1,     2 },
	};

	parametros_embaralhamento_t parametros_embaralhamento_fisher_yates[6] =
	{
		{ 10,      50, 100000 },
		{ 100,     50,  10000 },
		{ 1000,    50,   1000 },
		{ 10000,   50,    100 },
		{ 100000,  50,     10 },
		{ 1000000, 50,      1 },
	};

	medida(
		medidas_embaralhamento_simples,
		"embaralhamento_simples()",
		parametros_embaralhamento_simples,
		sizeof(parametros_embaralhamento_simples)/sizeof(parametros_embaralhamento_t),
		obtem_n_embaralhamento
	);

	medida(
		medidas_embaralhamento_fisher_yates,
		"embaralhamento_fisher_yates()",
		parametros_embaralhamento_fisher_yates,
		sizeof(parametros_embaralhamento_fisher_yates)/sizeof(parametros_embaralhamento_t),
		obtem_n_embaralhamento
	);

	printf("\n");
}