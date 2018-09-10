#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Comandos.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "CalculoCirculoRetangulo.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Lista.h"
#include "Svg.h"
#include "Vector.h"
#include "Ordenacao.h"
#include "Elemento.h"
#include "Calculo.h"

void funcFree(char **a){
	if (a == NULL){
		printf("ERRO\n");
	} else{
		free(*a);
		*a = NULL;
	}
}

char *colocaBarra(char *str){
	int log = 0;
	char *str2 = NULL, *str3 = NULL;
	if (str == NULL){
		return NULL;
	}
	if (str[strlen(str)-1] != '/'){
		if (str2 != NULL){
			str3 = (char*)malloc(sizeof(char)*(strlen(str2) + 2));
			sprintf(str3, "%s/", str2);
			log = 1;
		} else{
			str3 = (char*)malloc(sizeof(char)*(strlen(str) +2));
			sprintf(str3, "%s/", str);
			log = 1;
		}
	} else {
		str3 = str2;
	}
	if (log == 1){
		free(str);
		return str3;
	} else {
		return str;
	}
}

char *concatena(char *str1, char *str2){
	char *aux;

	if (str1 == NULL){
		if (str2 == NULL){
			return NULL;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str2) + 1));
			strcpy(aux, str2);
			return aux;
		}
	} else{
		if (str2 == NULL){
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + 1));
			strcpy(aux, str1);
			return aux;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + strlen(str2) +1));
			strcpy(aux, str1);
			strcat(aux, str2);
			return aux;
		}
	}
}

char *pegaParametro(int argc, char *argv[], char *str){
	int i, j, k;
	char *ret;
	for (i = 1; i < argc; i++){
		if (strcmp(str, argv[i]) == 0){
			if (strcmp(str, "-f") == 0){
				k=0;
				j=strlen(argv[i+1]) - 1;
				while(j>=0){
					if (argv[i+1][j] == '/')	
						break;
					j--;
					k++;
				}
				ret = (char*)malloc(sizeof(char)*(k + 1));
				ret[k]='\0';
				k--;
				j = strlen(argv[i+1]) - 1;
				while(k>=0){
					if (argv[i+1][j] == '/')
						break;
					ret[k] = argv[i+1][j];
					j--;
					k--;
				}
				return ret;
			} else{
				ret = (char *)malloc(sizeof(char)*(strlen(argv[i + 1]) + 1));
				strcpy(ret, argv[i + 1]);
				return ret;
			}
		}
	}
	return NULL;
}

char *funcTxt(int argc, char **argv){
	int i;
	char *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	aux4 = pegaParametro(argc, argv, "-o");
	aux2 = (char*)malloc(sizeof(char)*(strlen(aux4) + 1));
	strcpy(aux2, aux4);
	funcFree(&aux4);
	aux2 = colocaBarra(aux2);
	aux4 = pegaParametro(argc, argv, "-f");
	aux3 = concatena(aux2, aux4);
	funcFree(&aux4);
	funcFree(&aux2);
	i = strlen(aux3);
	aux3[i - 1] = 't';
	aux3[i - 2] = 'x';
	aux3[i - 3] = 't';
	return aux3;
}

char *funcIn(int argc, char **argv, char *str){
	char *aux3 = NULL, *arqIn = NULL, *aux2 = NULL;
	aux3 = pegaParametro(argc, argv, "-e");
	if (aux3 != NULL){
		aux3 = colocaBarra(aux3);
		aux2 = pegaParametro(argc, argv, str);
		arqIn = concatena(aux3, aux2);
		funcFree(&aux2);
		funcFree(&aux3);
	} else
		arqIn = pegaParametro(argc, argv, str);
	return arqIn;
}

Posic searchObjCep(Lista list, char *cep, Object func){
	int i;
	Posic p1;
	p1 = getFirst(list);
	i = length(list);
	while(i>0){
		if (strcmp(cep, func(getObjt(p1))) == 0){
			return p1;
		}
		p1 = getNext(p1);
		i--;
	}
	return NULL;
}

Posic searchObjId(Lista listCir, Lista listRet, int id){
	Posic p1 = NULL;
	int var;
	Retangulo r1 = NULL;
	Circulo c1 = NULL;
	p1 = getFirst(listRet);
	r1 = getObjt(p1);
	var = (int)length(listRet);
	while(var>0){
		if (getRetanguloId(r1) == id){
			return p1;
		}
		p1 = getNext(p1);
		if (p1 != NULL)
			r1 = getObjt(p1);
		var--;
	}
	p1 = getFirst(listCir);
	c1 = getObjt(p1);
	var = length(listCir);
	while(var>0){
		if (getCirculoId(c1) == id){
			return p1;
		}
		p1 = getNext(p1);
		if (p1 != NULL)
			c1 = getObjt(p1);
		var--;
	}
	return NULL;
}

int typeObj(Lista listCir, Lista listRet, int id){
	Posic p1 = NULL;
	int var;
	Retangulo r1 = NULL;
	Circulo c1 = NULL;
	p1 = getFirst(listRet);
	r1 = getObjt(p1);
	var = (int)length(listRet);
	while(var>0){
		if (getRetanguloId(r1) == id){
			return 0;
		}
		p1 = getNext(p1);
		if (p1 != NULL)
			r1 = getObjt(p1);
		var--;
	}
	p1 = getFirst(listCir);
	c1 = getObjt(p1);
	var = length(listCir);
	while(var>0){
		if (getCirculoId(c1) == id){
			return 1;
		}
		p1 = getNext(p1);
		if (p1 != NULL)
			c1 = getObjt(p1);
		var--;
	}
	return -1;
}

double distanciaCdm(Lista listCir, Lista listRet, int i, int j){
	Posic p1 = NULL, p2 = NULL;
	int tipo1, tipo2;
	double value;
	Retangulo r1 = NULL, r2 = NULL;
	Circulo c1 = NULL, c2 = NULL;
	p1 = (Posic)searchObjId(listCir, listRet, i);
	if (p1 == NULL)
		p1 = searchObjId(listCir, listRet, i);
	p2 = searchObjId(listCir, listRet, j);
	if (p2 == NULL)
		p2 = searchObjId(listCir, listRet, j);
	tipo1 = typeObj(listCir, listRet, i);
	tipo2 = typeObj(listCir, listRet, j);
	if (tipo1 == 0){
		if (tipo2 == 0){
			r1 = (Retangulo)getObjt(p1);
			r2 = (Retangulo)getObjt(p2);
			value = dcmRetanguloRetangulo(r1, r2);
		} else{
			r1 = (Retangulo)getObjt(p1);
			c1 = (Circulo)getObjt(p2);
			value = dcmCirculoRetangulo(c1, r1);
		}
	} else{
		if (tipo2 == 0){
			c1 = (Circulo)getObjt(p1);
			r1 = (Retangulo)getObjt(p2);
			value = dcmCirculoRetangulo(c1, r1);
		} else{
			c1 = (Circulo)getObjt(p1);
			c2 = (Circulo)getObjt(p2);
			value = dcmCirculoCirculo(c1, c2);
		}
	}
	return value;
}

char *funcSvg(int argc, char **argv, char *str){
	int i;
	char *aux = NULL, *strdir = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	aux3 = pegaParametro(argc, argv, "-o");
	aux4 = pegaParametro(argc, argv, "-f");
	aux2 = (char*)malloc(sizeof(char)*(strlen(aux4)));
	strdir = (char*)malloc(sizeof(char)*(strlen(aux3) + 1));
	strcpy(strdir, aux3);
	strdir = colocaBarra(strdir);
	aux = (char*)malloc(sizeof(char)*(strlen(aux4) + strlen(str) + strlen(strdir) + 2));
	strcpy(aux, strdir);
	funcFree(&strdir);
	for (i = 0; i<(strlen(aux4) - 4); i++){
			aux2[i] = aux4[i];
	}
	aux2[i] = '\0';
	strcat(aux, aux2);
	funcFree(&aux3);
	funcFree(&aux4);
	funcFree(&strdir);
	funcFree(&aux2);
	strcat(aux, "-");
	strcat(aux, str);
	strcat(aux, ".svg");
	return aux;
}

int countQry(char *str){
	int a, ret = 0;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] != '/')
			ret++;
		else
			break;
	}
	return ret;
}

int barraQry(char *str){
	int a, ret= -1;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] == '/'){
			ret = a;
			break;
		}
	}
	return ret;
}

char *funcSvgQry(int argc, char **argv){
	char *aux, *qry, *str;
	int a, b;
	qry = pegaParametro(argc, argv, "-q");
	aux = (char*)malloc(sizeof(char)*(countQry(qry) -3));
	b = barraQry(qry);
	if (b != -1)
		b += 1;
	else
		b = 0;
	for (a = 0; a<countQry(qry); a++){
		if (qry[b] == '.')
			break;
		aux[a] = qry[b];
		b++;
	}
	funcFree(&qry);
	aux[a] = '\0';
	str = funcSvg(argc, argv, aux);
	funcFree(&aux);
	return str;
}

void writeSvg(FILE **svg, Lista listCir, Lista listRet, Lista listSem, Lista listQua, Lista listTor, Lista listHid){
	printSvgList(&(*svg), listCir, printSvgCirculo);
	printSvgList(&(*svg), listRet, printSvgRetangulo);
	printSvgList(&(*svg), listQua, printSvgQuadra);
	printSvgList(&(*svg), listTor, printSvgTorre);
	printSvgList(&(*svg), listSem, printSvgSemaforo);
	printSvgList(&(*svg), listHid, printSvgHidrante);
}

void cmpRet(Retangulo r1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getRetanguloX(r1);
	if (*yme < 0)
		*yme = getRetanguloY(r1);
	if (getRetanguloX(r1) < *xme)
		*xme = getRetanguloX(r1);
	if (getRetanguloY(r1) < *yme)
		*yme = getRetanguloY(r1);
	if ((getRetanguloX(r1) + getRetanguloWidth(r1)) > *xma)
		*xma = getRetanguloX(r1) + getRetanguloWidth(r1);
	if ((getRetanguloY(r1) + getRetanguloHeight(r1)) > *yma)
		*yma = getRetanguloY(r1) + getRetanguloHeight(r1);
}

void cmpCir(Circulo c1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getCirculoX(c1) - getCirculoRaio(c1);
	if (*yme < 0)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) - getCirculoRaio(c1)) < *xme)
		*xme = (getCirculoX(c1) - getCirculoRaio(c1));
	if ((getCirculoY(c1) - getCirculoRaio(c1)) < *yme)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) + getCirculoRaio(c1)) > *xma)
		*xma = getCirculoX(c1) + getCirculoRaio(c1);
	if ((getCirculoY(c1) + getCirculoRaio(c1)) > *yma)
		*yma = getCirculoY(c1) + getCirculoRaio(c1);
}
/* se o elemento de id id estiver na lista, retorno = 1, se não, retorno = 0*/

void removeListCirLeak(Lista listCir){
	Posic p1 = NULL;
	Circulo c1 = NULL;
	char *str = NULL;
	int var;
	p1 = getFirst(listCir);
	c1 = getObjt(p1);
	var = length(listCir);
	while(var > 0){
		str = getCirculoCorPreenchimento(c1);
		funcFree(&str);
		str = getCirculoCorContorno(c1);
		funcFree(&str);
		var--;
	}

}

void consultaQ(FILE *txt, Item item, Lista list, Equip func){
	Posic p1;
	int i;
	p1 = getFirst(list);
	i = length(list);
	while(i>0){
		func(&txt, getObjt(p1), item);
		i--;
		p1 = getNext(p1);
	}
}

int cmpQuadra(Quadra q1, double x, double y, double width, double height){
	if (getQuadraX(q1) == x){
		if (getQuadraY(q1) == y){
			if (getQuadraWidth(q1) == width){
				if (getQuadraHeight(q1) == height)
					return 1;
			}
		}
	}
	return 0;
}

void svgCmpCirculo(double *svgH, double *svgW, double x, double y, double raio){
	if ((x+raio) > *svgW)
		*svgW = x+raio;
	if ((y+raio) > *svgH)
		*svgH = y+raio;
}

void svgCmpRetangulo(double *svgH, double *svgW, double x, double y, double height, double width){
	if ((x + width) > *svgW)
		*svgW = x + width;
	if ((y+height) > *svgH)
		*svgH = y + height;
}

void leitura(int argc, char *argv[], char *arqIn, double *svgH, double *svgW, FILE **svgMain, Lista listCir, Lista listRet, Lista listQua, Lista listSem, Lista listHid, Lista listTor){
	Posic p1 = NULL, p2 = NULL;
	FILE *entrada = NULL, *txt = NULL, *svg = NULL, *lixo = NULL;
	Circulo c1 = NULL, c2 = NULL;
	Retangulo r1 = NULL, r2 = NULL;
	Quadra q1 = NULL;
	Semaforo s1 = NULL;
	Torre t1 = NULL;
	Hidrante h1 = NULL;
	char *line = NULL, *word = NULL, *cor1 = NULL, *cor2 = NULL, 
	*aux = NULL, *aux2 = NULL, *aux3 = NULL, *suf = NULL, *cep = NULL,
	*corQP = NULL, *corQC = NULL, *corHP = NULL, *corHC = NULL, *corTP = NULL, *corTC = NULL, *corSP = NULL, *corSC = NULL,
	*tipo = NULL;
	int i, j, var, tipo1, tipo2, id1, id2;
	double raio, x, y, height, width, value, xme, yme, xma, yma;
	tipo = (char*)malloc(sizeof(char)*2);
	cep = (char*)malloc(sizeof(char)*20);
	line = (char*)malloc(sizeof(char)*200);
	word =(char*)malloc(sizeof(char)*30);
	cor1 = (char*)malloc(sizeof(char)*20);
	cor2 = (char*)malloc(sizeof(char)*20);
	suf = (char*)malloc(sizeof(char)*40);
	corQP = (char*)malloc(sizeof(char)*20);
	corQC = (char*)malloc(sizeof(char)*20);
	corHP = (char*)malloc(sizeof(char)*20);
	corHC = (char*)malloc(sizeof(char)*20);
	corSP = (char*)malloc(sizeof(char)*20);
	corSC = (char*)malloc(sizeof(char)*20);
	corTP = (char*)malloc(sizeof(char)*20);
	corTC = (char*)malloc(sizeof(char)*20);
	entrada = fopen(arqIn, "r");
	while(!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "c") == 0){
			sscanf(line, "%s %d %s %s %lf %lf %lf", word, &i, cor1, cor2, &raio, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			c1 = creatCirculo(i, raio, x, y, aux2, aux);
			insert(listCir, (Item)c1);
			if ((getCirculoX(c1) + getCirculoRaio(c1)) > *svgW){
				*svgW = getCirculoX(c1) + getCirculoRaio(c1);
			}
			if ((getCirculoY(c1) + getCirculoRaio(c1)) > *svgH){
				*svgH = getCirculoY(c1) + getCirculoRaio(c1);
			}
		} else if (strcmp(word, "r") == 0){
			sscanf(line, "%s %d %s %s %lf %lf %lf %lf", word, &i, cor1, cor2, &width, &height, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			r1 = creatRetangulo(i, width, height, x, y, aux2, aux);
			insert(listRet, (Item)r1);
			if ((getRetanguloX(r1) + getRetanguloWidth(r1)) > *svgW){
				*svgW = getRetanguloX(r1) + getRetanguloWidth(r1);
			}
			if ((getRetanguloY(r1) + getRetanguloHeight(r1)) > *svgH){
				*svgH = getRetanguloY(r1) + getRetanguloHeight(r1);
			}
		}else if(strcmp(word, "cq") == 0){
			sscanf(line, "%s %s %s", word, corQC, corQP);
		}else if(strcmp(word, "ct") == 0){
			sscanf(line, "%s %s %s", word, corTC, corTP);
		}else if(strcmp(word, "ch") == 0){
			sscanf(line, "%s %s %s", word, corHC, corHP);
		}else if(strcmp(word, "cs") == 0){
			sscanf(line, "%s %s %s", word, corSC, corSP);
		}else if(strcmp(word, "q") == 0){
			sscanf(line, "%s %s %lf %lf %lf %lf", word, cep, &x, &y, &width, &height);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cep);
			q1 = (Quadra)createQuadra(x, y, width, height, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corQP) + 1));
			strcpy(aux, corQP);
			setQuadraCorPreenchimento(q1, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corQC) + 1));
			strcpy(aux, corQC);
			setQuadraCorContorno(q1, aux);
			insert(listQua, (Item)q1);
			if ((x + width) > *svgW)
				*svgW = x + width;
			if ((y + height) > *svgH)
				*svgH = y + height;
		}else if(strcmp(word, "s") == 0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cep);
			s1 = createSemaforo(x, y, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corSP) + 1));
			strcpy(aux, corSP);
			setSemaforoCorPreenchimento(s1, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corSC) + 1));
			strcpy(aux, corSC);
			setSemaforoCorContorno(s1, aux);
			insert(listSem, (Item)s1);
			if (x > *svgW)
				*svgW = x;
			if (y > *svgH)
				*svgH = y;
		}else if(strcmp(word, "t") == 0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cep);
			t1 = createTorre(x, y, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corTP) + 1));
			strcpy(aux, corTP);
			setTorreCorPreenchimento(t1, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corTC) + 1));
			strcpy(aux, corTC);
			setTorreCorContorno(t1, aux);
			insert(listTor, (Item)t1);
			if (x > *svgW)
				*svgW = x;
			if (y > *svgH)
				*svgH = y;
		}else if(strcmp(word, "h") == 0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cep);
			h1 = createHidrante(x, y, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corHP) + 1));
			strcpy(aux, corHP);
			setHidranteCorPreenchimento(h1, aux);
			aux = (char*)malloc(sizeof(char)*(strlen(corHC) + 1));
			strcpy(aux, corHC);
			setHidranteCorContorno(h1, aux);
			insert(listHid, (Item)h1);
			if (x > *svgW)
				*svgW = x;
			if (y > *svgH)
				*svgH = y;
		} else if (strcmp(word, "i") == 0){
			sscanf(line, "%s %d %lf %lf", word, &j, &x, &y);
			p1 = searchObjId(listCir, listRet, j);
			i = typeObj(listCir, listRet, j);
			if (i == 0){
				r1 = (Retangulo)getObjt(p1);
				if (r1 != NULL)
					var = pontoInternoRetangulo(r1, x, y);
				else
					var = -1;
			} else{
				c1 = (Circulo)getObjt(p1);
				if (c1 != NULL)
					var = pontoInternoCirculo(c1, x, y);
				else
					var = -1;
			}
			aux = funcTxt(argc, argv);
			if (txt == NULL){
				txt = fopen(aux, "w");
			}
			funcFree(&aux);
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
			} else{
				fprintf(txt, "%s\nSIM\n", line);
			}
		} else if (strcmp(word, "o") == 0){
			xma = 0.0;
			yma = 0.0;
			xme = -1.0;
			yme = -1.0;
			sscanf(line, "%s %d %d", word, &i, &j);
			p1 = searchObjId(listCir, listRet, i);
			if (p1 == NULL)
				p1 = searchObjId(listCir, listRet, i);
			tipo1 = typeObj(listCir, listRet, i);
			p2 = searchObjId(listCir, listRet, j);
			if (p2 == NULL)
				p2 = searchObjId(listCir, listRet, j);
			tipo2 = typeObj(listCir, listRet, j);
			//printf("t1: %d t2: %d\n", tipo1, tipo2);
			if (tipo1 == 0){
				if (tipo2 == 0){
					r1 = (Retangulo)getObjt(p1);
					r2 = (Retangulo)getObjt(p2);
					var = sobreposicaoRetanguloRetangulo(r1, r2);
					if (var == 1){
						cmpRet(r1, &xma, &xme, &yma, &yme);
						cmpRet(r2, &xma, &xme, &yma, &yme);
					}
				} else{
					r1 = (Retangulo)getObjt(p1);
					c1 = (Circulo)getObjt(p2);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					if (var == 1){
						cmpRet(r1, &xma, &xme, &yma, &yme);
						cmpCir(c1, &xma, &xme, &yma, &yme);
					}
				}
			} else{
				if (tipo2 == 0){
					r1 = (Retangulo)getObjt(p2);
					c1 = (Circulo)getObjt(p1);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					if (var == 1){
						cmpRet(r1, &xma, &xme, &yma, &yme);
						cmpCir(c1, &xma, &xme, &yma, &yme);
					}
				} else{
					c1 = (Circulo)getObjt(p1);
					c2 = (Circulo)getObjt(p2);
					var  = sobreposicaoCirculoCirculo(c1, c2);
					if (var == 1){
						cmpCir(c1, &xma, &xme, &yma, &yme);
						cmpCir(c2, &xma, &xme, &yma, &yme);
					}
				}
			}
			aux = funcTxt(argc, argv);
			if (txt == NULL){
				txt = fopen(aux, "w");
			}
			funcFree(&aux);
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
			} else{
				fprintf(txt, "%s\nSIM\n", line);
				fprintf(*svgMain, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" stroke=\"purple\" stroke-width=\"4\" fill-opacity = \"0.000\" stroke-dasharray = \"5,10,2\"/>\n", xme, yme, (xma - xme), (yma - yme));				
			}
			if ((xme + (xma -xme)) > *svgW)
				*svgH = xme + (xma -xme);
			if ((yme + (yma - yme)) > *svgH)
				*svgH = yme + (yma - yme);
		} else if (strcmp(word, "d") == 0){
			sscanf(line, "%s %d %d", word, &i, &j);
			value = distanciaCdm(listCir, listRet, i, j);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "w");
				funcFree(&aux);
			}
			fprintf(txt, "%s\n%.10f\n", line, value);
		} else if (strcmp(word, "nx") == 0){
			sscanf(line, "%s %d", word, &i);
		}else if (strcmp(word, "a") == 0){
			sscanf(line, "%s %d %s", word, &i, suf);
			aux = funcSvg(argc, argv, suf);
			svg = fopen(aux, "w");
			funcFree(&aux);
			fprintf(svg, "<svg height = \"%f\" width = \"%f\">\n", *svgH, *svgW);
			tipo1 = typeObj(listCir, listRet, i);
			if (tipo1 == 0){
				p1 = searchObjId(listCir, listRet, i);
				r1 = getObjt(p1);
				printSvgRetangulo(&svg, r1);
				id1 = getRetanguloId(r1);
				j = length(listRet);
				if (j>0){
					p1 = getFirst(listRet);
					while(j>0){
						r2 = getObjt(p1);
						if (getRetanguloId(r2) != getRetanguloId(r1)){
							printSvgRetangulo(&svg, r2);
							printSvgLine(&svg, (getRetanguloX(r1)+getRetanguloWidth(r1)/2), (getRetanguloY(r1)+getRetanguloHeight(r1)/2), (getRetanguloX(r2)+getRetanguloWidth(r2)/2), (getRetanguloY(r2)+getRetanguloHeight(r2)/2));
						}
						p1 = getNext(p1);
						j--;
					}
					j = length(listCir);
					p1 = getFirst(listCir);
					while(j>0){
						c2 = getObjt(p1);
						printSvgCirculo(&svg, c2);
						printSvgLine(&svg, getCirculoX(c2), getCirculoY(c2), (getRetanguloX(r1)+getRetanguloWidth(r1)/2), (getRetanguloY(r1)+getRetanguloHeight(r1)/2));
						p1 = getNext(p1);
						j--;
					}
				}
			} else if (tipo1 == 1){
				p1 = searchObjId(listCir, listRet, i);
				c1 = getObjt(p1);
				id1 = getCirculoId(c1);
				printSvgCirculo(&svg, c1);
				j = length(listCir);
				if (j>0){
					p1 = getFirst(listCir);
					while(j>0){
						c2 = getObjt(p1);
						if (getCirculoId(c1) != getCirculoId(c2)){
							printSvgCirculo(&svg, c2);
							printSvgLine(&svg, getCirculoX(c2), getCirculoY(c2), getCirculoX(c1), getCirculoY(c1));
						}
						p1 = getNext(p1);
						j--;
					}
					p1 = getFirst(listRet);
					j = length(listRet);
					while(j>0){
						r2 = (Retangulo)getObjt(p1);
						printSvgRetangulo(&svg, r2);
						printSvgLine(&svg, getCirculoX(c1), getCirculoY(c1), (getRetanguloX(r2)+getRetanguloWidth(r2)/2), (getRetanguloY(r2)+getRetanguloHeight(r2)/2));
						p1 = getNext(p1);
						j--;
					}
				}
			}
			if (tipo1 != -1){
				fprintf(svg, "</svg>");
			}else
				printf("ERRO\n");
			fclose(svg);
		}else if (strcmp(word, "#") == 0){
			break;
		}else if (strcmp(word, "q?") == 0){
			sscanf(line, "%s %lf %lf %lf %lf", word, &x, &y, &width, &height);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			r1 = creatRetangulo(0, width, height, x, y, NULL, NULL);
			consultaQ(txt, (Item)r1, listQua, quadraInternaRetangulo);
			consultaQ(txt, (Item)r1, listHid, hidranteInternoRetangulo);
			consultaQ(txt, (Item)r1, listTor, torreInternaRetangulo);
			consultaQ(txt, (Item)r1, listSem, semaforoInternoRetangulo);
			fprintf(*svgMain, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"gray\" stroke=\"red\" stroke-width=\"3\" fill-opacity = \"0.0\" stroke-dasharray = \"5,5,5\"/>\n", x, y, width, height);
			svgCmpRetangulo(svgH, svgW, getRetanguloX(r1), getRetanguloY(r1), getRetanguloHeight(r1), getRetanguloWidth(r1));
			free(r1);
		} else if (strcmp(word, "Q?") == 0){
			sscanf(line, "%s %lf %lf %lf", word, &raio, &x, &y);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			c1 = creatCirculo(0, raio, x, y, NULL, NULL);
			consultaQ(txt, (Item)c1, listQua, quadraInternaCirculo);
			consultaQ(txt, (Item)c1, listTor, torreInternaCirculo);
			consultaQ(txt, (Item)c1, listHid, hidranteInternoCirculo);
			consultaQ(txt, (Item)c1, listSem, semaforoInternoCirculo);
			fprintf(*svgMain, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"gray\" stroke=\"red\" stroke-width=\"3\" fill-opacity = \"0.0\" stroke-dasharray = \"5,5,5\"/>\n", x, y, raio);
			svgCmpCirculo(svgH, svgW, getCirculoX(c1), getCirculoY(c1), getCirculoRaio(c1));

			free(c1);
		} else if (strcmp(word, "dq") == 0){
			sscanf(line, "%s %lf %lf %lf %lf", word, &x, &y, &width, &height);
			if (length(listQua) > 0){
				if (txt == NULL){
					aux = funcTxt(argc, argv);
					txt = fopen(aux, "a");
					funcFree(&aux);
				}
				aux = (char*)malloc(sizeof(char)*6);
				aux2 = (char*)malloc(sizeof(char)*7);
				strcpy(aux, "green");
				strcpy(aux2, "yellow");
				r1  = creatRetangulo(0, width, height, x, y, aux, aux2);
				p1 = getFirst(listQua);
				q1 = (Quadra)getObjt(p1);
				i = length(listQua);
				while(i>0){
					var = cmpQuadra(q1, x, y, width, height);
					if (var == 1){
						fprintf(txt, "%s\n", getQuadraCep(q1));
						freeQuadra(q1);
						p2 = getNext(p1);
						remover(listQua, p1);
					} else
						p2 = getNext(p1);
					p1 = p2;
					if (p1 != NULL)
						q1 = getObjt(p1);
					else
						break;
					i--;
				}
				printSvgRetangulo(svgMain, r1);
				svgCmpRetangulo(svgH, svgW, getRetanguloX(r1), getRetanguloY(r1), getRetanguloHeight(r1), getRetanguloWidth(r1));
				funcFree(&aux);
				funcFree(&aux2);
				if (r1 != NULL)
					free(r1);
			}
		} else if (strcmp(word, "dle") == 0){
			sscanf(line, "%s %s %lf %lf %lf %lf", word, tipo, &x, &y, &width, &height);
			aux = (char*)malloc(sizeof(char)*6);
			aux2 = (char*)malloc(sizeof(char)*7);
			strcpy(aux, "green");
			strcpy(aux2, "yellow");
			r1  = creatRetangulo(0, width, height, x, y, aux, aux2);
			if (txt == NULL){
				aux3 = funcTxt(argc, argv);
				txt = fopen(aux3, "a");
				funcFree(&aux3);
			}
			if (strcmp(tipo, "t") == 0){
				p1 = getFirst(listTor);
				t1 = getObjt(p1);
				i = length(listTor);
				
				while(i>0){
					var = torreInternaRetangulo(&lixo, t1, r1);
					if (var == 1){
						fprintf(txt, "%s\n", getTorreId(t1));
						freeTorre(t1);
						p2 = getNext(p1);
						remover(listTor, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						t1 = getObjt(p1);
					i--;
				}
			} else if (strcmp(tipo, "s") == 0){
				p1 = getFirst(listSem);
				s1 = getObjt(p1);
				i = length(listSem);
				while(i>0){
					var = semaforoInternoRetangulo(&lixo, s1, r1);
					if (var == 1){
						fprintf(txt, "%s\n", getSemaforoId(s1));
						freeSemaforo(s1);
						p2 = getNext(p1);
						remover(listSem, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						s1 = getObjt(p1);
					i--;
				}
			} else if(strcmp(word, "h") == 0){
				p1 = getFirst(listHid);
				h1 = getObjt(p1);
				i = length(listHid);
				while(i>0){
					var = hidranteInternoRetangulo(&lixo, h1, r1);
					if (var == 1){
						fprintf(txt, "%s\n", getHidranteId(h1));
						freeHidrante(h1);
						p2 = getNext(p1);
						remover(listHid, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						h1 = getObjt(p1);
					i--;
				}
			}
			//printSvgRetangulo(svgMain, r1);
			funcFree(&aux);
			funcFree(&aux2);
			if (r1 != NULL)
				free(r1);
		} else if (strcmp(word, "Dq") == 0){
			sscanf(line, "%s %lf %lf %lf", word, &raio, &x, &y);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			aux = (char*)malloc(sizeof(char)*6);
			aux2 = (char*)malloc(sizeof(char)*7);
			strcpy(aux, "green");
			strcpy(aux2, "yellow");
			c1  = creatCirculo(0, raio, x, y, aux, aux2);
			p1 = getFirst(listQua);
			q1 = (Quadra)getObjt(p1);
			i = length(listQua);
			while(i>0){
				var = quadraInternaCirculo(&lixo, q1, c1);
				if (var == 1){
					fprintf(txt, "%s\n", getQuadraCep(q1));
					freeQuadra(q1);
					p2 = getNext(p1);
					remover(listQua, p1);
				} else
					p2 = getNext(p1);
				p1 = p2;
				if (p1 != NULL)
					q1 = getObjt(p1);
				else
					break;
				i--;
			}
			printSvgCirculo(svgMain, c1);
			svgCmpCirculo(svgH, svgW, getCirculoX(c1), getCirculoY(c1), getCirculoRaio(c1));
			freeCirculo(c1);
			if (c1 != NULL)
				free(c1);
		} else if (strcmp(word, "Dle") == 0){
			sscanf(line, "%s %s %lf %lf %lf", word, tipo, &x, &y, &raio);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			c1  = creatCirculo(0, raio, x, y, NULL, NULL);
			if (strcmp(tipo, "t") == 0){
				p1 = getFirst(listTor);
				t1 = getObjt(p1);
				i = length(listTor);
				while(i>0){
					var = torreInternaCirculo(&lixo, t1, c1);
					if (var == 1){
						fprintf(txt, "%s\n", getTorreId(t1));
						freeTorre(t1);
						p2 = getNext(p1);
						remover(listTor, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						t1 = getObjt(p1);
					i--;
				}
			} else if (strcmp(tipo, "s") == 0){
				p1 = getFirst(listSem);
				s1 = getObjt(p1);
				i = length(listSem);
				while(i>0){
					var = semaforoInternoCirculo(&lixo, s1, c1);
					if (var == 1){
						fprintf(txt, "%s\n", getSemaforoId(s1));
						freeSemaforo(s1);
						p2 = getNext(p1);
						remover(listSem, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						s1 = getObjt(p1);
					i--;
				}
			} else if(strcmp(word, "h") == 0){
				p1 = getFirst(listHid);
				h1 = getObjt(p1);
				i = length(listHid);
				while(i>0){
					var = hidranteInternoCirculo(&lixo, h1, c1);
					if (var == 1){
						fprintf(txt, "%s\n", getHidranteId(h1));
						freeHidrante(h1);
						p2 = getNext(p1);
						remover(listHid, p1);
						p1 = p2;
					}else
						p1 = getNext(p1);
					if (p1 != NULL)
						h1 = getObjt(p1);
					i--;
				}
			}
			if (c1 != NULL)
				free(c1);
		} else if (strcmp(word, "cc") == 0){
			sscanf(line, "%s %s %s %s", word, cep, cor1, cor2);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			p1 = searchObjCep(listQua, cep, getQuadraCep);
			if (p1 == NULL){
				p1 = searchObjCep(listTor, cep, getTorreId);
				if (p1 == NULL){
					p1 = searchObjCep(listHid, cep, getHidranteId);
					if (p1 == NULL){
						p1 = searchObjCep(listSem, cep, getSemaforoId);
						if (p1 != NULL){
							s1 = (Semaforo)getObjt(p1);
							setSemaforoCorContorno(s1, aux);
							setSemaforoCorPreenchimento(s1, aux2);
							//printf("Sem -> c1: %s c2: %s\n", getSemaforoCorPreenchimento(s1), getSemaforoCorContorno(s1));
						}
					}else{
						h1 = (Hidrante)getObjt(p1);
						setHidranteCorContorno(h1, aux);
						setHidranteCorPreenchimento(h1, aux2);
						//printf("Hidrante -> c1: %s c2: %s\n", getHidranteCorPreenchimento(h1), getHidranteCorContorno(h1));
					}
				} else{
					t1 = (Torre)getObjt(p1);
					setTorreCorPreenchimento(t1, aux2);
					setTorreCorContorno(t1, aux);
					//printf("Torre -> c1: %s c2: %s\n", getTorreCorPreenchimento(t1), getTorreCorContorno(t1));
				}
			} else{
				q1 = (Quadra)getObjt(p1);
				setQuadraCorContorno(q1, aux);
				setQuadraCorPreenchimento(q1, aux2);
				//printf("Quadra -> c1: %s c2: %s\n", getQuadraCorPreenchimento(q1), getQuadraCorContorno(q1));
			}
		}else if (strcmp(word, "crd?") == 0){
			sscanf(line, "%s %s", word, cep);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			p1 = searchObjCep(listQua, cep, getQuadraCep);
			if (p1 == NULL){
				p1 = searchObjCep(listTor, cep, getTorreId);
				if (p1 == NULL){
					p1 = searchObjCep(listHid, cep, getHidranteId);
					if (p1 == NULL){
						p1 = searchObjCep(listSem, cep, getSemaforoId);
						if (p1 != NULL){
							s1 = (Semaforo)getObjt(p1);
							fprintf(txt, "Semaforo %lf %lf\n", getSemaforoX(s1), getSemaforoY(s1));
						}
					}else{
						h1 = (Hidrante)getObjt(p1);
						fprintf(txt, "Hidrante %lf %lf\n", getHidranteX(h1), getHidranteY(h1));
					}
				} else{
					t1 = (Torre)getObjt(p1);
					fprintf(txt, "Torre %lf %lf\n", getTorreX(t1), getTorreY(t1));
				}
			} else{
				q1 = (Quadra)getObjt(p1);
				fprintf(txt, "Quadra %lf %lf\n", getQuadraX(q1), getQuadraY(q1));
			}
		}else if (strcmp(word, "crb?") == 0){
			Vector vetor;
			Elemento e1 = NULL, e2 = NULL;
			aux = NULL;
			Posic p;
			Elemento e;
			vetor = ltov(listTor, getTorreX, getTorreY, getTorreId);
			heapSort(vetor, cmp, 'x');
			value = lessDistance(vetor, 1, getSizeVector(vetor), &e1, &e2);
			fprintf(*svgMain, "<circle cx = \"%f\" cy = \"%f\" r = \"120\" fill = \"gray\" stroke=\"red\" stroke-width=\"15\" fill-opacity = \"0.0\" />\n", getElementoX(e1), getElementoY(e1));
			fprintf(*svgMain, "<circle cx = \"%f\" cy = \"%f\" r = \"120\" fill = \"gray\" stroke=\"red\" stroke-width=\"15\" fill-opacity = \"0.0\" />\n", getElementoX(e2), getElementoY(e2));
			freeVector(vetor, freeElemento);
		}
	}
	funcFree(&line);
	funcFree(&word);
	funcFree(&cor1);
	funcFree(&cor2);
	funcFree(&suf);
	funcFree(&corHP);
	funcFree(&corHC);
	funcFree(&corSP);
	funcFree(&corSC);
	funcFree(&corTP);
	funcFree(&corTC);
	funcFree(&corQC);
	funcFree(&corQP);
	funcFree(&cep);
	funcFree(&tipo);
	fclose(entrada);
	if (txt != NULL)
		fclose(txt);
}	