#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N (2)
#define Head ("Head")
#define Next ("Next")
#define Previous ("Previous")

typedef int * Lista;

int Spremi(Lista, const char *, Lista, const char *);
int Provjera(const char*);
int Inicijaliziraj(Lista);

int main(void)
{
	Lista Lista1= (Lista) malloc(N * sizeof(Lista));
	Lista Lista2= (Lista) malloc(N * sizeof(Lista));
	//1 je next 2 je previous
	Inicijaliziraj(Lista1);
	Inicijaliziraj(Lista2);
	Spremi(Lista1, Next, Lista2, Head);
	Spremi(Lista2, Previous, Lista1, Head);

	return 0;
}

int Spremi(Lista P, const char * op1, Lista Q, const char *op2)
{
	int poz1 = 0;
	int poz2 = 0;

	if (strcmp(op1, Head) == 0)
	{
		printf("Pokusaj prebrisavanja heada od liste.\n");
		return -1;
	}

	poz1 = Provjera(op1);
	poz2 = Provjera(op2);

	if (poz2 == 0)
		P[poz1] = Q;
	else
		P[poz1] = &Q[poz2];

	return 0;
}

int Provjera(const char* op)
{
	if (strcmp(op, Previous) == 0)
		return 2;
	else if (strcmp(op, Next) == 0)
		return 1;
	else
		return 0;
}

int Inicijaliziraj(Lista Lista)
{
	int i = 0;
	
	for (i = 1; i <= N; i++)
		Lista[i] = NULL;

	return 0;
}