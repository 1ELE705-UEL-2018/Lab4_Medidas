#pragma once

int busca_linear(const int v[], int tam, int buscado);
int busca_binaria(const int v[], int tam, int buscado);

double calculo_polinomio_simples(const double coefs[], int ordem, double x);
double calculo_polinomio_horner(const double coefs[], int ordem, double x);

int conjuntos_disjuntos_simples(const int conj1[], int tam1, const int conj2[], int tam2);
int conjuntos_disjuntos_eficiente(const int conj1[], int tam1, const int conj2[], int tam2);

void embaralhamento_simples(int v[], int tam);
void embaralhamento_fisher_yates(int v[], int tam);

int expmod_simples(int b, int e, int m);
int expmod_direita_esquerda(int b, int e, int m);

void marca_primos_simples(char v[], int limite);
void marca_primos_busca_ate_raiz(char v[], int limite);
void marca_primos_crivo(char v[], int limite);

int mdc_simples(int a, int b);
int mdc_euclides(int a, int b);
