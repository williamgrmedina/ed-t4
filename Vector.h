#ifndef Vector_H
#define Vector_H
#include "Lista.h"

	typedef void *Vector;
	typedef void (*Free)(void*);

Vector createVector(int n);
int getSizeVector(Vector vet);
int getQntd(Vector vet);
void setSizeVector(Vector vet, int size);
Item getObjVector(Vector vet, int n);
Posic addVector(Vector vet, Item i, int n);
void swap(Vector vet, int i, int j);
void freeTopo(Vector vet);
void freeVector(Vector vet, Free func);

#endif