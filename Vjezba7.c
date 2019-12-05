#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N (50)

typedef struct Stog *Pok;

struct Stog
{
	int element;
	Pok Next;
};


int PushStog(Pok,int);
int Pop(Pok);
int IspisListe(Pok);
int Racun(Pok, char);
int Obrada(Pok, char*);

int main(void)
{
	struct Stog Slack;
	char niz[N];
	Slack.Next = NULL;
	scanf("%s",niz);
	Obrada(&Slack,niz);

	printf("Rezultat je %d.\n", Pop(&Slack));
	return 0;
}

int PushStog(Pok P,int el)
{
	Pok q = NULL;
	q = (Pok)malloc(sizeof(struct Stog));

	q->Next = P->Next;
	P->Next = q;
	q->element = el;

	return 0;
}

int Pop(Pok P)
{
	int vrijednost = 0;
	Pok temp = NULL;
	if (NULL != P) {
		temp = P->Next;
		vrijednost = temp->element;
		P->Next = temp->Next;
		free(temp);
	}

	return vrijednost;
}

int IspisListe(Pok P)
{
	if (NULL == P->Next)
	{
		printf("Lista je prazna\n");
		return 0;
	}

		P = P->Next;

	while (NULL != P)
	{	
		printf("%d\n", P->element);
		P = P->Next;
	}

	return 0;
}

int Racun(Pok P,char op)
{

	switch (op) {
	case '+': return Pop(P) + Pop(P);
	case '-': return -Pop(P) + Pop(P);
	case '*': return Pop(P) * Pop(P);
	case '/': return (int)((float)1/Pop(P) * Pop(P));
	}

	return 0;
}
int Obrada(Pok P, char* niz)
{
	int i = 0;
	char a = '\0';

	for ( i = 0; niz[i] != '\0'; i++)
	{
		a = niz[i];
		if (a >= '0' && a <= '9')
			PushStog(P, (int)a);

		else
			PushStog(P, Racun(P, a));
	}

	return 0;
}