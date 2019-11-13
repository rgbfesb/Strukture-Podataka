#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N (1024)

typedef struct List Lista;
typedef struct List *Pozicija;

struct List
{
	char ime[N];
	char prezime[N];
	int element;
	Pozicija Next;

};

int IspisListe(Pozicija);
int Unija(Pozicija, Pozicija, Pozicija);
int Presjek(Pozicija, Pozicija, Pozicija);
int Citajfile(Pozicija , const char* );
int SpremiUP3(Pozicija, Pozicija);
int ProvjeriKrajListe(Pozicija, Pozicija , Pozicija);
Pozicija Alokacija(Pozicija);

int main(void)
{
	Lista Lista1,Lista2, Lista3,Lista4;
	Lista1.Next = NULL, Lista2.Next = NULL, Lista3.Next = NULL, Lista4.Next=NULL;
	const char *a = "lista1.txt";
	const char *b = "lista2.txt";
	
	Citajfile(&Lista1, a);
	Citajfile(&Lista2, b);

	IspisListe(&Lista1);
	IspisListe(&Lista2);
	Unija(&Lista1, &Lista2, &Lista3);
	IspisListe(&Lista3);
	Presjek(&Lista1, &Lista2, &Lista4);
	IspisListe(&Lista4);
	
	getchar();

	return 0;
}

int Unija(Pozicija P1, Pozicija P2, Pozicija P3)
{
	P1 = P1->Next;
	P2 = P2->Next;
	if (NULL == P1)
		return  1;
	else if (NULL == P2)
		return 1;

	while (NULL != P1 && NULL != P2)
	{
		if (P1->element == P2->element)
		{
			SpremiUP3(P1, P3);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->element < P2->element)
		{
			SpremiUP3(P1, P3);
			P1 = P1->Next;
		}
		else if(P1->element > P2->element)
		{
			SpremiUP3(P2, P3);
			P2 = P2->Next;	
		}	
	}
	ProvjeriKrajListe(P1, P2, P3);

	return 0;
}

int Presjek(Pozicija P1, Pozicija P2, Pozicija P3)
{	
	P1 = P1->Next;
	P2 = P2->Next;

	if (NULL == P1)
	{
		printf("Presjek sa nulom je nula\n");
		return 1;
	}
	else if(NULL == P2)
	{
		printf("Presjek sa nulom je nula\n");
		return 1;
	}
	while (NULL != P1 && NULL != P2)
	{
		if (P1->element == P2->element)
		{
			SpremiUP3(P1, P3);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->element < P2->element)
		{
			P1 = P1->Next;
		}
		else if (P1->element > P2->element)
		{
			P2 = P2->Next;
		}
	}
	return 0;
}

int IspisListe(Pozicija P)		//ispis liste
{
	if (NULL == P->Next)
	{
		printf("Lista je prazna\n");
		return 0;
	}
	while (NULL != P->Next) 
	{
		printf("%s\t%s\t %d\n", P->Next->ime, P->Next->prezime, P->Next->element);
		P = P->Next;
	}
	printf("\n");
	return 0;
}

int Citajfile(Pozicija P, const char* ime_dat)
{
	Pozicija temp=NULL;
	FILE* fp = NULL;
	fp = fopen(ime_dat, "r");
	if (NULL == fp)
	{
		printf("Nema dovoljno prostora u memoriji za otvaranje filea\n");
		return 1;
	}

	while (!feof(fp))
	{
		temp = Alokacija(temp);
		if (NULL == temp) {
			printf("Nema dovoljno prostora u memoriji\n");
			return 1;
		}
		fscanf(fp, " %s %s %d", temp->ime, temp->prezime, &temp->element);
		while (NULL != P->Next)
			P = P->Next;
		temp->Next = P->Next;
		P->Next = temp;
	}
	fclose(fp);
	return 0;
}
Pozicija Alokacija(Pozicija temp)
{
	temp = (Pozicija)malloc(sizeof(Lista));
	if (NULL == temp)
	{
		printf("Greska pri alokaciji\n");
		return NULL;
	}
	return temp;
}

int SpremiUP3(Pozicija P, Pozicija P3)
{
	Pozicija temp=NULL;
	temp = Alokacija(temp);
	temp->element = P->element;
	strcpy(temp->ime, P->ime);
	strcpy(temp->prezime, P->prezime);
	temp->Next = P3->Next;
	P3->Next = temp;

	return 0;
}

int ProvjeriKrajListe(Pozicija P1, Pozicija P2, Pozicija P3)
{
	while ((NULL == P1&&NULL != P2) || (NULL == P2&&NULL != P1))
	{
		if (NULL == P1)
		{
			SpremiUP3(P2, P3);
			P2 = P2->Next;
		}
		else
		{
			SpremiUP3(P1, P3);
			P1 = P1->Next;
		}
	}
	return 0;
}