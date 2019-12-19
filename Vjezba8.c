#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#define N (64)

typedef struct Stablo *Grana;

typedef struct Stablo
{
	Grana PodDir;
	Grana Next;
	Grana NadDir;
	char ime[N];

}Stablo;


int UnosDir(Grana);
int UnosPodDir(Grana);
int Ispis(Grana);
int IspisDir(Grana);
Grana PovratakUPret(Grana);
Grana Ajde_U_Dir(Grana);

int main(void)
{
	struct Stablo Tree;
	Grana Pok = &Tree;
	Tree.Next = NULL;
	Tree.PodDir = NULL;
	strcpy(Tree.ime,"C:");
	int meni = 0;
	do {
		printf("1:Unos Direktorija\n2:Unos Poddirektorija\n3:Ispis Direktorija\n4:Povratak U Prethodni Direktorij\n5:Ulaz u direkorij\n\n0:Exit\n\n");
		Ispis(Pok);

		scanf("%d", &meni);
		switch (meni)
		{
		case 1:
			UnosDir(Pok);
			break;
		case 2:
			UnosPodDir(Pok);
			break;
		case 3:
			IspisDir(Pok);
			break;
		case 4:
			Pok=PovratakUPret(Pok);
			break;
		case 5:
			Pok = Ajde_U_Dir(Pok);
			break;
		}
		printf("\n\n");
	
	} while (meni!=0);
	return 0;
}

int UnosDir(Grana P)
{
	Grana temp;
	temp = (Grana)malloc(sizeof(struct Stablo));
	while ( NULL!=P->Next)
		P = P->Next;

	printf("Unesite ime direktorija\n");
	scanf(" %s", &temp->ime);

	temp->Next = P->Next;
	P->Next = temp;
	temp->PodDir = NULL;

	return 0;
}

int UnosPodDir(Grana P)
{
	Grana temp;
	int prov = 0;
	char ime[N];
	temp = (Grana)malloc(sizeof(struct Stablo));
	printf("Kojem direktoriju zelite unijeti poddirektorij? \n");
	scanf(" %s", &ime);

	while (P != NULL&&prov == 0)
	{
		if (strcmp(tolower(ime), tolower(P->ime)) != 0)
			P = P->Next;
		else
			prov = 1;
	}

	if (NULL == P&&prov==0) {
		printf("Nema tog direktorija\n");
		return 0;
	}

	printf("Unesite ime poddirektorija\n");
	scanf(" %s", &temp->ime);

	temp->NadDir = P;

	temp->Next = P->PodDir;
	P->PodDir = temp;
	temp->PodDir = NULL;

	return 0;
}

int Ispis(Grana P)
{

	if (NULL == P)
	{
		printf("Direktorij je prazan. \n");
		return 0;
	}

	while (NULL != P){
		printf("%s\n", P->ime);
	P= P->Next;
}
	return 0;
}

int IspisDir(Grana P)
{
	char ime[N];
	printf("Koji direktorij zelite ispisati? \n");
	scanf(" %s", &ime);
	while (P != NULL)
	{
		if (strcmp(tolower(ime), tolower(P->ime))==0)
		{
			Ispis(P->PodDir);
			return 0;
		}
		else 
		P = P->Next;
	}

	printf("Direktorij nije pronaden\n");
	return 0;
}

Grana PovratakUPret(Grana P)
{
	P = P->NadDir;
	return P;
}

Grana Ajde_U_Dir(Grana P)
{
	char ime[N];
	int prov = 0;
	printf("U koji direktorij zelite uci? \n");
	scanf(" %s", &ime);

	while (P != NULL&&prov == 0)
	{
		if (strcmp(tolower(ime), tolower(P->ime)) != 0)
			P = P->Next;
		else
			prov = 1;
	}
	if (NULL == P&&prov == 0) {
		printf("Nema tog direktorija\n");
		return 0;
	}

	return P->PodDir;
}