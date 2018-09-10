#include <stdio.h>
#include <stdlib.h>
#include "Retangulo.h"
#include "Circulo.h"
#include "Comandos.h"
#include "CalculoCirculoRetangulo.h"
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Svg.h"

int main (int argc, char **argv){
	Lista listCir, listRet, listQua, listSem, listHid, listTor;
	listSem = createList();
	listTor = createList();
	listRet = createList();
	listCir = createList();
	listQua = createList();
	listHid = createList();
	FILE *svgMain, *svgQry;
	int a, b;
	double  svgW = 0, svgH = 0;
	char *str, *str2, *str3, *str4;
	svgMain = NULL; 
	svgW = 0.0;
	svgH = 0.0;
	str = pegaParametro(argc, argv, "-o");
	if (str == NULL){
		printf("Diretório de saída não informado\n");
		return 0;
	} 
	str2 = pegaParametro(argc, argv, "-f");
	if (str == NULL){
		printf("Arquivo de entrada não informado\n");
		return 0;
	}
	str = colocaBarra(str);
	str3 = (char*)malloc(sizeof(char)*(strlen(str) + strlen(str2) + 1));
	strcpy(str3, str);
	b = 0;
	for(a = strlen(str); a<(strlen(str) + strlen(str2) -3); a++){
		str3[a] = str2[b];
		b++;
	}
	str3[a] = 's';
	a++;
	str3[a] = 'v';
	a++;
	str3[a] = 'g';
	a++;
	str3[a] = '\0';
	svgMain = fopen(str3, "w");
	fprintf(svgMain, "                                                                  ");
	if (str != NULL)
		free(str);
	str = funcIn(argc, argv, "-f");
	leitura(argc, argv, str, &svgH, &svgW, &svgMain, listCir, listRet, listQua, listSem, listHid, listTor);
	funcFree(&str);
	writeSvg(&svgMain, listCir, listRet, listSem, listQua, listTor, listHid);
	fprintf(svgMain, "</svg>");
	rewind(svgMain);
	svgH += 10.0;
	svgW += 10.0;
	fprintf(svgMain, "<svg width=\"%f\" height=\"%f\">\n", svgW, svgH);
	str = funcIn(argc, argv, "-q");	
	if (str != NULL){
		str4 = funcSvgQry(argc, argv);
		svgQry = fopen(str4, "w");
		funcFree(&str4);
		fprintf(svgQry, "                                                                          ");
		leitura(argc, argv, str, &svgH, &svgW, &svgQry, listCir, listRet, listQua, listSem, listHid, listTor);
		funcFree(&str);
		writeSvg(&svgQry, listCir, listRet, listSem, listQua, listTor, listHid);
		fprintf(svgQry, "</svg>");
		rewind(svgQry);
		svgH += 10.0;
		svgW += 10.0;
		fprintf(svgQry, "<svg width=\"%f\" height=\"%f\">\n", svgW, svgH);
		fclose(svgQry);
	}
	funcFree(&str2);
	funcFree(&str3);
	deleteListComplete(listRet, freeCor);
	deleteListComplete(listCir, freeCirculo);
	deleteListComplete(listTor, freeTorre);
	deleteListComplete(listSem, freeSemaforo);
	deleteListComplete(listQua, freeQuadra);
	deleteListComplete(listHid, freeHidrante);
	fclose(svgMain);
}