#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

static struct timeval t_start;
static struct timeval t_end;
static int clock_running = 0;

void start_clock() {
		assert(clock_running == 0);
		gettimeofday(&t_start, NULL);
		clock_running=1;
}

void stop_clock() {
		assert(clock_running == 1);
		gettimeofday(&t_end, NULL);
		clock_running=0;
}

long get_clock() {
	assert(clock_running == 0);

	return (long)((t_end.tv_usec - t_start.tv_usec) + 1000000*(t_end.tv_sec - t_start.tv_sec));
}

int start_proc(char *file, int fd[2]) {
	int pc[2], cp[2];
	int cpid;

	pipe(pc); pipe(cp);

	if((cpid=fork()) < 0) {
		perror("fork");
		abort();
	} else if (cpid == 0) {
		close(cp[0]);
		close(pc[1]);

		close(0);
		dup(pc[0]);
		close(pc[0]);

		close(1);
		dup(cp[1]);
		close(cp[1]);

		execl(file, file, (char *)NULL);
		perror("execl");
		abort();
	} else { /* parent */
		close(cp[1]);
		close(pc[0]);
		fd[0] = cp[0];
		fd[1] = pc[1];

		return 1; 
	}
}

int readline(int fd, void *buf, int n)
{
    int nr = 0;
    int t;

    while((t = read(fd, (char*)buf+nr, 1)) > 0) {
		if (((char*)buf)[nr] == '\n') {
			((char*)buf)[nr+1] = 0;
			return 0;
		}

		nr+=t;
	}

	return 1;
}

int writen(int fd, void *buf, int n)
{
    int nw = 0;
    int t;

    while(nw < n && (t = write(fd, (char*)buf+nw, n-nw)) > 0)
        nw+=t;

    return nw;
}

typedef struct
{
	int F[9];
	int B[9];
	int U[9];
	int D[9];
	int R[9];
	int L[9];
} cubo;

void left4(int* a, int* b, int* c, int* d)
{
	int t;
	
	t = *a;
	*a = *b;
	*b = *c;
	*c = *d;
	*d = t;
}

void right4(int* a, int* b, int* c, int* d)
{
	left4(d,c,b,a);
}

void swap2(int* a, int* b)
{
	int t;
	
	t = *a;
	*a = *b;
	*b = t;
}

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

void mostrarCubo(cubo* C)
{
	int i;
	
	if (C == NULL)
	{
		printf("mostrarCubo recibió argumento nulo\n");
		return;
	}
	
	for(i=0;i<3;++i)
	{
		printf("      ");
		printf("%i %i %i\n",C->U[3*i+0],C->U[3*i+1],C->U[3*i+2]);
	}
	
	for(i=0;i<9;i=i+3)
	{
		printf("%i %i %i ",C->L[i+0],C->L[i+1],C->L[i+2]);
		printf("%i %i %i ",C->F[i+0],C->F[i+1],C->F[i+2]);
		printf("%i %i %i ",C->R[i+0],C->R[i+1],C->R[i+2]);
		printf("%i %i %i\n",C->B[i+0],C->B[i+1],C->B[i+2]);
	}
	
	for(i=0;i<3;++i)
	{
		printf("      ");
		printf("%i %i %i\n",C->D[3*i+0],C->D[3*i+1],C->D[3*i+2]);
	}
}

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
			printf("Argumento invalido a hacerReceta. Caracter: %c (%i)\n",c,c);
			abort();
		}
	}
}

void aleatorio(cubo* C)
{
	int i;
	void (*funcs[])(cubo*) = { girarF, girarf, girarU, giraru,
	                           girarD, girard, girarR, girarr,
	                           girarL, girarl, girarB, girarb };
	
	i = rand() % (sizeof funcs / sizeof (funcs[0]));
	(funcs[i])(C);
}

void mostrarCuboS(cubo* C, char *s)
{
	int o=0;
	int i;
	
	if (C == NULL)
	{
		fprintf(stderr ,"mostrarCubo recibió argumento nulo\n");
		return;
	}
	
	for(i=0;i<3;++i)
	{
		o += sprintf(s+o, "%i %i %i ",C->U[3*i+0],C->U[3*i+1],C->U[3*i+2]);
	}
	
	for(i=0;i<9;i=i+3)
	{
		o += sprintf(s+o, "%i %i %i ",C->L[i+0],C->L[i+1],C->L[i+2]);
		o += sprintf(s+o, "%i %i %i ",C->F[i+0],C->F[i+1],C->F[i+2]);
		o += sprintf(s+o, "%i %i %i ",C->R[i+0],C->R[i+1],C->R[i+2]);
		o += sprintf(s+o, "%i %i %i ",C->B[i+0],C->B[i+1],C->B[i+2]);
	}
	
	for(i=0;i<3;++i)
	{
		o += sprintf(s+o, "%i %i %i ",C->D[3*i+0],C->D[3*i+1],C->D[3*i+2]);
	}

	s[o] = '\n';
	s[o+1] = 0;
}

int main(int argc, char** argv)
{
	cubo* C;
	cubo* check;
	
	char sol[5000];
	char input[5000];
	int i;
	
	int t=0;
	int pasos=0;
	
	int max;
	
	int corr=0;
	int tot=0;
	
	long long tiempotot=0;
	int tunnel[2];

	
	C = malloc(sizeof(cubo));
	check = malloc(sizeof(cubo));

	start_proc("./rubik", tunnel);	

	if(argc > 1)
		max = atoi(argv[1]);
	else
	{
		printf("Cuantos casos de prueba? ");
		scanf("%i",&max);
	}
		
	for(i=0;i<9;++i) /* cubo resuelto */
	{
		check->F[i] = 1;
		check->B[i] = 2;
		check->R[i] = 3;
		check->L[i] = 4;
		check->D[i] = 5;
		check->U[i] = 6;
	}
	
	srand(time(NULL) + getpid());
	
	while(tot<max)
	{
		for(i=0;i<100;++i)
			aleatorio(check); /* scramble */
			
		*C = *check; /*guardo el original */
		
		mostrarCuboS(C, input);

		start_clock();
		writen(tunnel[1], input, strlen(input)); /* era tunnel[1] */
		readline(tunnel[0], sol, 5000);
		stop_clock();

		sol[strlen(sol) - 1] = 0;
		hacerReceta(C,sol);
		
		if(!solved(C))
		{
			printf("ERROR en el cubo (intento %i):\n", tot);
			mostrarCubo(check);
			printf("Solucion propuesta: <%s>\n",sol);
			printf("Resultado al aplicar la solucion:\n");
			mostrarCubo(C);
			free(C); free(check);
			return 0; /*descomentar para que se detenga al primer error*/
		}
		else
		{
			pasos+=strlen(sol);
			corr++;
		}
		
		tot++;
		tiempotot += get_clock();
		
		if(tot >= t)
		{
			t+=1000;
			fprintf(stderr, "ok/total:%i/%i\tpasos prom:%.3f\ttiempo prom:%li us\n",corr,tot,1.0*pasos/tot,(long)(tiempotot/tot));
		}
	}
	
	free(C); free(check);	
	return 0;
}

