#include "medicao_tempo.h"
#include "medidas_busca.h"
#include "medidas_calculo_polinomio.h"
#include "medidas_conjuntos_disjuntos.h"
#include "medidas_embaralhamento.h"
#include "medidas_expmod.h"
#include "medidas_marca_primos.h"
#include "medidas_mdc.h"

int main()
{
	medicao_tempo_inicializar();

	medidas_busca();
	medidas_calculo_polinomio();
	medidas_conjuntos_disjuntos();
	medidas_embaralhamento();
	medidas_expmod();
	medidas_marca_primos();
	medidas_mdc();

    return 0;
}

