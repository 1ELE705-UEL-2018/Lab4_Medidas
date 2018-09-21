#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "medidas_aux.h"

static void inicializacao_marca_primos(char** v, int tam)
{
	*v = malloc(tam + 1);
}

static void destruicao_marca_primos(char* v)
{
	free(v);
}

typedef struct
{
	int tam, repeticoes1, repeticoes2;
} parametros_marca_primos_t;

static int obtem_n_marca_primos(const void* p, int i)
{
	const parametros_marca_primos_t* param = p;

	return param[i].tam;
}

#define VARIAVEIS_MARCA_PRIMOS \
	char *v;                   \
	int tam = param->tam;

#define INICIALIZACAO_MARCA_PRIMOS \
	inicializacao_marca_primos(&v, tam);

#define CHAMADA_FUNCAO_MARCA_PRIMOS(FUNCAO) \
			FUNCAO(v, tam);

#define DESTRUICAO_MARCA_PRIMOS \
 	destruicao_marca_primos(v);

#define ITERACOES_MARCA_PRIMOS (double)repeticoes2

#define FUNCAO_MEDIDA_MARCA_PRIMOS(FUNCAO) \
FUNCAO_MEDIDA(                             \
	medidas_ ## FUNCAO,                    \
	parametros_marca_primos_t,             \
	VARIAVEIS_MARCA_PRIMOS,                \
	INICIALIZACAO_MARCA_PRIMOS,            \
	,                                      \
	CHAMADA_FUNCAO_MARCA_PRIMOS(FUNCAO),   \
	DESTRUICAO_MARCA_PRIMOS,               \
	ITERACOES_MARCA_PRIMOS                 \
)

FUNCAO_MEDIDA_MARCA_PRIMOS(marca_primos_simples)

FUNCAO_MEDIDA_MARCA_PRIMOS(marca_primos_busca_ate_raiz)

FUNCAO_MEDIDA_MARCA_PRIMOS(marca_primos_crivo)

void medidas_marca_primos()
{
	parametros_marca_primos_t parametros_marca_primos_simples[4] =
	{
		{ 10,     50, 50000 },
		{ 100,    50,  1000 },
		{ 1000,   50,    20 },
		{ 10000,  10,     1 },
	};

	parametros_marca_primos_t parametros_marca_primos_busca_ate_raiz[6] =
	{
		{ 10,      50, 50000 },
		{ 100,     50,  2000 },
		{ 1000,    50,   200 },
		{ 10000,   50,    10 },
		{ 100000,  20,     1 },
		{ 1000000,  1,     1 },
	};

	parametros_marca_primos_t parametros_marca_primos_crivo[6] =
	{
		{ 10,      50, 500000 },
		{ 100,     50,  50000 },
		{ 1000,    50,   5000 },
		{ 10000,   50,    500 },
		{ 100000,  50,     20 },
		{ 1000000, 50,      2 },
	};

	medida(
		medidas_marca_primos_simples,
		"marca_primos_simples()",
		parametros_marca_primos_simples,
		sizeof(parametros_marca_primos_simples)/sizeof(parametros_marca_primos_t),
		obtem_n_marca_primos
	);

	medida(
		medidas_marca_primos_busca_ate_raiz,
		"marca_primos_busca_ate_raiz()",
		parametros_marca_primos_busca_ate_raiz,
		sizeof(parametros_marca_primos_busca_ate_raiz)/sizeof(parametros_marca_primos_t),
		obtem_n_marca_primos
	);

	medida(
		medidas_marca_primos_crivo,
		"marca_primos_crivo()",
		parametros_marca_primos_crivo,
		sizeof(parametros_marca_primos_crivo)/sizeof(parametros_marca_primos_t),
		obtem_n_marca_primos
	);

	printf("\n");
}