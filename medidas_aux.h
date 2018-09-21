#pragma once

#include <float.h>
#include "medicao_tempo.h"

int intcmp(const void* arg1, const void* arg2);

void medida(
	double(*funcao_medidas)(const void*, int),
	const char* nome_funcao,
	const void* parametros,
	int num_medidas,
	int(*obtem_n)(const void*, int)
);

#define FUNCAO_MEDIDA(NOME_FUNCAO, STRUCT, VARIAVEIS, INICIALIZACAO, INICIALIZACAO_REP1, CHAMADA_FUNCAO, DESTRUICAO, ITERACOES)   \
static double NOME_FUNCAO(const void* p, int n)  \
{                                                \
	const STRUCT* param = (const STRUCT*)p + n;  \
	VARIAVEIS                                    \
	int i, j;                                    \
	double min = DBL_MAX, t;                     \
	int repeticoes1 = param->repeticoes1;        \
	int repeticoes2 = param->repeticoes2;        \
	                                             \
	INICIALIZACAO                                \
	                                             \
	for (i = 0; i < repeticoes1; i++)            \
	{                                            \
		INICIALIZACAO_REP1                       \
		                                         \
		medicao_tempo_iniciar();                 \
		                                         \
		for (j = 0; j < repeticoes2; j++)        \
		{										 \
			CHAMADA_FUNCAO						 \
		}										 \
												 \
		medicao_tempo_parar();					 \
												 \
		t = medicao_tempo_obter_ultima_medida(); \
												 \
		if (t < min)							 \
		{										 \
			min = t;							 \
		}										 \
	}											 \
												 \
	DESTRUICAO                                   \
	                                             \
	return min/(ITERACOES);                      \
}