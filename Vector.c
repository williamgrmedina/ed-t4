#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

typedef struct {
	void *obj;
}vector;

typedef struct{
	int size;
	int qntd;
	vector *vet;
}head;


Vector createVector(int n){
	int i;
	head *newHead;
	vector *newVet;
	newHead = (head*)malloc(sizeof(head));
	newVet = (vector*)calloc(n, sizeof(vector));

	(*newHead).size = n;
	(*newHead).qntd = 0;
	(*newHead).vet = newVet;
	for (i=0; i<n; i++) {
		newVet[i].obj = NULL;
	}
	return (Vector)newHead;
}

int getQntd(Vector vet){
	head *newVector;
	newVector = (head*)vet;
	return newVector->qntd;
}

int getSizeVector(Vector vet){
	head *newVector;
	newVector = (head*)vet;
	return newVector->size;
}

void setSizeVector(Vector vet, int size){
	head *newVet;
	newVet = (head*)vet;
	newVet->size = size;
}

Item getObjVector(Vector vet, int n){
	head *cabeca;
	vector *vetor;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	if (vetor[n-1].obj == NULL)
		return NULL;
	else
		return vetor[n-1].obj;
}

Posic addVector(Vector vet,	Item obj, int n){
	head *cabeca;
	vector *vetor;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	if (vetor[n-1].obj == NULL){
		vetor[n-1].obj = obj;
		return vetor[n-1].obj;
	} else {
		return NULL;
	}
}

void swap(Vector vet, int i, int j){
	head *cabeca;
	vector *vetor, v;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	v.obj = vetor[i-1].obj;
	vetor[i-1].obj = vetor[j-1].obj;
	vetor[j-1].obj = v.obj;
}

void freeTopo(Vector vet){
	head *cabeca = (head*)vet;
	vector *vetor = cabeca->vet;
	if (cabeca != NULL)
		free(cabeca);
	if (vetor != NULL)
		free(vetor);
}

void freeVector(Vector vet, Free func){
	head *cabeca;
	vector *vetor;
	int i;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	for (i = 0; i < cabeca->size; i++){
		func(vetor[i].obj);
		if (vetor[i].obj != NULL){
			free(vetor[i].obj);
			cabeca->size--;
		}
	}
	freeTopo(vet);
}