#ifndef SEMAFORO_H
#define SEMAFORO_H
#include "Retangulo.h"
#include "Circulo.h"

	typedef void *Semaforo;

Semaforo createSemaforo(double x, double y, char *id);
double getSemaforoX(Semaforo h);
double getSemaforoY(Semaforo h);
char *getSemaforoId(Semaforo h);
char *getSemaforoCorPreenchimento(Semaforo h);
char *getSemaforoCorContorno(Semaforo h);
void setSemaforoCorPreenchimento(Semaforo h, char *cor);
void setSemaforoCorContorno(Semaforo h, char *cor);
int semaforoInternoRetangulo(FILE **txt, Semaforo s, Retangulo r);
int semaforoInternoCirculo(FILE **txt, Semaforo s, Circulo c);
void freeSemaforo(Semaforo s);
#endif