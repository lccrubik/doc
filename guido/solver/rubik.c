#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "method.h"
#include "post.h"
#include "metas.h"

#define CANTFASES (sizeof(METAS)/sizeof(int(*)(cubo*)))

cubo* resolver(cubo* C,char* solp)
{
	cubo* Cviejo;
	unsigned int i;

	for(i=0;i<CANTFASES;++i)
	{
		
		Cviejo = C;
		C = IDDFS(C,METAS[i],MOVS[i],solp); /* mi algoritmo anda como el orco */
		free(Cviejo);

		while(*solp != 0) {solp++;}
	}

	return C;
}


int main()
{
	cubo* C;
	char sol[3000];
	
	while(1) {
		C = leerCubo();

		if(C == NULL) return 0;
		
		C = resolver(C,sol);
		simplificar(sol);

		printf("%s\n",sol);
		fflush(stdout);
		free(C);
		C = NULL;
	}
	
	return 0;
}
