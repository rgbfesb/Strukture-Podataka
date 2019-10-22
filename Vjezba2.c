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
int TraziPrezime(char*,Pozicija);
int BrisiElement(int,Pozicija);

int main(void)
{
	
	int i = 5,provjera =0, n=0;
	char a[N];
	Pozicija Head = NULL;

	Head = (Pozicija)malloc(sizeof(Pozicija));
	Head->Next = NULL;

	DodajNaPocetak(i, Head);
	DodajNaPocetak(i + 1, Head);
	DodajNaPocetak(i - 4, Head);
	DodajNaKraj(i - 1, Head);
	IspisListe(Head);
	printf("Unesite prezime koje trazite\n");
	scanf("%s", a);
	provjera=TraziPrezime(a,Head);
	if (provjera > 0)
		printf("Pronadeno je prezime %s\n", a);
	else
		printf("Prezime nije pronadeno\n");
	printf("Unesite element koji zelite brisati\n");
	scanf("%d", &n);
	BrisiElement(n, Head);
	IspisListe(Head);
	getchar();

	return 0;

}

int DodajNaPocetak(int i, Pozicija P)
{
	Pozicija temp;
	temp = (Pozicija) malloc(sizeof(Pozicija));
	if (temp == NULL)
		printf("nema prostora");


	temp->element = i;
	temp->Next = P->Next;
	P->Next = temp;

	printf("Unesi ime\n");
	scanf(" %s", temp->ime);
	printf("Unesi prezime\n");
	scanf(" %s", temp->prezime);
	printf("Unesi godiste\n");
	scanf("%d", &temp->godina);
	return 0;

}
int DodajNaKraj(int i, Pozicija P)
{
	Pozicija temp2;
	temp2 = (Pozicija)malloc(sizeof(Pozicija));
	if (temp2 == NULL)
		printf("nema prostora");


	temp2->element = i;
	printf("Unesi ime\n");
	scanf(" %s", temp2->ime);
	printf("Unesi prezime\n");
	scanf(" %s", temp2->prezime);
	printf("Unesi godiste\n");
	scanf("%d", &temp2->godina);

	while (P->Next != NULL)
		P = P->Next;

	temp2->Next = P->Next;
	P->Next = temp2;
	return 0;

}
int IspisListe(Pozicija P)
{

	while (P->Next != NULL) {

		printf("%s\t%s\t %d\t %d\n", P->Next->ime, P->Next->prezime, P->Next->godina, P->Next->element);
		P = P->Next;

	}
	getchar();
	return 0;
}
int TraziPrezime(char *a, Pozicija P)
{
	int spremiste = 0;
	P = P->Next;
	while (P->Next != NULL)
	{
		if (strcmp(a, P->prezime)==0)
			spremiste++;
		P = P->Next;
	}
	getchar();
	return spremiste;
}
int BrisiElement(int i, Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Pozicija));
	q = P->Next;
	while (q!= NULL)
	{
		if (i == q->element) {
			P ->Next=q->Next;
			q = NULL;
		}
		else{
			P = P->Next;
			q = q->Next;
		}
	}
	free(q);
return 0;
}