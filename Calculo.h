#ifndef CALCULO_H
#define CALCULO_H
#include "Vector.h"
#include "Elemento.h"

double lessDistance(Vector vet, int first, int last, Elemento *r1, Elemento *r2);
double lessDistThree(Vector vet, int first, int last, Elemento *r1, Elemento *r2);
double lessDistanceFront(Vector vet, int last, double minDist, Elemento *r1, Elemento *r2);

#endif
