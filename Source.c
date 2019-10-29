#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define N (1000)


typedef struct lista *Pozicija;


struct lista {
	char ime[N];
	char prezime[N];
	int godina;
	int element;
	Pozicija Next;
};

int DodajNaPocetak(int, Pozicija);
int IspisListe(Pozicija);
int DodajNaKraj(int, Pozicija);
int TraziPrezime(char*, Pozicija);
Pozicija TraziElement(int, Pozicija);
int BrisiElement(int, Pozicija);
int UbaciIzaElementa(int, int, Pozicija);
int UbaciIspredElementa(int, int, Pozicija);
int Unos(Pozicija, int);
int SortirajListu(Pozicija);
int UpisUDatoteku(const char*, Pozicija);
int IspisIzDatoteke(const char *, Pozicija);
int BrisiSve(Pozicija);


int main(void)
{

	int i = 5, provjera = 0, n = 0, z = 0;
	char a[N];
	const char* b = "datoteka.txt";
	Pozicija Head;


	Head = (Pozicija)malloc(sizeof(Pozicija));

	Head->Next = NULL;


	DodajNaPocetak(i, Head);//dodajemo elemente
	DodajNaPocetak(i + 1, Head);
	DodajNaPocetak(i - 4, Head);
	DodajNaKraj(i - 1, Head);
	IspisListe(Head);//ispisujemo listu
	printf("Unesite prezime koje trazite\n");
	scanf("%s", a);
	provjera = TraziPrezime(a, Head);//trazimo prezime
	if (provjera > 0)
		printf("Pronadeno je prezime %s\n", a);
	else
		printf("Prezime nije pronadeno\n");
	printf("Unesite element koji zelite brisati\n");//brisemo element
	scanf("%d", &n);
	BrisiElement(n, Head);

	IspisListe(Head);

	UbaciIzaElementa(5, 7, Head);//ubacujemo iza nekog elementa
	UbaciIspredElementa(5, 9, Head);//ubacujemo poslije nekog elementa


	IspisListe(Head);
	SortirajListu(Head);

	IspisListe(Head);
	UpisUDatoteku(b, Head);
	IspisIzDatoteke(b, Head);

	return 0;

}

int DodajNaPocetak(int i, Pozicija P)//unos elementa na pocetak
{
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Pozicija));
	if (temp == NULL)
		printf("nema prostora");


	temp->element = i;
	temp->Next = P->Next;
	P->Next = temp;

	Unos(temp, i);
	return 0;

}
int DodajNaKraj(int i, Pozicija P)//unos elementa na kraj
{
	Pozicija temp2;
	temp2 = (Pozicija)malloc(sizeof(Pozicija));
	if (temp2 == NULL)
		printf("nema prostora");



	Unos(temp2, i);

	while (P->Next != NULL)
		P = P->Next;

	temp2->Next = P->Next;
	P->Next = temp2;
	return 0;

}
int IspisListe(Pozicija P)//ispis liste
{
	if (P->Next == NULL)
	{
		printf("Lista je prazna\n");
		return 0;
	}


	while (P->Next != NULL) {

		printf("%s\t%s\t %d\t %d\n", P->Next->ime, P->Next->prezime, P->Next->godina, P->Next->element);
		P = P->Next;

	}
	printf("\n");
	return 0;
}
int TraziPrezime(char *a, Pozicija P)//trazenje prezimena
{
	int spremiste = 0;
	P = P->Next;
	while (P->Next != NULL)
	{
		if (strcmp(a, P->prezime) == 0)
			spremiste++;
		P = P->Next;
	}

	return spremiste;
}
int BrisiElement(int i, Pozicija P)//brisanje elementa
{
	Pozicija q;
	q = TraziElement(i, P);

	if (q->Next == NULL)
	{
		printf("Nije pronaden navedeni element\n");
		return 0;
	}
	else {
		P = q->Next;
		q->Next = P->Next;
		free(P);

		return 0;
	}
}
int UbaciIzaElementa(int x, int y, Pozicija P)//ubacivanje elementa nakon nekog vec elementa
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Pozicija));

	P = TraziElement(x, P);
	P = P->Next;
	if (P == NULL) {
		printf("Greska\n");
		return 0;
	}
	else {

		Unos(q, y);
		q->Next = P->Next;
		P->Next = q;
		return 0;
	}
}

Pozicija TraziElement(int x, Pozicija P)//funkcija koja trazi prethodnika
{
	while (P->Next != NULL&&P->Next->element != x)
	{
		P = P->Next;
	}


	return P;
}


int UbaciIspredElementa(int x, int y, Pozicija P)//za ubacivanje elementa ispred nekog postojeceg
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Pozicija));
	P = TraziElement(x, P);

	if (P->Next == NULL) {
		printf("Greska\n");
		return 0;
	}
	else {

		Unos(q, y);
		q->Next = P->Next;
		P->Next = q;

		return 0;
	}
}
int Unos(Pozicija temp, int i)//funkcija koja unosi imena i ostalo
{
	temp->element = i;
	printf("Unesi ime\n");
	scanf(" %s", temp->ime);
	printf("Unesi prezime\n");
	scanf(" %s", temp->prezime);
	printf("Unesi godiste\n");
	scanf("%d", &temp->godina);
	return 0;
}

int SortirajListu(Pozicija P)//funkcija koja sortira po prezimenima
{
	Pozicija prev, j, temp, end;
	end = NULL;
	if (P == NULL)
	{
		printf("Greska\n");
		return 0;
	}

	while (P->Next != end) {

		prev = P;
		j = P->Next;

		while (j->Next != end)
		{

			if (strcmp(j->prezime, j->Next->prezime)>0)
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
int UpisUDatoteku(const char *a, Pozicija P)//upisuje iz liste u datoteku
{
	FILE *fp = NULL;
	P = P->Next;
	fp = fopen(a, "w");
	while (P != NULL)
	{
		fprintf(fp, " %s %s\t %d\t %d\n", P->ime, P->prezime, P->godina, P->element);
		P = P->Next;
	}

	fclose(fp);
	return 0;
}

int IspisIzDatoteke(const char *a, Pozicija P)//ispisuje iz datoteke u listu
{
	FILE *fp = NULL;
	Pozicija temp = NULL;

	Pozicija temp1=P;
	BrisiSve(P);

	fp = fopen(a, "r");

	do
	{	
		temp = (Pozicija)malloc(sizeof(Pozicija));
		temp1->Next = temp;
		fscanf(fp, " %s %s %d %d", temp->ime, temp->prezime, &temp->godina, &temp->element);
		while (temp1->Next != NULL)
			temp1 = temp1->Next;
		temp->Next = temp1->Next;
	} while (!feof(fp));

	fclose(fp);
	IspisListe(P);


	return 0;

}

int BrisiSve(Pozicija P)
{
	Pozicija temp;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = P->Next->Next;
		free(temp);
	}
	P->Next = NULL;
	return 0;
}
