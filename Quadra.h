#ifndef QUADRA_H
#define QUADRA_H
#include "Retangulo.h"
#include "Circulo.h"

	typedef void *Quadra;

Quadra createQuadra(double x, double y, double width, double height, char *cep);
char *getQuadraCorContorno(Quadra q);
char *getQuadraCorPreenchimento(Quadra q);
void setQuadraCorPreenchimento(Quadra q, char *cor);
void setQuadraCorContorno(Quadra q, char *cor);
char *getQuadraCep(Quadra q);
double getQuadraX(Quadra q);
double getQuadraY(Quadra q);
double getQuadraWidth(Quadra q);
double getQuadraHeight(Quadra q);
int quadraInternaRetangulo(FILE **txt, Quadra q, Retangulo r);
int quadraInternaCirculo(FILE **txt, Quadra q, Circulo c);
void freeQuadra(Quadra q);

#endif