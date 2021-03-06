#include <stdio.h>
#include "Svg.h"
#include <stdlib.h>
#include <math.h>
#include "CalculoCirculoRetangulo.h"

void printSvgCirculo(FILE **svg, Circulo c){
	fprintf(*svg, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getCirculoX(c), getCirculoY(c), getCirculoRaio(c), getCirculoCorPreenchimento(c), getCirculoCorContorno(c));
}
void printSvgRetangulo(FILE **svg, Retangulo r){
	fprintf(*svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getRetanguloX(r), getRetanguloY(r), getRetanguloWidth(r), getRetanguloHeight(r), getRetanguloCorPreenchimento(r), getRetanguloCorContorno(r));
}
void printSvgQuadra(FILE **svg, Quadra q){
	fprintf(*svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n", 
	getQuadraX(q), getQuadraY(q), getQuadraWidth(q), getQuadraHeight(q), getQuadraCorPreenchimento(q), getQuadraCorContorno(q));
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"3\">%s</text>\n", getQuadraX(q), getQuadraY(q), getQuadraCep(q));
}
void printSvgHidrante(FILE **svg, Hidrante h){
	double x, y;
	x = getHidranteX(h) - 3*sqrt(2)/2;
	y = getHidranteY(h) + 3*sqrt(2)/2;
	fprintf(*svg, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n", 
	getHidranteX(h), getHidranteY(h), 3.0, getHidranteCorPreenchimento(h), getHidranteCorContorno(h));
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"5\">H</text>\n",x, y);
}
void printSvgTorre(FILE **svg, Torre t){
	double x, y;
	fprintf(*svg, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getTorreX(t), getTorreY(t), 20.0, getTorreCorPreenchimento(t), getTorreCorContorno(t));
	x = getTorreX(t) - 15;
	y = getTorreY(t) + 20;
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"45\">T</text>\n", x, y);
}
void printSvgSemaforo(FILE **svg, Semaforo s){
	fprintf(*svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getSemaforoX(s), getSemaforoY(s) - 5, 10.0, 18.0, getSemaforoCorPreenchimento(s), getSemaforoCorContorno(s));
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"7\">S</text>\n", getSemaforoX(s), getSemaforoY(s)+3.0);
}

void printSvgLine(FILE **svg, double x1, double y1, double x2, double y2){
	double xm, ym, d;
	fprintf(*svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
	x1, y1, x2, y2);
	xm = (x1 + x2)/2;
	ym = (y1 + y2)/2;
	d = distanciaEntrePontos(x1, y1, x2, y2);
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"5\">%f</text>\n",
	xm, ym, d);
}

void printSvgList(FILE **svg, Lista list, Print func){
	Posic p1 = NULL;
	int n;
	n = length(list);
	p1 = getFirst(list);
	while(n>0){
		func(svg, getObjt(p1));
		n--;
		p1 = getNext(p1);
	}
}