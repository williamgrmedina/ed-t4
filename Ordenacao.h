#ifndef ORDENACAO_H
#define ORDENACAO_H
#include "Vector.h"
#include "Lista.h"

typedef char *(*Str)(Item);
typedef double (*Mat)(Item);
typedef int (*Compare)(Vector vet, int i, int j, char p);

Vector ltov(Lista list, Mat matx, Mat maty, Str id);
void heapSort(Vector vet, Compare cmp, char coodn);

#endif