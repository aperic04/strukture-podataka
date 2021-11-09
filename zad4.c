#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#define MAX 25

struct Polinom {
	int koef;
	int pot;
	struct Polinom *next;
};
typedef struct Polinom* Pol;


int Unos(Pol);
int UnosSume(Pol, int, int);
Pol Stvori(Pol);
int Ispis(Pol);
int Suma(Pol, Pol, Pol);
int Umnozak(Pol, Pol, Pol);
int SortirajUmnozak(Pol);

int main()
{
	Pol P1, P2, S, U;

	P1 = (Pol)malloc(sizeof(struct Polinom));
	P2= (Pol)malloc(sizeof(struct Polinom));
	S = (Pol)malloc(sizeof(struct Polinom));
	U = (Pol)malloc(sizeof(struct Polinom));

	P1->next = NULL;
	P2->next = NULL;
	S->next = NULL;
	U->next = NULL;

	Unos(P1);
	Ispis(P1);

	Unos(P2);
	Ispis(P2);

	Suma(P1, P2, S);
	printf("\nSuma: \n");
	Ispis(S);

	Umnozak(P1, P2, U);
	SortirajUmnozak(U);
	printf("\nUmnozak: \n");
	Ispis(U);

	return 0;
}

Pol Stvori(Pol head)
{
	Pol q;
	q = (Pol)malloc(sizeof(struct Polinom));

	if (head == NULL) {
		printf("\nGreska u alokaciji memorije!\n");
	}

	q->next = head->next;
	head->next = q;

	return q;
}

int Unos(Pol P)
{
	Pol q;
	Pol temp = NULL;
	q = (Pol)malloc(sizeof(struct Polinom));

	temp = P;

	char* filename;

	filename = (char*)malloc(sizeof(char) * MAX);

	printf("\nIz koje datoteke citamo? ");
	scanf("%s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}


	while (!feof(fp)) {

		q = Stvori(q);

		fscanf(fp, " %d %d", &q->koef, &q->pot);

		while (temp->next != NULL && temp->next->pot > q->pot)
			temp = temp->next;
		if (temp->next != NULL && temp->next->pot == q->pot) {
			temp->next->koef += q->koef;

			if (temp->next->koef == 0) {
				q = temp->next;
				temp->next = q->next;
			}
		}
		else {
			q->next = temp->next;
			temp->next = q;
		}
	}

	fclose(fp);

	return 0;
}

int Ispis(Pol p1)
{
	p1 = p1->next;
	while (p1->next != NULL) {
		printf(" %d x^%d + ", p1->koef, p1->pot);
		p1 = p1->next;
	}
	printf(" %d x^%d ", p1->koef, p1->pot);

	printf("\n");

	return 0;
}

int UnosSume(Pol S, int k, int p)
{
	Pol q;

	while (S->next != NULL && S->next->pot > p)
		S = S->next;
	
	q = (Pol)malloc(sizeof(struct Polinom));
	q->koef = k;
	q->pot = p;
	q->next = S->next;
	S->next = q;

	return 0;
}


int Suma(Pol P1, Pol P2, Pol S)
{
	Pol temp = NULL;
	temp = (Pol)malloc(sizeof(struct Polinom));
	P1 = P1->next;
	P2 = P2->next;

	while (P1 != NULL && P2 != NULL) {

		if (P1->pot == P2->pot) {
			UnosSume(S, P1->koef + P2->koef, P1->pot);
			P1 = P1->next;
			P2 = P2->next;
		}

		else if (P1->pot > P2->pot) {
			UnosSume(S, P1->koef, P1->pot);
			P1 = P1->next;
		}

		else {
			UnosSume(S, P2->koef, P2->pot);
			P2 = P2->next;
		}
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL) {
		UnosSume(S, temp->koef, temp->pot);
		temp = temp->next;
	}

	return 0;
}

int SortirajUmnozak(Pol u)
{
	Pol temp;
	temp = (Pol)malloc(sizeof(struct Polinom));

	u = u->next;
	temp = u->next;

	while (u != NULL && temp!=NULL) {
		if(u->pot == temp->pot) {
			u->koef = u->koef + temp->koef;
			u->next = temp->next;
			free(temp);
			temp = u->next;
		}	
		else {
			u = u->next;
			temp = temp->next;
		}
	}

	return 0;
}

int Umnozak(Pol p1, Pol p2, Pol u)
{
	Pol temp;
	p1 = p1->next;
	p2 = p2->next;
	temp = p2->next;

	while (p1 != NULL) {
		while (p2 != NULL) {
			UnosSume(u, p1->koef * p2->koef, p1->pot + p2->pot);
			p2 = p2->next;
		}
		p2 = temp;
		p1 = p1->next;
	}
	return 0;
}
