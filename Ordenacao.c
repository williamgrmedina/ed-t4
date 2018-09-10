#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ordenacao.h"
#include "Elemento.h"

Vector ltov(Lista list, Mat matx, Mat maty, Str mid){
    int i;
    char *id;
    Posic p;
    Elemento e;
    Vector vet;
    vet = createVector(length(list));
    p = getFirst(list);
    for (i = 1; i <= length(list); i++){
        id  = (char*)malloc(sizeof(char)*(strlen((mid(getObjt(p)))) + 1));
        strcpy(id, mid(getObjt(p)));
        e = createElemento(matx(getObjt(p)), maty(getObjt(p)), id);
        addVector(vet, e, i);
        p = getNext(p);
    }
    return vet;
}

void heap(Vector vet, int size, int i, Compare cmp, char coodn){
    int l, r, largest, var;
    largest = i;
    l = 2*i;
    r = 2*i + 1;
    if (l < size){
        var = cmp(vet, l, largest, coodn);
        if (var == -1)
            largest = l;
    }
    if (r < size){
        var = cmp(vet, r, largest, coodn);
        if (var == -1)
            largest = r;
    }
    if (i != largest){
        swap(vet, i, largest);
        heap(vet, size, largest, cmp, coodn);
    }
}

void heapSort(Vector vet, Compare cmp, char coodn){
    int i;
    for (i = getSizeVector(vet)/2; i > 0; i--){
        heap(vet, getSizeVector(vet), i, cmp, coodn);
    }
    for (i = getSizeVector(vet); i>0; i--){
        swap(vet, 1, i);
        heap(vet, i, 1, cmp, coodn);
    }
}