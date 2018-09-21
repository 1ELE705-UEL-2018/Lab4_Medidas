#include <stdio.h>
#include "medicao_tempo.h"

int intcmp(const void* arg1, const void* arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

void medida(double(*funcao_medidas)(const void*, int), const char* nome_funcao, const void* parametros, int num_medidas, int(*obtem_n)(const void*, int))
{
	double min;
	int i;
	medicao_tempo_t m;

	for (i = 0; i < num_medidas; i++)
	{
		medicao_tempo_iniciar2(&m);

		min = funcao_medidas(parametros, i);

		medicao_tempo_parar2(&m);

#ifdef DEBUG_TEMPO_TESTE
		printf("[%lf] ", medicao_tempo_obter_ultima_medida2(&m));
#endif
		printf("%s: n = %d min = %le\n", nome_funcao, obtem_n(parametros, i), min);
	}

}
