#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reemplazar(char* s, char* a, char* b)
{
	int i;
	
	while(*s)
	{
		i=0;
		while(a[i] && a[i] != *s) i++;

		if(a[i] != 0) *s = b[i];
		
		s++;
	}
}

int main()
{
	char s[200];
	char t[200];
	
	a:
	scanf("%s",s);
	
	if(*s=='X') return 0;
	
	strcpy(t,s);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	
	reemplazar(t,"FRBLfrblUuDd","flbrFLBRuUdD");
	
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	reemplazar(t,"FRBLfrbl","RBLFrblf");
	printf("\"%s\", ",t);
	
	goto a;
	return 0;
}
	
