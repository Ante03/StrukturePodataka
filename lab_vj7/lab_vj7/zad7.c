#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory {
    char name[MAX_NAME_LENGTH];
    PositionDirectory subDirectories;
    PositionDirectory next;
} Directory;

struct _levelStack;
typedef struct _levelStack* PositionLevelStack;
typedef struct _levelStack {
    PositionDirectory directoryLevel;
    PositionLevelStack next;
} LevelStack;

//inicijaliziranje funkcija
PositionDirectory create_New(char name[50]);
int createSubDir(PositionDirectory head);
PositionDirectory change_dir(PositionDirectory current);
int push(PositionLevelStack head, PositionDirectory current);
PositionLevelStack create_levelstack(PositionDirectory current);
PositionDirectory pop(PositionLevelStack headLevelStack);
int print(PositionDirectory current);


//main funkcija
int main() {
    Directory head = { .name = {0}, .subDirectories = NULL, .next = NULL };
    PositionDirectory root = create_New("C:");
    PositionDirectory currentDir = root;

    LevelStack headlevelstack = { .directoryLevel = NULL, .next = NULL };
    push(&headlevelstack, currentDir);

    while (1) {
        printf("Menu:\n");
        printf("1 - Create directory\n");
        printf("2 - Change directory\n");
        printf("3 - Go up\n");
        printf("4 - Print directory\n");
        printf("5 - exit\n");

        int choice = 0;
        scanf("%d", &choice);

        if (choice == 1) {
            createSubDir(currentDir);
        }
        else if (choice == 2) {
            currentDir = change_dir(currentDir);
            push(&headlevelstack, currentDir);
        }
        else if (choice == 3) {
            if (currentDir != root) {
                currentDir = pop(&headlevelstack);
                printf("\nCurrently in %s\n", currentDir->name);
            }
            else {
                printf("\nAlready in root directory\n");
            }
        }
        else if (choice == 4) {
            print(currentDir);
        }
        else if (choice == 5) {
            printf("\nClosing program!");
            break;
        }
        else {
            printf("You enterd wrong number");
        }
    }
    return 0;
}

//funkcija za stvaranje novog elementa
PositionDirectory create_New(char name[50]) {
    PositionDirectory newel;
    newel = (PositionDirectory)malloc(sizeof(Directory));
    if (!newel) {
        printf("NEWEL MISTAKE!");
        return NULL;
    }
    strcpy(newel->name, name);
    newel->next = NULL;
    newel->subDirectories = NULL;

    return newel;
}

//funkcija za pravljenje poddirektorija
int createSubDir(PositionDirectory head) {
    char name[50];
    PositionDirectory newSub;
    printf("Enter name of subdirectory: ");
    scanf("%s", name);
    newSub = create_New(name);
    if (!newSub) {
        printf("\nnewSub mistake!\n");
        return 0;
    }
    newSub->next = head->subDirectories;
    head->subDirectories = newSub;

    return 0;
}

//funkcija za promjenu direktorija
PositionDirectory change_dir(PositionDirectory current) {
    char name[50];
    PositionDirectory sub = current->subDirectories;
    printf("Enter name of directory: ");
    scanf("%s", name);
    
    while (sub!=NULL) {
        if (strcmp(name, sub->name) == 0) {
            return sub;
        }
        sub = sub->next;
    }
    printf("\nNije pronadeno\n");
    return current;
}

//funkcija za pushanje na stock
int push(PositionLevelStack head, PositionDirectory current) {
    PositionLevelStack Newel=NULL;
    PositionLevelStack temp=head;
    Newel = create_levelstack(current);
    Newel->next = head->next;
    head->next = Newel;

    return 0;
}

//funkcija za stvaranje novog elementa stacka
PositionLevelStack create_levelstack(PositionDirectory current) {
    PositionLevelStack Newel;
    Newel = (PositionLevelStack)malloc(sizeof(LevelStack));
    if (!Newel) {
        printf("create level stack mistake!");
        return NULL;
    }
    Newel->directoryLevel = current;
    Newel->next = NULL;

    return Newel;
}

//funkcija za skidanje sa stoga
PositionDirectory pop(PositionLevelStack headLevelStack) {
    PositionDirectory dirlev = NULL;
    PositionLevelStack todel = headLevelStack->next;

    if (todel == NULL) {
        printf("Stack empty!");
        return NULL;
    }
    headLevelStack->next = todel->next;
    dirlev = todel->directoryLevel;
    free(todel);

    return dirlev;
}

//funkcija za printanje liste
int print(PositionDirectory current) {
    PositionDirectory sub = current->subDirectories;

    if (current->subDirectories == NULL) {
        printf("Empty directory!");
        return 0;
    }
    while (sub != NULL) {
        printf("%s\n", sub->name);
        sub = sub->next;
    }
    return 0;
}