#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Stablo;
typedef struct Stablo *Pok;

struct Stablo
{
	int element;
	Pok Left;
	Pok Right;
};
Pok Unos(int, Pok);
Pok TraziMin(Pok);
int Ispis(Pok);
Pok Brisanje(int, Pok);
int Trazi(int, Pok);


int main(void)
{
	struct Stablo Tree;
	Tree.Left = NULL;
	Tree.Right = NULL;
	int el = 0;
	printf("Unesite root element\n");
	scanf("%d", &Tree.element);
	int meni = 0;
	do {
		printf("1:Unos elementa \n2:Brisanje elementa\n3:Trazenje elementa\n4:Ispis stabla\n\n0:Exit\n\n");

		scanf("%d", &meni);
		switch (meni)
		{
		case 1:
			printf("Unesite element koji zelite unijeti\n");
			scanf("%d", &el);
			Unos(el,&Tree);
			break;
		case 2:
			printf("Unesite element koji zelite izbrisati\n");
			scanf("%d", &el);
			Brisanje(el, &Tree);
			break;
		case 3:
			printf("Unesite element koji trazite\n");
			scanf("%d", &el);
			Trazi(el, &Tree);
			break;
		case 4:
			printf("\n");
			Ispis(&Tree);
			break;
		}
		printf("\n\n");

	} while (meni != 0);
	return 0;

}
Pok Unos(int el, Pok P)
{
	if (NULL == P)
	{
		P = (Pok)malloc(sizeof(struct Stablo));
		P->Left = NULL;
		P->Right = NULL;
		P->element = el;
	}

	else if (el > P->element)
		P->Right = Unos(el, P->Right);

	else if(el < P->element)
		P->Left = Unos(el, P->Left);

	return P;
}

int Trazi(int el, Pok P)//P je root
{
	while (NULL != P)
	{
		if (el > P->element)
			P = P->Right;

		else if (el < P->element)
			P = P->Left;

		else
		{
			printf("Taj element postoji u stablu\n");
			return 0;
		}
	}

	printf("Taj element ne postoji u stablu\n");
	return 0;
}

Pok TraziMin(Pok P)
{
	if (NULL == P)
		return P;

	if (NULL == P->Left);
		return P;
	
	return TraziMin(P->Left);
}

Pok Brisanje(int el, Pok P)
{
	if (NULL == P)
	{
		printf("Ne postoji trazeni element\n");
		return P;
	}
	if (el > P->element)
		P->Right = Brisanje(el, P->Right);

	else if (el < P->element)
		P->Left = Brisanje(el, P->Left);

	else if (NULL != P->Left && NULL != P->Right)
	{
		Pok Temp;
		Temp = TraziMin(P->Right);
		P->element = Temp->element;
		P->Right = Brisanje(P->element, P->Right);
	}
	else 
	{
		Pok Temp = P;
		if (NULL == P->Left)
			P = P->Right;
		else
			P = P->Left;
		free(Temp);
	}
	return P;
}
int Ispis(Pok P)
{
	if (NULL != P)
	{
		Ispis(P->Left);
		printf("%d\n", P->element);
		Ispis(P->Right);
	
	}
}