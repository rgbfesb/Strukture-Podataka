#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define N (64)

typedef struct Stablo *Stablo;
typedef struct Stog *Pok;

struct Stablo
{
	char element;
	Stablo Left;
	Stablo Right;

};

struct Stog {
	Stablo Pok;
	Pok Next;
};

int Ispis(const char*,Stablo);
Stablo StvoriStablo();
Pok StvoriStog();
int PushStog(Pok, char);
Stablo PopStog(Pok);
int CitajIzDat(const char*, Pok);
int Operator(char);

int main(void)
{
	struct Stog HeadStog;
	const char* a = "datoteka.txt";
	HeadStog.Next = NULL;
	CitajIzDat(a, &HeadStog);
	getchar();
	return 0;
}

int CitajIzDat(const char* dat, Pok Head)
{
	FILE *fp;
	Stablo t1 = NULL, t2 = NULL;
	char niz[N];
	int i = 0;
	fp = fopen(dat, "r");
	fgets(niz, N, fp);
	fclose(fp);

	for (i = 0; (unsigned)i <= strlen(niz); i++) {
		if (niz[i] != ' ' && niz[i] != '\0')
		{
			if (!Operator(niz[i]))//onda je broj
				PushStog(Head, niz[i]);
			else {
				t1 = PopStog(Head);
				t2 = PopStog(Head);
				PushStog(Head, niz[i]);
				Head->Next->Pok->Right = t1;
				Head->Next->Pok->Left = t2;
			}
		}
	}

		Ispis("rezultat.txt", Head->Next->Pok);
		return 0;
	
}

int Ispis(const char* a,Stablo P)
{
	if (NULL != P)
	{
		
		Ispis(a,P->Left);
		FILE* fp;
		fp = fopen(a, "a");
		fprintf(fp,"%c ",P->element);
		fclose(fp);
		Ispis(a,P->Right);
	}
	
	return 0;
}

int PushStog(Pok Head, char el)
{
	Pok q = NULL;

	q = StvoriStog();
	q->Pok->element = el;
	q->Next = Head->Next;
	Head->Next = q;

	return 0;
}

Stablo PopStog(Pok Head) {

	Pok temp = Head->Next;
	Stablo ret = temp->Pok;
	Head->Next=temp->Next;
	free(temp);
	return ret;
}

Pok StvoriStog()
{
	Pok temp = (Pok)malloc(sizeof(struct Stog));
	if (NULL == temp)
	{
		printf("Greska pri stvaranju stoga.\n");
		return temp;
	}
	else
	{
		temp->Pok = StvoriStablo();
		temp->Next = NULL;
		return temp;
	}
}

Stablo StvoriStablo()
{
	Stablo temp = (Stablo)malloc(sizeof(struct Stablo));
	if (NULL==temp)
	{
		printf("Greska pri stvaranju stabla.\n");
		return temp;
	}
	else
	{
		temp->Left = NULL;
		temp->Right= NULL;
		return temp;
	}
}

int Operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return 1;
	else
		return 0;
}