#pragma once

#include <windows.h>

typedef struct
{
	LARGE_INTEGER t0, t1;
} medicao_tempo_t;

void medicao_tempo_inicializar();

void medicao_tempo_iniciar();
void medicao_tempo_parar();
double medicao_tempo_obter_ultima_medida();

void medicao_tempo_iniciar2(medicao_tempo_t* m);
void medicao_tempo_parar2(medicao_tempo_t* m);
double medicao_tempo_obter_ultima_medida2(medicao_tempo_t* m);
