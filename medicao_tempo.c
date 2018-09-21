#include "medicao_tempo.h"
#include <windows.h>

static double freq;
static LARGE_INTEGER t0, t1;

void medicao_tempo_inicializar()
{
	LARGE_INTEGER f;

	QueryPerformanceFrequency(&f);

	freq = (double)f.QuadPart;
}

void medicao_tempo_iniciar()
{
	QueryPerformanceCounter(&t0);
}

void medicao_tempo_parar()
{
	QueryPerformanceCounter(&t1);
}

double medicao_tempo_obter_ultima_medida()
{
	return (t1.QuadPart - t0.QuadPart)/freq;
}

void medicao_tempo_iniciar2(medicao_tempo_t* m)
{
	QueryPerformanceCounter(&m->t0);
}

void medicao_tempo_parar2(medicao_tempo_t* m)
{
	QueryPerformanceCounter(&m->t1);
}

double medicao_tempo_obter_ultima_medida2(medicao_tempo_t* m)
{
	return (m->t1.QuadPart - m->t0.QuadPart)/freq;
}