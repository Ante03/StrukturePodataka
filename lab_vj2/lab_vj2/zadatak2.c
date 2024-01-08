#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[10];
	char surname[10];
	int b_year;
	Position next;
} Person;


//deklaracija funkcija
Position create_person();
int add_at_begining(Position head);
int print(Position head);
int add_at_end(Position head);
int find_element(Position head);
int delete(Position head);
int add_before(Position head);
int add_after(Position head);
int sort(Position head);
int write_in_file(Position head);
int read_from_file(Position head);
int num_lines();
Position create_person_r_f_f(char name[10], char surname[10], int b_year);

int main()
{
	Person head = { .name = NULL, .surname = NULL, .b_year = 0, .next = NULL };
	int choice = 0;
	while (1) {
		printf("Menu: \n");
		printf("1  - add at begining\n");
		printf("2  - print list \n");
		printf("3  - add at end\n");
		printf("4  - find person(by surname) \n");
		printf("5  - delete element(by surname)\n");
		printf("6  - add before(by surname)\n");
		printf("7  - add after(by surname)\n");
		printf("8  - sort(by surname)\n");
		printf("9  - write in file\n");
		printf("10 - read from file\n");
		printf("11 - exit\n");
		scanf("%d", &choice);
		if (choice == 1) {
			add_at_begining(&head);
		}
		else if (choice == 2) {
			print(&head);
		}
		else if (choice == 3) {
			add_at_end(&head);
		}
		else if (choice == 4) {
			find_element(&head);
		}
		else if (choice == 5) {
			delete(&head);
		}
		else if (choice == 6) {
			add_before(&head);
		}
		else if (choice == 7) {
			add_after(&head);
		}
		else if (choice == 8) {
			sort(&head);
		}
		else if (choice == 9) {
			write_in_file(&head);
		}
		else if (choice == 10) {
			read_from_file(&head);
		}
		else if (choice == 11) {
			printf("Exit sucessfully");
			return 0;
		}
	}
	return 0;
}

//funkcija za stvaranje osobe
Position create_person() {
	Position newPerson;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("MISTAKE(newperson!!!");
		return NULL;
	}

	printf("\nEnter name: ");
	scanf("%s", newPerson->name);
	printf("Enter surname: ");
	scanf("%s", newPerson->surname);
	printf("Enter birth year: ");
	scanf("%d", &newPerson->b_year);
	newPerson->next = NULL;

	return newPerson;
}

//funkcija za dodavanje na pocetak
int add_at_begining(Position head) {
	Position newPerson=NULL;
	
	newPerson = create_person();
	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

//funkcija za printanje
int print(Position head) {
	Position temp = head->next;
	if (temp == NULL) {
		printf("Empty list!");
		return 0;
	}
	printf("Name\tSurname\tBirth year\n");
	while (temp != NULL) {
		printf("%s\t%s\t%d\n", temp->name, temp->surname, temp->b_year);
		temp = temp->next;
	}
	return 0;
}

//funkcija za dodavanje na kraj
int add_at_end(Position head) {
	Position newPerson = NULL;
	Position temp=NULL;
	newPerson = create_person();
	if (head->next == NULL) {
		newPerson->next = head->next;
		head->next = newPerson;
		return 0;
	}

	temp = head->next;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newPerson;

	return 0;
}

//funkcija za pronalazenje elementa po prezimenu
int find_element(Position head) {
	char surn[10];
	Position temp = head->next;

	if (head->next == NULL) {
		printf("Empty list!!");
		return 0;
	}

	printf("\nEnter surname of person you want to find: ");
	scanf("%s", surn);

	while (temp != NULL) {
		if (strcmp(surn, temp->surname) == 0) {
			printf("\nPerson found:\n");
			printf("%s\t %s\t %d\n", temp->name, temp->surname, temp->b_year);
			return 0;
		}
		temp = temp->next;
	}
	return 0;
}

//funkcija za brisanje elementa po prezimenu
int delete(Position head) {
	char surn[10];
	Position temp = head->next;
	Position previous = head->next;

	if (head->next == NULL) {
		printf("Empty list!!");
		return 0;
	}

	printf("\nEnter surname of person you want to delete: ");
	scanf("%s", surn);

	while (temp != NULL) {
		if (strcmp(surn, temp->surname) == 0) {
			if (temp->next == previous->next) {
				head->next = temp->next;
				free(temp);
				return 0;
			}
			else if (temp->next == NULL) {
				previous->next = NULL;
				free(temp);
				return 0;
			}
			else {
				previous->next = temp->next;
				free(temp);
				return 0;
			}
		}
		previous = temp;
		temp = temp->next;
	}
	return 0;
}

//funkcija za dodavanje ispred nekog clana
int add_before(Position head) {
	char surn[10];
	Position newper;
	Position temp = head->next;
	Position previous = head->next;

	if (head->next == NULL) {
		printf("Empty list!!");
		return 0;
	}
	newper = create_person();

	printf("\nEnter surname(add before): ");
	scanf("%s", surn);

	while (temp != NULL) {
		if (strcmp(surn, temp->surname) == 0) {
			if (temp->next == previous->next) {
				newper->next = head->next;
				head->next = newper;
				return 0;
			}
			else{
				newper->next = previous->next;
				previous->next = newper;
				return 0;
			}
		}
		previous = temp;
		temp = temp->next;
	}
	return 0;
}

//funkcija za dodavanje iza nekog clana
int add_after(Position head) {
	char surn[10];
	Position newper;
	Position temp = head->next;

	if (head->next == NULL) {
		printf("Empty list!!");
		return 0;
	}
	newper = create_person();

	printf("\nEnter surname(add after): ");
	scanf("%s", surn);

	while (temp != NULL) {
		if (strcmp(surn, temp->surname) == 0) {
			newper->next = temp->next;
			temp->next = newper;
			return 0;
		}
		temp = temp->next;
	}
	return 0;
}

//funkcija za sortiranje
int sort(Position head) {
	Position temp = head->next;
	Position previous = head->next;
	Position current;
	Position tmp, pre;
	if (head->next == NULL) {
		printf("Empty list!!");
		return 0;
	}
	while (temp->next != NULL) {
		if ((strcmp(temp->surname, temp->next->surname) > 0) && previous->next == temp->next) {
			current = temp->next;
			tmp = temp;
			head->next = current;
			tmp->next = current->next;
			current->next = tmp;
			temp = head->next;
			previous = head->next;
		}
		else if ((strcmp(temp->surname, temp->next->surname) > 0) && previous->next != temp->next) {
			current = temp->next;
			pre = previous;
			tmp = temp;
			pre->next = current;
			tmp->next = current->next;
			current->next = tmp;
			temp = head->next;
			previous = head->next;
		}
		else {
			previous = temp;
			temp = temp->next;
		}

	}
	return 0;
}

//funkcija za upisivanje u datoteku
int write_in_file(Position head) {
	Position temp = head->next;
	FILE* filepointer;
	filepointer = fopen("osoba.txt", "w");
	if (!filepointer) {
		printf("MISTAKE(filepointer)");
		return 0;
	}
	while (temp != NULL) {
		fprintf(filepointer, "%s %s %d\n", temp->name, temp->surname, temp->b_year);
		temp = temp->next;
	}
	printf("Write in file succeded\n");
	fclose(filepointer);
	 
	return 0;
}

//funkcija za citanje iz filea
int read_from_file(Position head) {
	char name[10], surname[10];
	int b_year;
	Position temp = NULL;
	Position previous = head->next;
	int counter = 0, i;
	FILE* filepointer;
	filepointer = fopen("osobatxt.txt", "r");
	if (!filepointer) {
		printf("MISTAKE(filepointer)");
		return 0;
	}
	counter = num_lines();
	for (i = 0; i < counter; i++) {
		fscanf(filepointer, "%s", name);
		fscanf(filepointer, "%s", surname);
		fscanf(filepointer, "%d", &b_year);
		temp = create_person_r_f_f(name, surname, b_year);
		temp->next = head->next;
		head->next = temp;
	}

	return 0;
}

//funkcija za brojanje redaka u datoteci
int num_lines() {
	char name[10], surname[10];
	int counter = 0;
	int bod;

	//otvaranje datoteke
	FILE* filepointer = NULL;
	filepointer = fopen("osobatxt.txt", "r");
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

//funkcija za stvaranje nove osobe
Position create_person_r_f_f(char name[10],char surname[10], int b_year) {
	Position newPerson;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("MISTAKE(newperson!!!");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->b_year = b_year;
	newPerson->next = NULL;

	return newPerson;
}