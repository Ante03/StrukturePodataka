//Napisati program koji cita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država.Uz
//ime drzave u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
//države.Svaka datoteka koja predstavlja drzavu sadrzi popis gradova u formatu naziv_grada,
//broj_stanovnika.
//a) Potrebno je formirati sortiranu vezanu listu drzava po nazivu.Svaki cvor vezane liste
//sadrzi stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
//b) Potrebno je formirati stablo drzava sortirano po nazivu.Svaki cvor stabla sadrzi vezanu
//listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
//Nakon formiranja podataka potrebno je ispisati drzave i gradove te omoguciti korisniku putem
//tastature pretragu gradova odredene drzave koji imaju broj stanovnika ve?i od unosa na
//tastaturi.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//struktura grada
struct _Grad;
typedef struct _Grad* Positiongrad;
typedef struct _Grad {
    int value;
    char ime[500];
    Positiongrad left;
    Positiongrad right;
} grad;

//struktura drzave
struct _Drzava;
typedef struct _Drzava* Positiondrz;
typedef struct _Drzava {
    char ime[50];
    Positiondrz next;
    Positiongrad stanovnik;
} drzava;

//inicijalizacija funkcija
int read_from_file_drzave(Positiondrz headDrz);
int add_to_list_drz(Positiondrz headDrz, char* country_name, char* country_file);
Positiondrz create_drz(char* country_name);
int print_drz(Positiondrz headDrz);
Positiongrad create_tree_grad(char* country_file);
Positiongrad add_to_tree(Positiongrad headGrad, char* city_name, int num_stan);
Positiongrad create_city(char* city_name, int num_stan);
int find_drz(Positiondrz headDrz);
int inorder_min(Positiongrad headGrad, int min_num);

int main() {
    drzava headDrz = { .ime = {0}, .next = NULL, .stanovnik = NULL };
    //read_from_file_drzave(&headDrz);
    read_from_file_drzave(&headDrz);

    find_drz(&headDrz);

    return 0;
}


//funkcija za citanje iz filea drzave.txt
int read_from_file_drzave(Positiondrz headDrz) {
    char country_name[50], country_file[50];
    FILE* filepointer;
    filepointer = fopen("drzave.txt", "r");
    if (!filepointer) {
        printf("Filepointer mistake");
        return 0;
    }
    while (!feof(filepointer)) {
        fscanf(filepointer, "%s %s", country_name, country_file);
        add_to_list_drz(headDrz, country_name, country_file);
    }

    print_drz(headDrz);

    fclose(filepointer);
    return 0;
}

//funkcija za dodavanje strukture u vezanu listu
int add_to_list_drz(Positiondrz headDrz, char* country_name, char* country_file) {
    Positiondrz new_drz = NULL;
    Positiondrz temp = headDrz->next;
    Positiondrz prev = headDrz->next;
    new_drz = create_drz(country_name);
    new_drz->stanovnik = create_tree_grad(country_file);
    if (!new_drz) {
        printf("New_drz MISTAKE");
        return 0;
    }
    if (headDrz->next == NULL) {
        headDrz->next = new_drz;
        return 0;
    }
    if (temp->next == NULL) {
        if (strcmp(temp->ime, country_name) == 1) {
            headDrz->next = new_drz;
            new_drz->next = temp;
            return 0;
        }
        temp->next = new_drz;

        return 0;
    }
    while (temp != NULL) {
        if (strcmp(temp->ime, country_name) == 1) {
            if (temp == prev) {
                headDrz->next = new_drz;
                new_drz->next = temp;
                return 0;
            }
            prev->next = new_drz;
            new_drz->next = temp;
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }

    prev->next = new_drz;
    return 0;
}

//funkcija za stvaranje strukture drzave
Positiondrz create_drz(char* country_name) {
    Positiondrz new_drz = NULL;
    new_drz = (Positiondrz)malloc(sizeof(drzava));
    if (!new_drz) {
        printf("New_drz MISTAKE!");
        return NULL;
    }
    strcpy(new_drz->ime, country_name);
    new_drz->next = NULL;
    new_drz->stanovnik = NULL;

    return new_drz;
}

//funkcija za printanje drzava
int print_drz(Positiondrz headDrz) {

    Positiondrz temp = headDrz;
    if (!headDrz) {
        printf("EMPTY LIST!");
        return 0;
    }

    while (temp->next != NULL) {
        printf("\n%s\n", temp->ime);
        inorder(temp->stanovnik);
        temp = temp->next;
    }
    printf("\n%s\n", temp->ime);
    inorder(temp->stanovnik);

    return 0;
}

//funkcija za stvaranje stabla grada
Positiongrad create_tree_grad(char* country_file) {
    char city_name[50];
    int numstan = 0;
    Positiongrad headGrad = NULL;
    FILE* filepointer;
    filepointer = fopen(country_file, "r");
    if (!filepointer) {
        printf("Filepointer didnt opened");
        return NULL;
    }
    while (!feof(filepointer)) {
        fscanf(filepointer, "%s %d", city_name, &numstan);
        headGrad = add_to_tree(headGrad, city_name, numstan);
    }
    return headGrad;
}

//funkcija za stvaranje grada
Positiongrad add_to_tree(Positiongrad headGrad, char* city_name, int num_stan) {
    Positiongrad new_city = NULL;
    new_city = create_city(city_name, num_stan);
    if (headGrad == NULL) {
        headGrad = new_city;
        return headGrad;
    }
    if (headGrad->value > new_city->value) {
        headGrad->left = add_to_tree(headGrad->left, city_name, num_stan);
    }
    else {
        headGrad->right = add_to_tree(headGrad->right, city_name, num_stan);
    }
    return headGrad;
}

//funkcija za stvaranje grada
Positiongrad create_city(char* city_name, int num_stan) {
    Positiongrad new_city = NULL;
    new_city = (Positiongrad)malloc(sizeof(grad));
    if (!new_city) {
        printf("New city MISTAKE!");
        return NULL;
    }
    strcpy(new_city->ime, city_name);
    new_city->value = num_stan;
    new_city->left = NULL;
    new_city->right = NULL;

    return new_city;
}

//funkcija za printanje gradova
int inorder(Positiongrad headGrad) {
    if (headGrad) {
        inorder(headGrad->left);
        printf("%s %d\n", headGrad->ime, headGrad->value);
        inorder(headGrad->right);
    }
    return 0;
}

//funkcija za pronalazak drzava i gradova
int find_drz(Positiondrz headDrz) {
    char country_name[50];
    int min_num;
    printf("\nEnter name of country: ");
    scanf("%s", country_name);
    printf("\nEnter min number of citizen: ");
    scanf("%d", &min_num);
    while (headDrz != NULL) {
        if (strcmp(headDrz->ime, country_name) == 0) {
            break;
        }
        headDrz = headDrz->next;
    }
    printf("Vasa drzava je %s, njezini gradovi veci od %d stanovnika su: \n", headDrz->ime, min_num);
    inorder_min(headDrz->stanovnik, min_num);

    return 0;
}

//funkcija inorder za ispis
//veci od minimalnog br stanovnika
int inorder_min(Positiongrad headGrad, int min_num) {

    if (headGrad) {
        inorder_min(headGrad->left, min_num);
        if (headGrad->value > min_num) {
            printf("%s \t %d\n", headGrad->ime, headGrad->value);
        }
        inorder_min(headGrad->right, min_num);
    }

    return 0;
}
