#include "post.h"

static int reemplazar(char* orig, char* a, char* b);

static char* tabla[] =
{
	"ff","FF", "uu","UU", "bb","BB",
	"dd","DD", "rr","RR", "ll","LL",

	"Ll","", "lL","", "Rr","",
	"rR","", "Dd","", "dD","",
	"Ff","", "fF","", "Uu","",
	"uU","", "Bb","", "bB","",

	"UUU","u", "uuu","U", "FFF","f",
	"fff","F", "rrr","R", "RRR","r",
	"DDD","d", "ddd","D", "bbb","B",
	"BBB","b", "LLL","l", "lll","L",

	"bf","fb", "bF","Fb", "Bf","fB",
	"BF","FB",

	"lr","rl", "Lr","rL", "lR","Rl",
	"LR","RL",

	"du","ud", "dU","Ud", "Du","uD",
	"DU","UD",
};

void simplificar(char* str)
{
	unsigned int i;
	int R = 1;
	
	while(R != 0)
	{
		R = 0;
	
		for(i=0;i<sizeof(tabla)/sizeof(char*);i+=2)
			R += reemplazar(str,tabla[i],tabla[i+1]);
	}
}

static int reemplazar(char* orig, char* a, char* b) /*LONG A >= LONG B, critico*/
{
	int j,k;
	int R = 0;
	char* dest = orig;

	while(*orig != 0)
	{
		j = 0;
		while(orig[j] != 0 && a[j] != 0 && orig[j] == a[j]) j++;
		
		if(a[j] == 0)
		{
			R = 1; /*reemplacé algo.*/
			
			for(k=0;b[k]!=0;++k)
				dest[k] = b[k];
			
			dest+=k;
			orig+=j;
		} else
			*dest++ = *orig++;
	}
	
	*dest = 0;
	return R; } 
