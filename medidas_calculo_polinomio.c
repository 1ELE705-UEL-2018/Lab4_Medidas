#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"
#include "aleatorio.h"
#include "medidas_aux.h"

static void inicializacao_calculo_polinomio(double** coefs, int ordem)
{
	int i;

	*coefs = malloc((ordem + 1)*sizeof(double));

	for (i = 0; i <= ordem; i++)
	{
		(*coefs)[i] = ((int)aleatorio())/2147483648.0;
	}
}

static void destruicao_calculo_polinomio(double* v)
{
	free(v);
}

typedef struct
{
	int ordem, repeticoes1, repeticoes2;
} parametros_calculo_polinomio_t;

static int obtem_n_calculo_polinomio(const void* p, int i)
{
	const parametros_calculo_polinomio_t* param = p;

	return param[i].ordem;
}

#define VARIAVEIS_CALCULO_POLINOMIO \
	double *coefs;                  \
	volatile double res;            \
	double x;                       \
	int ordem = param->ordem;

#define INICIALIZACAO_CALCULO_POLINOMIO \
	inicializacao_calculo_polinomio(&coefs, ordem);

#define INICIALIZACAO_REP1_CALCULO_POLINOMIO \
		x = 0.9375 + (aleatorio()/68719476736.0);

#define CHAMADA_FUNCAO_CALCULO_POLINOMIO(FUNCAO) \
			res = FUNCAO(coefs, ordem, x);

#define DESTRUICAO_CALCULO_POLINOMIO \
 	destruicao_calculo_polinomio(coefs);

#define ITERACOES_CALCULO_POLINOMIO (double)repeticoes2

#define FUNCAO_MEDIDA_CALCULO_POLINOMIO(FUNCAO) \
FUNCAO_MEDIDA(                                  \
	medidas_ ## FUNCAO,                         \
	parametros_calculo_polinomio_t,             \
	VARIAVEIS_CALCULO_POLINOMIO,                \
	INICIALIZACAO_CALCULO_POLINOMIO,            \
	INICIALIZACAO_REP1_CALCULO_POLINOMIO,       \
	CHAMADA_FUNCAO_CALCULO_POLINOMIO(FUNCAO),   \
	DESTRUICAO_CALCULO_POLINOMIO,               \
	ITERACOES_CALCULO_POLINOMIO                 \
)

FUNCAO_MEDIDA_CALCULO_POLINOMIO(calculo_polinomio_simples)

FUNCAO_MEDIDA_CALCULO_POLINOMIO(calculo_polinomio_horner)

void medidas_calculo_polinomio()
{
	const parametros_calculo_polinomio_t parametros_calculo_polinomio_simples[5] =
	{
		{ 1,     50, 500000 },
		{ 10,    50, 100000 },
		{ 100,   50,   1000 },
		{ 1000,  50,      5 },
		{ 10000,  5,      1 },
	};

	const parametros_calculo_polinomio_t parametros_calculo_polinomio_horner[5] =
	{
		{ 1,     50, 2000000 },
		{ 10,    50,  500000 },
		{ 100,   50,   20000 },
		{ 1000,  50,    2000 },
		{ 10000, 50,     200 },
	};

	medida(
		medidas_calculo_polinomio_simples,
		"calculo_polinomio_simples()",
		parametros_calculo_polinomio_simples,
		sizeof(parametros_calculo_polinomio_simples)/sizeof(parametros_calculo_polinomio_t),
		obtem_n_calculo_polinomio
	);

	medida(
		medidas_calculo_polinomio_horner,
		"calculo_polinomio_horner()",
		parametros_calculo_polinomio_horner,
		sizeof(parametros_calculo_polinomio_horner)/sizeof(parametros_calculo_polinomio_t),
		obtem_n_calculo_polinomio
	);

	printf("\n");
}
