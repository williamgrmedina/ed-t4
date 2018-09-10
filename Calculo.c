#include <stdio.h>
#include "Calculo.h"
#include "Ordenacao.h"
#include <string.h>
#include <math.h>
#include "Elemento.h"
#include "Comandos.h"
#include <stdlib.h>

double min(double a, double b){
    if(a < b)
        return a;
    else
        return b;
}

void ver(Elemento *r1, Elemento *r2, Elemento e1, Elemento e2){
    double d1, d2;
    d1 = sqrt(pow((getElementoX(*r1) - 
    getElementoX(*r2)), 2) + 
    pow((getElementoY(*r1) - 
     getElementoY(*r2)), 2));
    d2 = sqrt(pow((getElementoX(e1) - getElementoX(e2)), 2) + pow((getElementoY(e1) - getElementoY(e2)), 2));
    if (d1 > d2){
        *r1 = e1;
        *r2 = e2;
    }
}

double lessDistanceFront(Vector vet, int last, double minDist, Elemento *r1, Elemento *r2){
    int i, j;
    char *aux;
    
    double auxd;
    heapSort(vet, cmp, 'y');

    for(i = 1; i <= last; i++){
        j = i+1;
        for (; j<=last; j++){
            if ((getElementoY(getObjVector(vet, j)) - getElementoY(getObjVector(vet, i))) < minDist){
                auxd = sqrt(pow((getElementoX(getObjVector(vet, i)) - getElementoX(getObjVector(vet, j))), 2) + pow((getElementoY(getObjVector(vet, i)) - getElementoY(getObjVector(vet, j))), 2));
                if (auxd < minDist){
                    minDist = auxd;
                    ver(r1, r2, getObjVector(vet, i), getObjVector(vet, j));
                }
            }
        }
    }
    return minDist;
}

double lessDistThree(Vector vet, int first, int last, Elemento *r1, Elemento *r2){
    double d1, resp, d3, daux, d2;
    char *aux;
    int size, i, j;
    Elemento e1, e2, e3;
    resp = -1.0;

    for (i = 1; i<=last; i++){
        for(j = i+1; j<=last; j++){
            d1 = sqrt(pow((getElementoX(getObjVector(vet, i)) - getElementoX(getObjVector(vet, j))), 2) + pow((getElementoY(getObjVector(vet, i)) - getElementoY(getObjVector(vet, j))), 2));
            if (resp < 0){
                resp = d1;
                if (*r1 == NULL && *r2 == NULL){
                    *r1 = getObjVector(vet, j);
                    *r2 = getObjVector(vet, i);
                } else
                    ver(r1, r2, getObjVector(vet, j), getObjVector(vet, i));
            }else if (d1 < resp){
                resp = d1;
                ver(r1, r2, getObjVector(vet, j), getObjVector(vet, i));
            }
        }
    }
    return resp;
}

double lessDistance(Vector vet, int first, int last, Elemento *r1, Elemento *r2){
    Vector aux;
    char *str;
    double dl, dr, d, midx, mf, a, resp, x, y;
    Elemento e1;
    int m, i, j;
    if (last <= 3){
        resp = lessDistThree(vet, first, last, r1, r2); 
        return resp;
    }
    m = last/2;
    dl = lessDistance(vet, first, m, r1, r2);
    dr = lessDistance(vet, first + m, last - m, r1, r2);
    d = min(dl, dr);
    aux = createVector(getSizeVector(vet));
    midx = getElementoX(getObjVector(vet, m+1));

    for (i = 1, j = 0; i <= last; i++){
        a = getElementoX(getObjVector(vet, i)) - midx;
        if (a < 0)
            a *= -1;
        if (a < d){
            j++;
            str = (char*)malloc(sizeof(char)*(strlen(getElementoId((Item)getObjVector(vet, i))) + 1));
            strcpy(str, getElementoId((Item)getObjVector(vet, i)));
            x = getElementoX((Item)getObjVector(vet, i));
            y = getElementoY((Item)getObjVector(vet, i));
            e1 = createElemento(x, y, str);
            addVector(aux, e1, j);
        }
    }
    setSizeVector(aux, j);  
    mf = lessDistanceFront(aux, j, d, r1, r2);
    return min(mf, d);
}

