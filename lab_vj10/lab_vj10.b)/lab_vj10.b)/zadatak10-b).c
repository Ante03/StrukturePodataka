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
    Positiongrad next;
} grad;

//struktura drzave
struct _Drzava;
typedef struct _Drzava* Positiondrz;
typedef struct _Drzava {
    char ime[50];
    Positiondrz left;
    Positiondrz right;
    Positiongrad stanovnik;
} drzava;

//inicijalizacija funkcija
int read_f_f_drz(Positiondrz headDrz);
Positiondrz add_to_tree_drz(Positiondrz headDrz, char* country_name, char* country_file);
Positiondrz create_drz(char* country_name);
Positiongrad read_f_f_grad(char* country_file);
Positiongrad add_to_list_grad(Positiongrad headGrad, char* city_name, int num_stan);
Positiongrad create_city(char* city_name, int num_stan);
int print_drz(Positiondrz headDrz);
Positiondrz select_country(Positiondrz headDrz, char* country_name);
int find_drzave(Positiondrz headDrz);


int main() {
    drzava headDrz = { .ime = {0}, .left = NULL, .right = NULL, .stanovnik = NULL };
    read_f_f_drz(&headDrz);

    find_drzave(&headDrz);

    return 0;
}


//funkcija za citanje filea
int read_f_f_drz(Positiondrz headDrz) {
    char country_name[50], country_file[50];
    FILE* filepointer;
    filepointer = fopen("drzave.txt", "r");
    if (!filepointer) {
        printf("Filepointer didnt opened");
        return 0;
    }
    while (!feof(filepointer)) {
        fscanf(filepointer, "%s %s", country_name, country_file);
        headDrz = add_to_tree_drz(headDrz, country_name, country_file);
    }
    print_drz(headDrz);

    fclose(filepointer);

    return 0;
}

//funkcija za dodavanje u stablo
Positiondrz add_to_tree_drz(Positiondrz headDrz, char* country_name, char* country_file) {
    Positiondrz new_drz;
    new_drz = create_drz(country_name);
    new_drz->stanovnik = read_f_f_grad(country_file);
    if (headDrz == NULL) {
        headDrz = new_drz;
        return headDrz;
    }
    if (strcmp(headDrz->ime, new_drz->ime) > 0) {
        headDrz->left = add_to_tree_drz(headDrz->left, country_name, country_file);
    }
    else {
        headDrz->right = add_to_tree_drz(headDrz->right, country_name, country_file);
    }
    return headDrz;
}

//funkcija za stvaranje drzave
Positiondrz create_drz(char* country_name) {
    Positiondrz new_drz = NULL;
    new_drz = (Positiondrz)malloc(sizeof(drzava));
    if (!new_drz) {
        printf("New_drz MISTAKE!");
        return NULL;
    }
    strcpy(new_drz->ime, country_name);
    new_drz->left = NULL;
    new_drz->right = NULL;
    new_drz->stanovnik = NULL;
    
    return new_drz;
}

//funkcija za citanje gradova
Positiongrad read_f_f_grad(char* country_file) {
    Positiongrad headGrad = NULL;
    char city_name[50];
    int num_stan = 0;
    FILE* filepointer;
    filepointer = fopen(country_file, "r");
    if (!filepointer) {
        printf("Filepointer Mistake");
        return NULL;
    }
    while (!feof(filepointer)) {
        fscanf(filepointer, "%s %d", city_name, &num_stan);
        headGrad = add_to_list_grad(headGrad, city_name, num_stan);
    }

    fclose(filepointer);
    return headGrad;
}

//funkcija za dodavanje gradova u listu
Positiongrad add_to_list_grad(Positiongrad headGrad, char* city_name, int num_stan) {
    Positiongrad new_grad = NULL;
    Positiongrad temp = headGrad;
    Positiongrad prev = headGrad;
    new_grad = create_city(city_name, num_stan);
    if (headGrad == NULL) {
        headGrad = new_grad;
        return headGrad;
    }
    if (headGrad->next == NULL) {
        if (headGrad->value > new_grad->value) {
            headGrad->next = new_grad;
            return headGrad;
        }
        headGrad = new_grad;
        new_grad->next = temp;

        return headGrad;
    }
    while (temp != NULL) {
        if (temp->value < new_grad->value) {
            if (temp == prev) {
                headGrad = new_grad;
                new_grad->next = temp;

                return headGrad;
            }
            prev->next = new_grad;
            new_grad->next = temp;

            return headGrad;
        }
        prev = temp;
        temp = temp->next;
    }
    prev->next = new_grad;

    return headGrad;
}

//funkcija za stvaranje novog grada
Positiongrad create_city(char* city_name, int num_stan) {
    Positiongrad new_grad = NULL;
    new_grad = (Positiongrad)malloc(sizeof(grad));
    if (!new_grad) {
        printf("New_grad MISTAKE");
        return NULL;
    }
    strcpy(new_grad->ime, city_name);
    new_grad->value = num_stan;
    new_grad->next = NULL;

    return new_grad;
}

//funkcija za printanje drzava
int print_drz(Positiondrz headDrz) {
    if (headDrz) {
        print_drz(headDrz->left);
        printf("\n%s\n", headDrz->ime);
        Positiongrad temp = headDrz->stanovnik;
        while (temp != NULL) {
            printf("%s %d\n", temp->ime, temp->value);
            temp = temp->next;
        }
        print_drz(headDrz->right);
    }
    return 0;
}

//funkcija za pronalazenje drzave
int find_drzave(Positiondrz headDrz) {
    char country_name[50];
    Positiondrz drz;
    int min_num = 0;
    printf("Unesite ime drzave: ");
    scanf("%s", country_name);
    printf("Unsite min broj stanovnika: ");
    scanf("%d", &min_num);
    drz = select_country(headDrz, country_name);
    printf("Vasa drzava je %s, njezini gradovi su: ", drz->ime);
    Positiongrad temp = drz->stanovnik;
    while (temp != NULL) {
        if (temp->value > min_num) {
            printf("\n%s %d", temp->ime, temp->value);
        }
        temp = temp->next;
    }
    return 0;
}

//funkcija za odabir konkretne drzave
Positiondrz select_country(Positiondrz headDrz, char* country_name) {
    if (strcmp(headDrz->ime, country_name) > 0) {
        return select_country(headDrz->left, country_name);
    }
    if (strcmp(headDrz->ime, country_name) < 0) {
        return select_country(headDrz->right, country_name);
    }
    if (strcmp(headDrz->ime, country_name) == 0) {
        return headDrz;
    }
    return NULL;
}