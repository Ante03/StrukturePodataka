#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//struktura elementa
struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
	int number;
	Position next;
} StackElement;

//funkcije
int read_from_file(char* buffer);
Position createNewEl(int num);
int push(Position head, int num);
int stringToStack(Position head, char* buffer);
int do_operation(Position head, char operation);
int pop(Position head);
int print(Position head);

//main funkcija
int main() {

	char* buffer[1024];
	StackElement head = { .number = 0, .next = NULL };

	read_from_file(buffer);
	stringToStack(&head, buffer);
	print(&head);

	return 0;
}

//funkcija za pohranjivanje postfix izraza u stog
int read_from_file(char* buffer) {
	FILE* filepointer;
	filepointer = fopen("postfix.txt", "r");
	if (!filepointer) {
		printf("Filepointer MISTAKE!");
		return 0;
	}
	fgets(buffer, 1024, filepointer);
	printf("%s", buffer);

	fclose(filepointer);
	return 0;
}

//funkcija prebaciivanja u vezan listu
int stringToStack(Position head, char* buffer) {
	char* currentbuffer = buffer;
	int numBy = 0, status=0, CurrentNumber=0;
	char operation = 0;

	while (strlen(currentbuffer) > 0) {
		numBy = 0;
		status = sscanf(currentbuffer, " %d %n", &CurrentNumber, &numBy);
		if (status == 1) {
			push(head, CurrentNumber);
		}
		if (status != 1) {
			sscanf(currentbuffer, " %c %n", &operation, &numBy);
			do_operation(head, operation);
		}
		currentbuffer += numBy;
	}
	return 0;
}

//funkcija push za dodavanje elementa u niz
int push(Position head, int num) {
	Position newel;
	newel = createNewEl(num);

	newel->next = head->next;
	head->next = newel;
	
	return 0;
}

//funkcija za stvaranje elementa
Position createNewEl(int num) {
	Position newel;
	newel = (Position)malloc(sizeof(StackElement));
	if (!newel) {
		printf("newel Mistake!");
		return NULL;
	}
	newel->number = num;
	return newel;
}

//funkcija za obavljenje operacije
//nad dva broja
int do_operation(Position head, char operation) {
	int Num1 = 0, Num2 = 0, result = 0;
	Num1 = pop(head);
	Num2 = pop(head);
	switch (operation)
	{
	case '+':
		result = Num1 + Num2;
		break;
	case '-':
		result = Num1 - Num2;
		break;
	case '*':
		result = Num1 * Num2;
		break;
	case '/':
		result = Num1 / Num2;
		break;
	default:
		return EXIT_FAILURE;
		break;
	}
	push(head, result);
	return 0;
}

//funkcija za izbacivanje
//prvog clana vezane liste
int pop(Position head) {
	int num=0;
	Position first = NULL;
	if (!head) {
		printf("PRAZNA LISTA!");
		return 0;
	}
	first = head->next;
	head->next = head->next->next;
	num = first->number;
	free(first);

	return num;
}

//funkcija za ispis
int print(Position head) {

	Position current = head->next;
	if (!current) {
		printf("PRAZNA LISTAA");
		return 0;
	}
	while (current) {
		printf("\n%d", current->number);
		current = current ->next;
	}
	return 0;
}