#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define N (20)
#define Z (100)

typedef struct _student {
	int bodovi;
	char ime[N];
	char prezime[N];
}Student;

int BrojiStudentneIzDatoteke(const char*);
int main(void)
{
	FILE *fp = NULL;
	float relb = 0;
	int brojac = 0;
	int max = 0;
	int i = 0;
	Student *ucenik = NULL;
	const char* a = "studenti.txt";


	brojac = BrojiStudentneIzDatoteke(a);

	ucenik = (Student*)malloc(brojac * sizeof(Student));

	fp = fopen(a, "r");
	for (i = 0; i < brojac; i++) {

		fscanf(fp, "%d", &ucenik[i].bodovi);
		fscanf(fp, " %s", &ucenik[i].ime);
		fscanf(fp, " %s", &ucenik[i].prezime);

		if (max < ucenik[i].bodovi)
			max = ucenik[i].bodovi;
	}
	fclose(fp);

	for (i = 0; i < brojac; i++) {
		relb = ((float)ucenik[i].bodovi) / ((float)max);
		printf("%s %s\t %d\t %.2f\n", &ucenik[i].ime, &ucenik[i].prezime, ucenik[i].bodovi, relb*Z);
	}
	return 0;
}

int BrojiStudentneIzDatoteke(const char* a)
{
	FILE *fp = NULL;
	int brojac = 0;
	fp = fopen(a, "r");
	while (!feof(fp))
	{

		if (fgetc(fp) == '\n')
			brojac++;
	}
	brojac++;
	fclose(fp);
	return brojac;
}