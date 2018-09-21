#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_expmod(int e, int** exps, int num_exps)
{
	int i;
	*exps = malloc(num_exps*sizeof(int));

	aleatorio_seed(1);

	for (i = 0; i < num_exps; i++)
	{
		(*exps)[i] = e + (aleatorio() % e);
	}
}

static void destruicao_expmod(int* exps)
{
	free(exps);
}

typedef struct
{
	int e, repeticoes1, repeticoes2, num_exps;
} parametros_expmod_t;

static int obtem_n_expmod(const void* p, int i)
{
	const parametros_expmod_t* param = p;

	return param[i].e;
}

#define VARIAVEIS_EXPMOD            \
	int *exps;                      \
	volatile int temp;              \
	int k, b, m;                    \
	int e = param->e;               \
	int num_exps = param->num_exps;

#define INICIALIZACAO_EXPMOD \
	inicializacao_expmod(e, &exps, num_exps);

#define INICIALIZACAO_REP1_EXPMOD \
		b = aleatorio() % 32768;  \
		m = aleatorio() % 32768;

#define CHAMADA_FUNCAO_EXPMOD(FUNCAO)         \
			for (k = 0; k < num_exps; k++)    \
			{                                 \
				temp = FUNCAO(b, exps[k], m); \
			}

#define DESTRUICAO_EXPMOD \
 	destruicao_expmod(exps);

#define ITERACOES_EXPMOD (double)repeticoes2*(double)num_exps

#define FUNCAO_MEDIDA_EXPMOD(FUNCAO) \
FUNCAO_MEDIDA(                       \
	medidas_ ## FUNCAO,              \
	parametros_expmod_t,             \
	VARIAVEIS_EXPMOD,                \
	INICIALIZACAO_EXPMOD,            \
	INICIALIZACAO_REP1_EXPMOD,       \
	CHAMADA_FUNCAO_EXPMOD(FUNCAO),   \
	DESTRUICAO_EXPMOD,               \
	ITERACOES_EXPMOD                 \
)

FUNCAO_MEDIDA_EXPMOD(expmod_simples)

FUNCAO_MEDIDA_EXPMOD(expmod_direita_esquerda)

void medidas_expmod()
{
	const parametros_expmod_t parametros_expmod_simples[5] =
	{
		{ 10,     50, 500, 100 },
		{ 100,    50,  20, 100 },
		{ 1000,   50,   2, 100 },
		{ 10000,  20,   1, 100 },
		{ 100000,  5,   1, 100 },
	};

	const parametros_expmod_t parametros_expmod_direita_esquerda[5] =
	{
		{ 10,     50,  2000, 100 },
		{ 100,    50,  1000, 100 },
		{ 1000,   50,   500, 100 },
		{ 10000,  50,   500, 100 },
		{ 100000, 50,   200, 100 },
	};
	
	medida(
		medidas_expmod_simples,
		"expmod_simples()",
		parametros_expmod_simples,
		sizeof(parametros_expmod_simples)/sizeof(parametros_expmod_t),
		obtem_n_expmod
	);

	medida(
		medidas_expmod_direita_esquerda,
		"expmod_direita_esquerda()",
		parametros_expmod_direita_esquerda,
		sizeof(parametros_expmod_direita_esquerda)/sizeof(parametros_expmod_t),
		obtem_n_expmod
	);

	printf("\n");
}