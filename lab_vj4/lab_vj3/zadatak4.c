#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _Polynom;
typedef struct _Polynom* Position;
typedef struct _Polynom {
	int coef;
	int exp;
	Position next;
} Polynom;

//deklaracija funkcija
int read_from_file(Position head1, Position head2);
Position create_poly(int coef, int exp);
int print(Position head);
int Insert_sorted(Position head, int coef, int exp);
int add(Position head, Position head1, Position head2);
int multiply(Position head, Position head1, Position head2);

int main() {
	Polynom head1 = { .coef = 0, .exp = 0, .next = NULL };
	Polynom head2 = { .coef = 0, .exp = 0, .next = NULL };
	Polynom headadd= { .coef = 0, .exp = 0, .next = NULL };
	Polynom headmultiply = { .coef = 0, .exp = 0, .next = NULL };
	read_from_file(&head1, &head2);

	printf("Polinom 1:\n");
	print(&head1);
	printf("\n\nPolinom 2:\n");
	print(&head2);

	printf("\n\nZbrojeni polinomi:\n");
	add(&headadd, &head1, &head2);
	print(&headadd);

	printf("\n\nPomnozeni polinomi:\n");
	multiply(&headmultiply, &head1, &head2);
	print(&headmultiply);
	printf("\n");

	return 0;
}

//funkcija za citanje iz filea
int read_from_file(Position head1, Position head2) {
	FILE* filepointer;
	int coef, exp, counter=0;
	char newline = "0";
	filepointer = fopen("polynoms.txt", "r");
	if (!filepointer) {
		printf("MISTAKE!(filepointer");
		return 0;
	}
	while (fscanf(filepointer, "%dx^%d", &coef, &exp) == 2) {
		Insert_sorted(head1, coef, exp);
		fscanf(filepointer, "%c", &newline);
		if (newline == '\n') {
			break;
		}
	}
	while (fscanf(filepointer, "%dx^%d", &coef, &exp) == 2) {
		Insert_sorted(head2, coef, exp);
		fscanf(filepointer, "%c", &newline);
		if (newline == '\n') {
			break;
		}
	}
	
	return 0;
}

//funkcija za stvaranje novog polinoma
Position create_poly(int coef, int exp) {
	Position newPolynom;
	newPolynom = (Position)malloc(sizeof(Polynom));
	if (!newPolynom) {
		printf("MISTAKE(newPolynom!");
		return NULL;
	}
	newPolynom->coef = coef;
	newPolynom->exp = exp;
	newPolynom->next = NULL;

	return newPolynom;
}

//funkcija za sortiranje i stvaranje liste
int Insert_sorted(Position head, int coef, int exp) {
	Position newPolynom;
	Position temp = head;
	newPolynom = create_poly(coef, exp);
	if (head->next == NULL) {
		head->next = newPolynom;
		newPolynom->next = NULL;
		return 0;
	}
	while (temp->next != NULL && temp->next->exp > newPolynom->exp) {
		temp = temp->next;
	}
	if (temp->next == NULL || temp->next->exp != newPolynom->exp ) {
		newPolynom->next = temp->next;
		temp->next = newPolynom;
		return 0;
	}
	else if (newPolynom->exp == temp->next->exp) {
		temp->next->coef = temp->next->coef + newPolynom->coef;
		return 0;
	}
	return 0;
}

//funkcija za printanje liste
int print(Position head) {
	Position temp = head->next;
	if (head->next == NULL) {
		printf("EMPTY LIST!!(print)");
		return 0;
	}
	while (temp != NULL) {
		printf("%dx^%d\t", temp->coef, temp->exp);
		temp = temp->next;
	}
}

//funkcija za zbrajanje polinoma
int add(Position head, Position head1, Position head2) {
	Position temp1 = head1->next;
	Position temp2 = head2->next;
	if (head1->next == NULL && head2->next == NULL) {
		printf("Empty lists!!");
		return 0;
	}
	while (temp1 != NULL) {
		Insert_sorted(head, temp1->coef, temp1->exp);
		temp1=temp1->next;
	}
	while (temp2 != NULL) {
		Insert_sorted(head, temp2->coef, temp2->exp);
		temp2 = temp2->next;
	}
	return 0;
}

//funkcija za mnozenje polinoma
int multiply(Position head, Position head1, Position head2) {
	Position temp1 = head1->next;
	Position temp2 = head2->next;
	if (head1->next == NULL && head2->next == NULL) {
		printf("Empty lists!!");
		return 0;
	}
	while (temp1 != NULL) {
		while (temp2 != NULL) {
			Insert_sorted(head, temp1->coef * temp2->coef, temp1->exp + temp2->exp);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	return 0;
}