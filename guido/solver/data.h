#ifndef ___DATA___
#define ___DATA___

#include <stdio.h>

typedef struct
{
	int F[9];
	int B[9];
	int U[9];
	int D[9];
	int R[9];
	int L[9];
} cubo;

cubo* leerCubo();
void mostrarCuboF(cubo*, FILE*);
void swap2(int*, int*);

void hacerReceta(cubo*, char*); 
void deshacerReceta(cubo*, char*);

typedef void cubeTransformFunc(cubo*); 

cubeTransformFunc girarF, girarf, girarU,
				  giraru, girarD, girard,
				  girarB, girarb, girarL,
				  girarl, girarR, girarr;

int solved(cubo*);
cubo* IDDFS(cubo*,int(*)(cubo*),char**,char*);
cubo* DFS(cubo*,char*,int,int(*)(cubo*),char**);

#endif
