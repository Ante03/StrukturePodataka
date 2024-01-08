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

//struktura za spremanje za lvl order
struct _number;
typedef struct _number* Positionn;
typedef struct _number {
    Position node;
    Positionn next;
} Number;

//inicijalizacija funkcija
Position add_new_mem(Position head, int value);
Position create_New(int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root, Positionn head);
Position find(Position root, int value);
int delete(Position root, int value);
Positionn create_number(Position node);
int add_number(Positionn head, Position node);

int main() {
    Number head = { .node = NULL, .next = NULL };



    Position root = NULL;
    root = add_new_mem(root, 7);

    while (1) {
        printf("Menu:\n");
        printf("1 - Add new member\n");
        printf("2 - Print inorder\n");
        printf("3 - Print preorder\n");
        printf("4 - Print level order\n");
        printf("5 - Find member\n");
        printf("6 - Delete member\n");
        printf("7 - exit\n");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            int value = 0;
            printf("\nEnter value:");
            scanf("%d", &value);
            add_new_mem(root, value);
        }
        else if (choice == 2) {
            inorder(root);
        }
        else if (choice == 3) {
            preorder(root);
        }
        else if (choice == 4) {
            levelOrder(root, &head);
        }
        else if (choice == 5) {
            printf("Which value you want to find: ");
            int value = 0;
            scanf("%d", &value);
            find(root, value);
        }
        else if (choice == 6) {
            printf("Which value you want to delete: ");
            int value = 0;
            scanf("%d", &value);
            delete(root, value);
        }
        else if (choice == 7) {
            printf("Closing program");
            break;
        }
        else {
            printf("Value out of range [1,7]");
        }
    }
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

//funkcija za ispis inorder
int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return 0;
}

//funkcija za ispis preorder
int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        inorder(root->left);
        inorder(root->right);
    }
    return 0;
}

//funkcija za ispis postorder
int postorder(Position root) {
    if (root) {
        inorder(root->left);
        inorder(root->right);
        printf("%d ", root->value);
    }
    return 0;
}

//funkcija za ispis level order sa vezanom listom
int levelOrder(Position root, Positionn head) {
    int front = 0, rear = 1;
    if (root == NULL) {
        return 0;
    }
    add_number(head, root);
    
    Positionn temp = head;
    while (front < rear && temp->next != NULL) {
        temp = temp->next;
        Position current = temp->node;
        front++;

        if (current->left != NULL) {
            add_number(head, current->left);
            rear++;
        }
        if (current->right != NULL) {
            add_number(head, current->right);
            rear++;
        }
    }
    temp = head->next;
    while (temp != NULL) {
        printf("%d ", temp->node->value);
        temp = temp->next;
    }
    return 0;
}

//funkcija za pronalazenje
//nekog elementa
Position find(Position root, int value) {
    if (root->value == value) {
        printf("\nPronadena vrijednost %d!\n", root->value);
        return root;
    }
    if (value<root->value) {
        find(root->left, value);
    }
    else if (value>=root->value) {
        find(root->right, value);
    }
    else
        printf("Nije pronadena vrijednost");
    return NULL;
}

//funkcija za brisanje clana
int delete(Position todelete, int value) {
    if (todelete == NULL) {
        printf("Empty list!");
        return 0;
    }
    if (value < todelete->value) {
        delete(todelete->left, value);
    }
    else  if (value > todelete->value) {
        delete(todelete->right, value);
    }
    else {
        if (todelete->left == NULL && todelete->right == NULL) {
            printf("\nVrijednost %d je izbrisana!\n", todelete->value);
            free(todelete);
            return 0;
        }
        else if (todelete->left != NULL && todelete->right == NULL) {
            Position temp = todelete;
            todelete = todelete->left;
            free(temp);
            return 0;
        }
        else if (todelete->left == NULL && todelete->right != NULL) {
            Position temp = todelete;
            todelete = todelete->right;
            free(temp);
            return 0;
        }
        Position temp = todelete->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        printf("\nIzbrisana vrijednost %d\n", todelete->value);
        todelete->value = temp->value;
        delete(todelete->right, temp->value);
    }
    return 0;
}

//funkcija za dodavanje u number strukturu
int add_number(Positionn head, Position node) {
    Positionn new_num = NULL;
    new_num = create_number(node);
    if (head->next == NULL) {
        head->next = new_num;
        return 0;
    }
    Positionn temp = head->next;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_num;

    return 0;
}

//funkcija za stvaranje novog clana number strukture
Positionn create_number(Position node) {
    Positionn new_num = NULL;
    new_num = (Positionn)malloc(sizeof(Number));
    if (!new_num) {
        return NULL;
    }
    new_num->node = node;
    new_num->next = NULL;

    return new_num;
}