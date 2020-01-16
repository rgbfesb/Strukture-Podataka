#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N (11)

typedef struct Struct;
typedef struct Struct *Pok;

struct Struct
{
	char ime[N];
	char prezime[N];
	int matbroj;
	Pok Next;
};

int Preslikavanje(char *);
int DodajHash(Pok,Pok);
int Ispis(Pok);
int IspisListe(Pok);
int IspisMb(char*, char *, Pok);
int Init(Pok);

int main(void)
{
	struct Struct HashList[N];
	Pok temp=NULL;
	char ime[N] = {0};
	char prezime[N] = {0};
	int i = 0;
	for (i = 0; i < N; i++)
		Init(&HashList[i]);

	for (i = 0; i < N; i++)
	{
		temp =(Pok) malloc(sizeof(struct Struct));
		Init(temp);
		printf("Unesite ime , prezime i maticni broj studenta %d\n", i + 1);
		scanf("%s %s %d", temp->ime, temp->prezime, &temp->matbroj);
		DodajHash(HashList,temp);
	}
	Ispis(HashList);
	printf("Ciji maticni broj trazite?\n");
	scanf("%s %s", ime, prezime);
	IspisMb(ime, prezime, HashList);

	return  0;
}

int Preslikavanje(char * prez)
{
	int temp = 0;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if(i<(int)strlen(prez))
		temp += prez[i];
	}
	return temp%N;
}

int DodajHash(Pok P,Pok temp)	
{
	int key = 0;

	key = Preslikavanje(temp->prezime);
	P = &P[key];
	temp->Next = P->Next;
	P->Next = temp;

	return 0;

}
int Ispis(Pok P)
{
	int i = 0;
	Pok temp = P;
	puts("\n");
	for(i=1; i<=N; i++)
	{
		if(P)
		IspisListe(P);
		P= &temp[i];
	}
	return 0;
}

int IspisListe(Pok P)
{
	P = P->Next;
	while (NULL != P)
	{
		printf("%s %s %d\n", P->ime, P->prezime, P->matbroj);
		P = P->Next;
	}
	return 0;
}
int IspisMb(char* ime,char* prezime, Pok p)
{
	int key = Preslikavanje(prezime);
	Pok List=&p[key];
	List = List->Next;

	while (List)
	{
		if (!strcmp(prezime, List->prezime)&& !strcmp(ime, List->ime))
		{
			printf("Postoji taj student i %d mu je MB\n", List->matbroj);
			return 0;
		}

		List = List->Next;
	}
	printf("Ne postoji taj student\n");
	return 0;
}

int Init(Pok P)
{
	P->Next = NULL;
	P->ime[0] = '/0';
	P->prezime[0] = '/0';
	P->matbroj = 0;

	return 0;

}