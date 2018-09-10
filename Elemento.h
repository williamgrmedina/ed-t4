#ifndef Elemento_H
#define Elemento_H
#include "Vector.h"

    typedef void *Elemento;

Elemento createElemento(double x, double y, char *id);
char *getElementoId(Elemento c);
double getElementoX(Elemento c);
double getElementoY(Elemento c);
int cmp(Vector vet, int i, int j, char p);
void freeElemento(Elemento e);

#endif