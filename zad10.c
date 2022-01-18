#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 50

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    char ime_grada[MAX_NAME];
    int broj_stanovnika;
    Position left;
    Position right;
}tree;

struct _drzava;
typedef struct _drzava* PositionList;
typedef struct _drzava {
    char ime_drzave[MAX_NAME];
    Position grad;
    PositionList next;
}drzava;

int UnesiUListuIzDatoteke(PositionList head, char* imedatoteke);
int UnesiUStabloIzDatoteke(PositionList ime_drzave, char* imedatoteke);
int SortiraniUnosUListu(PositionList head, PositionList newPerson);
int UmetniIza(PositionList head, PositionList NewEl);
PositionList NapraviElementListe(char* ime_drzave);
int IspisListe(PositionList first);
int IspisStabla(Position curr);
Position SortiraniUnosUStablo(Position curr, Position NewEl);
Position NapraviElementStabla(char* ime_grada, int broj_stanovnika);

int main() {

    drzava lstDrzava = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PositionList listaDrzava = &lstDrzava;

    char imedatoteke[] = "drzave.txt";
    UnesiUListuIzDatoteke(listaDrzava, imedatoteke);
    IspisListe(listaDrzava);

    return 1;

}


int UnesiUListuIzDatoteke(PositionList head, char* imedatoteke) {

    FILE* f = NULL;
    f = fopen(imedatoteke, "r");
    char ime_drzave[MAX_NAME] = { 0 };
    char buffer[MAX_NAME] = { 0 };
    char grad[MAX_NAME] = { 0 };

    drzava t = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PositionList temp = &t;

    if (!f) {
        printf("Datoteka ne postoji.\n");
        return -1;
    }

    while (!feof(f)) {

        fscanf(f, "%s %s\n", ime_drzave, grad);
        temp = NapraviElementListe(ime_drzave);

        UnesiUStabloIzDatoteke(temp, grad);

        SortiraniUnosUListu(head, temp);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int UnesiUStabloIzDatoteke(PositionList ime_drzave, char* imedatoteke) {
    FILE* f = NULL;
    f = fopen(imedatoteke, "r");

    char ime_grada[MAX_NAME] = { 0 };
    int broj_stanovnika = 0;

    if (!f) {
        perror("File is invalid\n");
        return -1;
    }

    while (!feof(f)) {
        fscanf(f, "%s %d", ime_grada, &broj_stanovnika);
        Position temp = NapraviElementStabla(ime_grada, broj_stanovnika);
        ime_drzave->grad = SortiraniUnosUStablo(ime_drzave->grad, temp);
    }

    fclose(f);

    return EXIT_SUCCESS;

}

int SortiraniUnosUListu(PositionList head, PositionList NewEl) {

    PositionList temp = NULL;
    temp = head->next;

    while (temp != NULL && strcmp(temp->ime_drzave, NewEl->ime_drzave) > 0) { //ne triba next isprid temp!!
        temp = temp->next;
    }

    UmetniIza(NewEl, head);
    return EXIT_SUCCESS;
}

int UmetniIza(PositionList head, PositionList NewEl) {

    head->next = NewEl->next;
    NewEl->next = head;

    return EXIT_SUCCESS;
}

PositionList NapraviElementListe(char* ime_drzave) {
    PositionList NewEl = NULL;
    NewEl = (PositionList)malloc(sizeof(drzava));

    if (!NewEl) {
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(NewEl->ime_drzave, ime_drzave);
    NewEl->grad = NULL;
    NewEl->next = NULL;

    return NewEl;
}

int IspisListe(PositionList first) {
    PositionList temp = first->next;

    while (temp) {
        printf("%s\n ", temp->ime_drzave);
        IspisStabla(temp->grad);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int IspisStabla(Position curr) {
    if (curr == NULL)
        return 0;

    IspisStabla(curr->left);
    printf("\t%s - %d stanovnika\n", curr->ime_grada, curr->broj_stanovnika);
    IspisStabla(curr->right);

    return 0;
}

Position SortiraniUnosUStablo(Position curr, Position NewEl) {

    if (!curr)
        return NewEl;

    if (curr->broj_stanovnika < NewEl->broj_stanovnika) {
        curr->right = SortiraniUnosUStablo(curr->right, NewEl);
    }

    else if (curr->broj_stanovnika > NewEl->broj_stanovnika) {
        curr->left = SortiraniUnosUStablo(curr->left, NewEl);
    }
    else free(NewEl);

    return curr;
}

Position NapraviElementStabla(char* ime_grada, int broj_stanovnika) {
    Position NewEl = (Position)malloc(sizeof(tree));

    if (!NewEl) {
        printf("\nNemoguce alocirati memoriju!!");
        return NULL;
    }

    strcpy(NewEl->ime_grada, ime_grada);
    NewEl->broj_stanovnika = broj_stanovnika;
    NewEl->right = NULL;
    NewEl->left = NULL;

    return NewEl;
}
