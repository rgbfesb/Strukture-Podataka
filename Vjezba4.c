#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N (1024)

typedef struct Poli Poli;
typedef struct Poli *Polinom;

struct Poli
{
	int koeficijent;
	int potencija;
	Polinom Next;
};


Poli ZbrajanjePolinoma(Polinom, Polinom, Polinom);
Poli MnozenjePolinoma(Polinom, Polinom, Polinom);
Poli Citajfile(Polinom, const char*);
Polinom CitajPolinom(FILE *);
int SortirajListu(Polinom);
int IspisListe(Polinom);



int main(void)
{
	char *a = "datoteka11.txt";
	char *b = "datoteka12.txt";

	Poli P1, P2, PZbroj, PMnozenje;

	P1.Next = NULL,P2.Next = NULL,PZbroj.Next = NULL,PMnozenje.Next = NULL;

	P1 = Citajfile(&P1, a); //upisuje prvi polinom
	IspisListe(&P1);

	P2 = Citajfile(&P2, b);	//upisuje drugi polinom
	IspisListe(&P2);

	PZbroj = ZbrajanjePolinoma(&P1, &P2, &PZbroj);		//zbraja polinome
	PMnozenje = MnozenjePolinoma(&P1, &P2, &PMnozenje);	//mnozi polinome	

	IspisListe(&PZbroj);
	IspisListe(&PMnozenje);
	int p = 4;
	return 0;
}

Poli Citajfile(Polinom P, const char* ime_dat)
{
	Polinom temp;
	FILE* fp = NULL;
	fp = fopen(ime_dat, "r");
	if (NULL == fp)
	{
		printf("Nema dovoljno prostora u memoriji za otvaranje filea\n");
		return *P;
	}
	
	while (!feof(fp))
	{
	
		temp = (Polinom)malloc(sizeof(Poli));
		if (NULL == temp) {
			printf("Nema dovoljno prostora u memoriji\n");
			return *P;
		}

		fscanf(fp, " %d %d", &temp->koeficijent, &temp->potencija);

		temp->Next = P->Next;
		P->Next = temp;

	}
	fclose(fp);
	SortirajListu(P);
	return *P;
}

Poli ZbrajanjePolinoma(Polinom P1, Polinom P2, Polinom P)
{
	Polinom temp,klonP2,klonP;
	int provjera = 0;
	klonP2 = P2->Next, P2 = P2->Next;
	klonP = P->Next, P1 = P1->Next;

	while (NULL != P1)
	{
		while (NULL != P2)
		{
			if (P1->potencija == P2->potencija)
			{
				temp = (Polinom)malloc(sizeof(Poli));
				temp->potencija = P1->potencija;
				temp->koeficijent = P1->koeficijent + P2->koeficijent;

				temp->Next = P->Next;
				P->Next = temp;
				provjera++;
			}
			else if (NULL == P2->Next&&provjera == 0)
			{
				temp = (Polinom)malloc(sizeof(Poli));
				temp->potencija = P1->potencija;
				temp->koeficijent = P1->koeficijent;

				temp->Next = P->Next;
				P->Next = temp;
			}
			P2 = P2->Next;
		}
		provjera = 0;
		P1 = P1->Next;
		P2 = klonP2;

	}
	
	while (NULL != klonP2)
	{
		provjera = 0;
		while (NULL != klonP)
		{
			if (klonP->potencija == klonP2->potencija)
				provjera++;

			klonP = klonP->Next;	
		}
		if (provjera == 0) {
			temp = (Polinom)malloc(sizeof(Poli));
			temp->potencija = klonP2->potencija;
			temp->koeficijent = klonP2->koeficijent;

			temp->Next = P->Next;
			P->Next = temp;
		}
		klonP2 = klonP2->Next;
		klonP = P->Next;	
	}
	SortirajListu(P);
	return *P;
}



Poli MnozenjePolinoma(Polinom P1, Polinom P2, Polinom P)
{
	Polinom klonP2=P2,temp;
	
	while (NULL != P1->Next)
	{
		P1 = P1->Next;
		while (NULL != P2->Next)
		{
			P2 = P2->Next;
			
			temp = (Polinom)malloc(sizeof(Poli));
			temp->koeficijent = P1->koeficijent*P2->koeficijent;
			temp->potencija = P1->potencija + P2->potencija;

			temp->Next = P->Next;
			P->Next = temp;
		
		}
		P2 = klonP2;
	
	}
	SortirajListu(P);
	klonP2 = P->Next;
	while (NULL != klonP2->Next)
	{
		if (klonP2->potencija==klonP2->Next->potencija)
		{
			klonP2->koeficijent=klonP2->koeficijent+ klonP2->Next->koeficijent;
			temp = klonP2->Next;
			klonP2->Next = klonP2->Next->Next;
			free(temp);
		}
		else
		klonP2 = klonP2->Next;
	}
	
	return *P;
}


int IspisListe(Polinom P)
{
	if (NULL == P->Next)
	{
		printf("Lista je prazna\n");
		return 0;
	}

	P = P->Next;

	while (NULL != P) {
		if (P->koeficijent != 0) {

			if (P->koeficijent > 0)
				printf("+");

			if (P->potencija == 0)
				printf("%d", P->koeficijent);

			else if (P->potencija == 1)
				printf("%dx", P->koeficijent);

			else
				printf("%dx^%d", P->koeficijent, P->potencija);
		}

		P = P->Next;
		
	}
	printf("\n");
	return 0;
}

int SortirajListu(Polinom P)	
{
	Polinom prev, j, temp, end;
	end = NULL;
	if (NULL == P)
	{
		printf("Poslana NULL adresa umjesto adrese od head\n");
		return 0;
	}

	while (P->Next != end) {
		prev = P;
		j = P->Next;
		while (j->Next != end)
		{
			if (j->potencija<j->Next->potencija)
			{
				temp = j->Next;
				prev->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;
				j = temp;
			}
			prev = j;
			j = j->Next;
		}
		end = j;
	}
	return 0;
}