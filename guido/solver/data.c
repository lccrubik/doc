#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

static void left4(int*, int*, int*, int*);
/* ahora es un define: void right4(int*, int*, int*, int*); */


cubo* IDDFS(cubo* C,int (*fit)(cubo*),char** Movs,char* sol)
{
	int i;
	cubo* r;

	for(i=0;;i++)
		if((r=DFS(C,sol,i,fit,Movs)) != NULL)
			return r;

	return NULL;
}

cubo* DFS(cubo* C, char* sol, int max,int (*fit)(cubo*),char** Movs)
{
	cubo* nuevo;
	cubo* r;
	char** nMovs;

	if(max <= 0)
	{
		if((*fit)(C))
		{
			r = (cubo*)malloc(sizeof(cubo));
			*r = *C;

			sol[0] = 0;

			return r;
		} else {
			return NULL;
		}
	} else {
		nuevo = (cubo*)malloc(sizeof(cubo));
		nMovs = Movs;
		*nuevo = *C;

		while(strcmp(*nMovs,"") != 0)
		{
			hacerReceta(nuevo,*nMovs);
			strcpy(sol,*nMovs);
			r = DFS(nuevo,sol+strlen(*nMovs),max-strlen(*nMovs),fit,Movs);

			if(r != NULL)
			{
				free(nuevo);
				return r;
			} else
				*nuevo = *C;

			nMovs++;
		}

		free(nuevo);
		return NULL;
	}
}

/*
void aleatorio(cubo* C)
{
	int i;

	i = rand()%12;

	if(i == 0)
		girarF(C);
	else if(i == 1)
		girarf(C);
	else if(i == 2)
		girarU(C);
	else if(i == 3)
		giraru(C);
	else if(i == 4)
		girarD(C);
	else if(i == 5)
		girard(C);
	else if(i == 6)
		girarR(C);
	else if(i == 7)
		girarr(C);
	else if(i == 8)
		girarL(C);
	else if(i == 9)
		girarl(C);
	else if(i == 10)
		girarB(C);
	else if(i == 11)
		girarb(C);
}
*/

int solved(cubo* C)
{
	int i;

	for(i=0;i<8;++i)
	{
		if(C->U[i] != C->U[8]) return 0;
		if(C->D[i] != C->D[8]) return 0;
		if(C->B[i] != C->B[8]) return 0;
		if(C->F[i] != C->F[8]) return 0;
		if(C->L[i] != C->L[8]) return 0;
		if(C->R[i] != C->R[8]) return 0;
	}

	return 1;
}

void hacerReceta(cubo* C, char* s)
{
	char c;
	while((c = *s++)) /*doble parentesis asi mi compilador no llora*/
	{
		if(c == 'F')
			girarF(C);
		else if(c == 'f')
			girarf(C);
		else if(c == 'U')
			girarU(C);
		else if(c == 'u')
			giraru(C);
		else if(c == 'B')
			girarB(C);
		else if(c == 'b')
			girarb(C);
		else if(c == 'D')
			girarD(C);
		else if(c == 'd')
			girard(C);
		else if(c == 'L')
			girarL(C);
		else if(c == 'l')
			girarl(C);
		else if(c == 'R')
			girarR(C);
		else if(c == 'r')
			girarr(C);
		else
		{
			printf("%i\n",c);
			printf("argumento invalido a hacerreceta\n");
			abort();
		}
	}
}

cubo* leerCubo()
{
	int i,j;
	cubo* C;
	int ret;

	C = (cubo*) malloc(sizeof(cubo));
	ret = 1;

	for(i=0;i<9;++i)
		ret = ret && 0 < scanf("%i",&C->U[i]); /*leo U*/

	for(i=0;i<3;++i)
	{
		for(j=0;j<3;++j)
			ret = ret && 0 < scanf("%i",&C->L[3*i+j]);

		for(j=0;j<3;++j)
			ret = ret && 0 < scanf("%i",&C->F[3*i+j]);

		for(j=0;j<3;++j)
			ret = ret && 0 < scanf("%i",&C->R[3*i+j]);

		for(j=0;j<3;++j)
			ret = ret && 0 < scanf("%i",&C->B[3*i+j]);
	}


	for(i=0;i<9;++i)
		ret = ret && 0 < scanf("%i",&C->D[i]); /*leo D*/

	if(ret)
		return C;
	else {
		free(C);
		return NULL;
	}
}

void mostrarCuboF(cubo* C, FILE* ff)
{
	int i;

	if (C == NULL)
	{
		fprintf(ff, "mostrarCubo recibió argumento nulo\n");
		return;
	}

	for(i=0;i<3;++i)
	{
		fprintf(ff, "      ");
		fprintf(ff, "%i %i %i\n",C->U[3*i+0],C->U[3*i+1],C->U[3*i+2]);
	}

	for(i=0;i<9;i=i+3)
	{
		fprintf(ff, "%i %i %i ",C->L[i+0],C->L[i+1],C->L[i+2]);
		fprintf(ff, "%i %i %i ",C->F[i+0],C->F[i+1],C->F[i+2]);
		fprintf(ff, "%i %i %i ",C->R[i+0],C->R[i+1],C->R[i+2]);
		fprintf(ff, "%i %i %i\n",C->B[i+0],C->B[i+1],C->B[i+2]);
	}

	for(i=0;i<3;++i)
	{
		fprintf(ff, "      ");
		fprintf(ff, "%i %i %i\n",C->D[3*i+0],C->D[3*i+1],C->D[3*i+2]);
	}
}

inline void left4(int* a, int* b, int* c, int* d)
{
	int t;

	t = *a;
	*a = *b;
	*b = *c;
	*c = *d;
	*d = t;
}

/*
inline void right4(int* a, int* b, int* c, int* d)
{
	left4(d,c,b,a);
}
*/
#define right4(a,b,c,d) left4(d,c,b,a)

void girarF(cubo* C)
{
	right4(C->F+0, C->F+2, C->F+8, C->F+6);
	right4(C->F+1, C->F+5, C->F+7, C->F+3);
	right4(C->U+6, C->R+0, C->D+2, C->L+8);
	right4(C->U+7, C->R+3, C->D+1, C->L+5);
	right4(C->U+8, C->R+6, C->D+0, C->L+2);
}

void girarf(cubo* C)
{
	left4(C->F+0, C->F+2, C->F+8, C->F+6);
	left4(C->F+1, C->F+5, C->F+7, C->F+3);
	left4(C->U+6, C->R+0, C->D+2, C->L+8);
	left4(C->U+7, C->R+3, C->D+1, C->L+5);
	left4(C->U+8, C->R+6, C->D+0, C->L+2);
}

void girarU(cubo* C)
{
	right4(C->U+0, C->U+2, C->U+8, C->U+6);
	right4(C->U+1, C->U+5, C->U+7, C->U+3);
	right4(C->B+2, C->R+2, C->F+2, C->L+2);
	right4(C->B+1, C->R+1, C->F+1, C->L+1);
	right4(C->B+0, C->R+0, C->F+0, C->L+0);
}

void giraru(cubo* C)
{
	left4(C->U+0, C->U+2, C->U+8, C->U+6);
	left4(C->U+1, C->U+5, C->U+7, C->U+3);
	left4(C->B+2, C->R+2, C->F+2, C->L+2);
	left4(C->B+1, C->R+1, C->F+1, C->L+1);
	left4(C->B+0, C->R+0, C->F+0, C->L+0);
}

void girarD(cubo* C)
{
	right4(C->D+0, C->D+2, C->D+8, C->D+6);
	right4(C->D+1, C->D+5, C->D+7, C->D+3);
	right4(C->F+6, C->R+6, C->B+6, C->L+6);
	right4(C->F+7, C->R+7, C->B+7, C->L+7);
	right4(C->F+8, C->R+8, C->B+8, C->L+8);
}

void girard(cubo* C)
{
	left4(C->D+0, C->D+2, C->D+8, C->D+6);
	left4(C->D+1, C->D+5, C->D+7, C->D+3);
	left4(C->F+6, C->R+6, C->B+6, C->L+6);
	left4(C->F+7, C->R+7, C->B+7, C->L+7);
	left4(C->F+8, C->R+8, C->B+8, C->L+8);
}

void girarR(cubo* C)
{
	right4(C->R+0, C->R+2, C->R+8, C->R+6);
	right4(C->R+1, C->R+5, C->R+7, C->R+3);
	right4(C->U+8, C->B+0, C->D+8, C->F+8);
	right4(C->U+5, C->B+3, C->D+5, C->F+5);
	right4(C->U+2, C->B+6, C->D+2, C->F+2);
}

void girarr(cubo* C)
{
	left4(C->R+0, C->R+2, C->R+8, C->R+6);
	left4(C->R+1, C->R+5, C->R+7, C->R+3);
	left4(C->U+8, C->B+0, C->D+8, C->F+8);
	left4(C->U+5, C->B+3, C->D+5, C->F+5);
	left4(C->U+2, C->B+6, C->D+2, C->F+2);
}

void girarL(cubo* C)
{
	right4(C->L+0, C->L+2, C->L+8, C->L+6);
	right4(C->L+1, C->L+5, C->L+7, C->L+3);
	right4(C->U+0, C->F+0, C->D+0, C->B+8);
	right4(C->U+3, C->F+3, C->D+3, C->B+5);
	right4(C->U+6, C->F+6, C->D+6, C->B+2);
}

void girarl(cubo* C)
{
	left4(C->L+0, C->L+2, C->L+8, C->L+6);
	left4(C->L+1, C->L+5, C->L+7, C->L+3);
	left4(C->U+0, C->F+0, C->D+0, C->B+8);
	left4(C->U+3, C->F+3, C->D+3, C->B+5);
	left4(C->U+6, C->F+6, C->D+6, C->B+2);
}

void girarB(cubo* C)
{
	right4(C->B+0, C->B+2, C->B+8, C->B+6);
	right4(C->B+1, C->B+5, C->B+7, C->B+3);
	right4(C->U+0, C->L+6, C->D+8, C->R+2);
	right4(C->U+1, C->L+3, C->D+7, C->R+5);
	right4(C->U+2, C->L+0, C->D+6, C->R+8);
}

void girarb(cubo* C)
{
	left4(C->B+0, C->B+2, C->B+8, C->B+6);
	left4(C->B+1, C->B+5, C->B+7, C->B+3);
	left4(C->U+0, C->L+6, C->D+8, C->R+2);
	left4(C->U+1, C->L+3, C->D+7, C->R+5);
	left4(C->U+2, C->L+0, C->D+6, C->R+8);
}

