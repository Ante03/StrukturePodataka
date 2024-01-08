#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//struktura za binarno stablo
struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

//inicijalizacija funckija
Position add_new_mem(Position head, int value);
Position create_New(int value);
int replace(Position root);
int inorder(Position root);
int random();


int main() {

    Position root = NULL;
    root = add_new_mem(root, 2);
    Position rootR = NULL;
    int i = 0;
    srand(time(0));

    add_new_mem(root, 5);
    add_new_mem(root, 7);
    add_new_mem(root, 8);
    add_new_mem(root, 11);
    add_new_mem(root, 1);
    add_new_mem(root, 4);
    add_new_mem(root, 2);
    add_new_mem(root, 3);
    add_new_mem(root, 7);
    inorder(root);
    printf("\n");
    replace(root);
    inorder(root);
    printf("\n");
    rootR = add_new_mem(rootR, random());
    for (i = 0; i < 10; i++) {
        add_new_mem(rootR, random());
    }
    inorder(rootR);
    printf("\n");

    return 0;
}

//funkcija za stvaranje novog clana
Position create_New(int value) {
    Position NewEl = NULL;
    NewEl = (Position)malloc(sizeof(Node));
    if (!NewEl) {
        printf("NewEl MISTAKE!!!");
        return NULL;
    }
    NewEl->value = value;
    NewEl->left = NULL;
    NewEl->right = NULL;

    return NewEl;
}

//funkcija za dodavanje novog clana u stablo
Position add_new_mem(Position head, int value) {
    if (head == NULL) {
        return create_New(value);
    }

    if (value < head->value) {
        head->left = add_new_mem(head->left, value);
    }
    else if (value >= head->value) {
        head->right = add_new_mem(head->right, value);
    }
    return head;
}

//funkcija za zamjenu clanova
int replace(Position root) {
    if (root == NULL) {
        return 0;
    }
    int lv = 0, rv = 0;
    lv = replace(root->left);
    rv = replace(root->right);

    int realr = root->value;
    root->value = lv + rv;

    return root->value + realr;
}

//funkcija za ispis inorder,
//dodana samo zbog provjere
int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return 0;
}

//funkcija za random broj
//izmedu 10 i 90
int random(){
    int a = 0;
    a = rand() % 81 + 10;
    return a;
}
