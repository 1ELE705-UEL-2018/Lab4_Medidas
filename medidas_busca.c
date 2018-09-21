#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_busca(int** v, int tam, int** buscado, int num_buscados)
{
	int i;
	*v = malloc(tam*sizeof(int));
	*buscado = malloc(num_buscados*sizeof(int));

	aleatorio_seed(1);

	for (i = 0; i < tam; i++)
	{
		(*v)[i] = (int)(2*(aleatorio()/4));
	}

	qsort(*v, tam, sizeof(int), intcmp);

	for (i = 0; i < num_buscados; i += 2)
	{
		(*buscado)[i] = (*v)[aleatorio() % tam];
		(*buscado)[i+1] = (int)(2*(aleatorio()/4) + 1);
	}
}

static void destruicao_busca(int* v, int* buscado)
{
	free(v);
	free(buscado);
}

typedef struct
{
	int tam, repeticoes1, repeticoes2, num_buscados;
} parametros_busca_t;

static int obtem_n_busca(const void* p, int i)
{
	const parametros_busca_t* param = p;

	return param[i].tam;
}

#define VARIAVEIS_BUSCA                       \
	int *v;                                   \
	int *buscado;                             \
	volatile int temp;                        \
	int k;                                    \
	int tam = param->tam;                     \
	int num_buscados = param->num_buscados;

#define INICIALIZACAO_BUSCA \
	inicializacao_busca(&v, tam, &buscado, num_buscados);

#define CHAMADA_FUNCAO_BUSCA(FUNCAO)               \
			for (k = 0; k < num_buscados; k++)     \
			{                                      \
				temp = FUNCAO(v, tam, buscado[k]); \
			}

#define DESTRUICAO_BUSCA \
 	destruicao_busca(v, buscado);

#define ITERACOES_BUSCA (double)repeticoes2*(double)num_buscados

#define FUNCAO_MEDIDA_BUSCA(FUNCAO) \
FUNCAO_MEDIDA(                      \
	medidas_ ## FUNCAO,             \
	parametros_busca_t,             \
	VARIAVEIS_BUSCA,                \
	INICIALIZACAO_BUSCA,            \
	,                               \
	CHAMADA_FUNCAO_BUSCA(FUNCAO),   \
	DESTRUICAO_BUSCA,               \
	ITERACOES_BUSCA                 \
)

FUNCAO_MEDIDA_BUSCA(busca_linear)

FUNCAO_MEDIDA_BUSCA(busca_binaria)

void medidas_busca()
{
	const parametros_busca_t parametros_busca_linear[6] =
	{
		{ 10,      50, 100000, 10 },
		{ 100,     50,  10000, 10 },
		{ 1000,    50,   1000, 10 },
		{ 10000,   50,    100, 10 },
		{ 100000,  50,     10, 10 },
		{ 1000000, 50,      1, 10 },
	};

	const parametros_busca_t parametros_busca_binaria[6] =
	{
		{ 10,      50,  50000, 10 },
		{ 100,     50,  20000, 10 },
		{ 1000,    50,  10000, 10 },
		{ 10000,   50,  10000, 10 },
		{ 100000,  50,   5000, 10 },
		{ 1000000, 50,   5000, 10 },
	};
	
	medida(
		medidas_busca_linear,
		"busca_linear()",
		parametros_busca_linear,
		sizeof(parametros_busca_linear)/sizeof(parametros_busca_t),
		obtem_n_busca
	);

	medida(
		medidas_busca_binaria,
		"busca_binaria()",
		parametros_busca_binaria,
		sizeof(parametros_busca_binaria)/sizeof(parametros_busca_t),
		obtem_n_busca
	);

	printf("\n");
}