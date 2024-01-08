#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//struktura studenta
typedef struct student {
	char name[10];
	char surname[10];
	double bod;
}_stud;


//deklaracija funkcija
int num_lines();
int loading(int num, _stud* head);
int print(int num, _stud* head);


//main 
int main() {
	int coun = 0;
	coun = num_lines();		//pozivanje funkcije za broj redova

	struct _stud* head = NULL;							//Alociranje memorije
	head = (_stud*)malloc(coun * sizeof(_stud));		//za sve studente iz dat

	loading(coun, head);
	print(coun, head);

	return 0;
}


//funkcija koja pronalazi broj redaka
int num_lines() {
	char name[10], surname[10];
	int counter = 0;
	int bod;

	//otvaranje datoteke
	FILE* filepointer = NULL;
	filepointer = fopen("studenti.txt", "r");
	if (!filepointer) {
		printf("MISTAKE(filepointer)!!");
		return 0;
	}
	//trazenje broja redaka
	while (fscanf(filepointer, "%s %s %d", name, surname, &bod) == 3) {
		counter++;
	}

	fclose(filepointer);
	return counter;
}


//ucitavanje podataka u strukturu
int loading(int num, _stud* head) {

	int i = 0;
	FILE* filepointer = NULL;
	filepointer = fopen("studenti.txt", "r");
	if (!filepointer) {
		printf("MISTAKE(filepointer)!!");
		return 0;
	}

	//Ucitavanje u niz struktura
	for (i = 0; i < num; i++) {
		fscanf(filepointer, "%s", head[i].name);
		fscanf(filepointer, "%s", head[i].surname);
		fscanf(filepointer, "%lf", &head[i].bod);
	}
	fclose(filepointer);
	return 0;
}


//funkcija za printanje
int print(int num, _stud* head) {
	int i;
	int high_bod = head[0].bod;

	//pronalazenje najveceg broja bodova
	for (i = 1; i < num; i++) {
		if (head[i].bod > high_bod) {
			high_bod = head[i].bod;
		}
	}

	//ispisivanje studenata
	for (i = 0; i < num; i++) {
		printf("%s\t", head[i].name);
		printf("%s\t", head[i].surname);
		printf("%lf\t", head[i].bod);
		printf("%lf\n", head[i].bod / high_bod * 100);
	}
	return 0;
}