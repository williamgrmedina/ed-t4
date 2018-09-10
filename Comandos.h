#ifndef COMANDOS_H
#define COMANDOS_H
#include "Lista.h"

	typedef int (*Equip)(FILE **txt, Item, Item);
	typedef char *((*Object)(Item));

char *funcIn(int argc, char **argv, char *str);
char *concatena(char *str1, char *str2);
void leitura(int argc, char *argv[], char *str, double *svgH, double *svgW, FILE **svgMain, Lista listCir, Lista listRet, Lista listQua, Lista listSem, Lista listHid, Lista listTor);
void funcFree(char **a);
char *colocaBarra(char *str);
char *pegaParametro(int argc, char *argv[], char *str);
void writeSvg(FILE **svg, Lista listCir, Lista listRet, Lista listSem, Lista listQua, Lista listTor, Lista listHid);
char *funcSvgQry(int argc, char **argv);

#endif