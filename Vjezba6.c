#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define max (100)
#define min (10)


typedef struct Stog *Pok;

struct Stog
{
	int element;
	Pok Next;
};

int Rand();
int PushStog(Pok);
int PushRed(Pok);
int Pop(Pok);
int IspisListe(Pok);

int main(void)
{
	struct Stog Slack;

	srand((unsigned int)time(NULL));

	Slack.Next = NULL;

	PushStog(&Slack);
	PushStog(&Slack);
	PushRed(&Slack);
	Pop(&Slack);

	IspisListe(&Slack);
	return 0;
}

int Rand()
{
	int randBr = 0;
	randBr = (min + (rand() / (RAND_MAX / (max - min + 1) + 1)));
	return randBr;
}

int PushStog(Pok P)
{
	Pok q = NULL;
	q = (Pok)malloc(sizeof(struct Stog));

	q->Next = P->Next;
	P->Next = q;
	q->element = Rand();

	return 0;
}

int PushRed(Pok P)
{
	Pok q = NULL;
	q = (Pok)malloc(sizeof(struct Stog));
	q->element = Rand();
	while (NULL != P->Next)
		P = P->Next;

	q->Next = P->Next;
	P->Next = q;

	return 0;
}
int Pop(Pok P)
{
	int vrijednost = 0;
	Pok temp = NULL;
	temp = P->Next;

	vrijednost = temp->element;

	P->Next = temp->Next;

	free(temp);

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