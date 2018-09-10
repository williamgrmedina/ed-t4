#ifndef SGV_H
#define SGV_H
#include "Quadra.h"
#include "Hidrante.h"
#include "Torre.h"
#include "Semaforo.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Lista.h"

	typedef void (*Print)(FILE **svg, void *);

void printSvgCirculo(FILE **svg, Circulo c);
void printSvgRetangulo(FILE **svg, Retangulo r);
void printSvgQuadra(FILE **svg, Quadra q);
void printSvgHidrante(FILE **svg, Hidrante h);
void printSvgTorre(FILE **svg, Torre t);
void printSvgSemaforo(FILE **svg, Semaforo s);
void printSvgLine(FILE **svg, double x1, double y1, double x2, double y2);

void printSvgList(FILE **svg, Lista list, Print func);
#endif