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

int Unos(Pozicija);
int DodajNaPocetak(Pozicija);
int DodajNaKraj(Pozicija);
int IspisListe(Pozicija);
int SortirajListu(Pozicija);
int UbaciIzaElementa(Pozicija);
int UbaciIspredElementa(Pozicija);
int BrisiElement(Pozicija);
int BrisiSve(Pozicija);
int TraziPrezime(Pozicija);
Pozicija TraziElement(int, Pozicija);
int UpisUDatoteku(const char*, Pozicija);
int IspisIzDatoteke(const char *, Pozicija);


int main(void)
{
	const char* ime_file = "datoteka.txt";
	Pozicija Head;

	Head = (Pozicija)malloc(sizeof(Pozicija));
	Head->Next = NULL;

	DodajNaPocetak(Head);		//dodajemo element na pocetak liste
	DodajNaPocetak(Head);		//dodajemo element na pocetak liste
	DodajNaPocetak(Head);		//dodajemo element na pocetak liste
	DodajNaKraj(Head);			//dodajemo element na kraj liste
	IspisListe(Head);			//ispisujemo listu
	TraziPrezime(Head);			//trazimo prezime
	BrisiElement(Head);			//brisemo element iz liste
	IspisListe(Head);			//ispisujemo listu
	UbaciIzaElementa(Head);		//ubacujemo iza nekog elementa
	IspisListe(Head);			//ispisujemo listu
	UbaciIspredElementa(Head);	//ubacujemo ispred nekog elementa
	IspisListe(Head);			//ispisujemo listu
	SortirajListu(Head);		//sortiramo listu po prezimenima
	IspisListe(Head);			//ispisujemo listu
	UpisUDatoteku(ime_file, Head);		//upisujemo listu u datoteku
	IspisIzDatoteke(ime_file, Head);	//ispisujemo listu iz datoteke

	system("pause");
	return 0;

}

int Unos(Pozicija temp)			//funkcija koja unosi ime prezime godinu i element
{

	printf("Unesi ime\n");
	scanf(" %s", temp->ime);
	printf("Unesi prezime\n");
	scanf(" %s", temp->prezime);
	printf("Unesi godiste\n");
	scanf("%d", &temp->godina);
	printf("Unesi element\n");
	scanf("%d", &temp->element);
	return 0;
}

int DodajNaPocetak(Pozicija P)	//unos elementa na pocetak
{
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Pozicija));
	if (NULL == temp) {
		printf("Nema dovoljno prostora u memoriji\n");
		return 0;
	}

	temp->Next = P->Next;
	P->Next = temp;

	Unos(temp);
	return 0;

}

int DodajNaKraj(Pozicija P)		//unos elementa na kraj
{
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Pozicija));
	if (NULL == temp) {
		printf("Nema dovoljno prostora u memoriji\n");
		return 0;
	}

	Unos(temp);

	while (NULL != P->Next)
		P = P->Next;

	temp->Next = P->Next;
	P->Next = temp;
	return 0;

}

int IspisListe(Pozicija P)		//ispis liste
{
	if (NULL == P->Next)
	{
		printf("Lista je prazna\n");
		return 0;
	}


	while (NULL != P->Next) {

		printf("%s\t%s\t %d\t %d\n", P->Next->ime, P->Next->prezime, P->Next->godina, P->Next->element);
		P = P->Next;
	}
	printf("\n");
	return 0;
}

int SortirajListu(Pozicija P)	//funkcija koja sortira listu po prezimenima
{
	Pozicija prev, j, temp, end;
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

int UbaciIzaElementa(Pozicija P)	//ubacivanje elementa iza nekog elementa
{
	int x = 0;
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Pozicija));

	printf("Iza kojeg elementa zelite ubaciti\n");
	scanf("%d", &x);

	P = TraziElement(x, P);
	P = P->Next;

	if (NULL == P) {
		printf("Nije pronaden navedeni element\n");
		return 0;
	}
	else {
		Unos(q);
		q->Next = P->Next;
		P->Next = q;
		return 0;
	}
}

int UbaciIspredElementa(Pozicija P)		//ubacivanje elementa ispred nekog elementa
{
	int x = 0;
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Pozicija));

	printf("Ispred kojeg elementa zelite ubaciti\n");
	scanf("%d", &x);

	P = TraziElement(x, P);

	if (NULL == P->Next) {
		printf("Nije pronaden navedeni element\n");
		return 0;
	}
	else {
		Unos(q);
		q->Next = P->Next;
		P->Next = q;

		return 0;
	}
}

int BrisiElement(Pozicija P)		//brisanje elementa
{
	int n;
	Pozicija q;

	printf("Unesite element koji zelite brisati\n");
	scanf("%d", &n);

	q = TraziElement(n, P);

	if (NULL == q->Next)
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

int TraziPrezime(Pozicija P)		//trazenje prezimena
{
	char a[N];
	int spremiste = 0;
	P = P->Next;

	printf("Unesite prezime koje trazite\n");
	scanf(" %s", a);

	while (NULL != P->Next)
	{
		if (strcmp(tolower(a), tolower(P->prezime)) == 0)
			spremiste++;
		P = P->Next;
	}
	if (spremiste > 0)
		printf("Pronadeno je prezime %s i takvih %d\n",a,spremiste);
	else
		printf("Prezime nije pronadeno\n");

	return 0;
}


Pozicija TraziElement(int x, Pozicija P)	//funkcija koja trazi prethodnika elementu
{
	while (NULL != P->Next && P->Next->element != x)
	{
		P = P->Next;
	}
	return P;
}

int UpisUDatoteku(const char *a, Pozicija P)	//upis liste u datoteku
{
	FILE *fp = NULL;
	P = P->Next;
	fp = fopen(a, "w");

	if (NULL == fp) {
		printf("Greska pri pokusaju otvaranja filea\n");
		return 0;
	}

	while (NULL != P)
	{
		fprintf(fp, " %s %s\t %d\t %d\n", P->ime, P->prezime, P->godina, P->element);
		P = P->Next;
	}
	fclose(fp);

	return 0;
}

int IspisIzDatoteke(const char *a, Pozicija P)	//ispis iz prazne datoteke u listu
{
	FILE *fp = NULL;
	Pozicija temp = NULL;
	Pozicija temp1 = P;
	BrisiSve(P);
	fp = fopen(a, "r");

	if (NULL == fp){
		printf("Greska pri pokusaju otvaranja filea\n");
	return 0;
}
	do
	{	
		temp = (Pozicija)malloc(sizeof(Pozicija));
		temp1->Next = temp;
		fscanf(fp, " %s %s %d %d", temp->ime, temp->prezime, &temp->godina, &temp->element);
		while (NULL != temp1->Next)
			temp1 = temp1->Next;
		temp->Next = temp1->Next;
	} while (!feof(fp));

	fclose(fp);
	IspisListe(P);
	return 0;
}