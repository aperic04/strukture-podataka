#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#define MAX 1024

typedef struct _student {
	char ime[MAX];
	char prezime[MAX];
	int godina;

	struct _student* next;
}student;


int UnosPocetak(student*);
int Ispis(student*);
int UnosKraj(student*);
student* PronadiZadnji(student*);
student* PronadiPrezime(student*, char*);
student* PronadiPrethodni(student*, student*);
int Obrisi(student*, student*);
int DodajIzaElementa(student*, student*);
int DodajIspredElementa(student*, student*);
int Sortiraj(student*);
int CitajIzDat(student*);
int PisiuDat(student*);

int main()
{
	student* head;
	head = (student*)malloc(sizeof(student));
	head->next = NULL;
	int izbor = 0;

	char prezime[MAX];
	student* nadi_prezime = NULL;
	nadi_prezime = (student*)malloc(sizeof(student));

	char obrisi[MAX];
	student* obrisi_el = NULL;
	obrisi_el = (student*)malloc(sizeof(student));

	char iza[MAX];
	student* dodaj_iza = NULL;
	dodaj_iza = (student*)malloc(sizeof(student));

	char ispred[MAX];
	student* dodaj_ispred = NULL;
	dodaj_ispred = (student*)malloc(sizeof(student));
	
	printf("\n");
	printf("1 - Unos na pocetak\n");
	printf("2 - Unos na kraj\n");
	printf("3 - Ispis liste\n");
	printf("4 - Pronadi prezime\n");
	printf("5 - Izbrisi prezime\n");
	printf("6 - Dodaj iza\n");
	printf("7 - Dodaj ispred\n");
	printf("8 - Sortiraj listu\n");
	printf("9 - Citaj iz datoteke\n");
	printf("10 - Pisi u datoteku\n");
	
	printf("\n");

	while (1) {

		printf("\nIzaberite sto zelite raditi:\n");
		scanf(" %d", &izbor);

		switch (izbor) {
		case (1): UnosPocetak(head);
			break;

		case (2): UnosKraj(head);
			break;

		case (3): Ispis(head);
			break;

		case(4): printf("\n\nKoje prezime zelite pronaci? ");
			scanf("%s", prezime);
			nadi_prezime = PronadiPrezime(head, prezime);
			printf("\nElement koji ste pretrazili:\nIme: %s\nPrezime: %s\nGodina rodenja: %d\n", nadi_prezime->ime, nadi_prezime->prezime, nadi_prezime->godina);
			break;

		case(5): printf("\n\nKoje prezime zelite obrisati? ");
			scanf("%s", obrisi);
			obrisi_el = PronadiPrezime(head, obrisi);
			Obrisi(head, obrisi_el);
			break;

		case (6): printf("\nIza kojeg prezimena zelite dodati element? ");
			scanf("%s", iza);
			dodaj_iza = PronadiPrezime(head, iza);
			DodajIzaElementa(head, dodaj_iza);
			break;

		case(7): printf("\nIspred kojeg elementa zelite dodati prezime? ");
			scanf("%s", ispred);
			dodaj_ispred = PronadiPrezime(head, ispred);
			DodajIspredElementa(head, dodaj_ispred);
			break;

		case(8): Sortiraj(head);
			break;

		case(9): CitajIzDat(head);
			break;

		case(10): PisiuDat(head);
			break;


		
		}
	}


	

	return 0;
}

int UnosPocetak(student* head)
{
	student* s;
	s = (student*)malloc(sizeof(student));

	s->next = head->next;
	head->next = s;

	printf("Unesite ime: ");
	scanf("%s", s->ime);
	printf("Unesite prezime: ");
	scanf("%s", s->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &s->godina);
	printf("\n");

	return 0;
}

int Ispis(student* head)
{
	student* s = head->next;

	printf("\n");
	while (s != NULL) {
		printf("\tIme: %s", s->ime);
		printf("\n\tPrezime: %s", s->prezime);
		printf("\n\tGodina rodenja: %d\n", s->godina);
		printf("\n");
		s = s->next;
	}
	

	return 0;
}

int UnosKraj(student* head)
{
	student* s;
	s = (student*)malloc(sizeof(student));
	student* p;
	p = (student*)malloc(sizeof(student));

	p = PronadiZadnji(head);

	s->next = NULL;
	p->next = s;

	printf("Unesite ime: ");
	scanf("%s", s->ime);
	printf("Unesite prezime: ");
	scanf("%s", s->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &s->godina);
	printf("\n");

	return 0;
}

student* PronadiZadnji(student* head)
{
	student* p = head;

	while (p != NULL && p->next != NULL)
		p = p->next;

	return p;
}

student* PronadiPrezime(student* head, char* prezime)
{
	student* P = head->next;

	while (P != NULL && strcmp(P->prezime, prezime))
		P = P->next;

	return P;
}

student* PronadiPrethodni(student* head, student* element)
{
	student* P;
	P = head;

	while (P != NULL && P->next != element)
		P = P->next;

	return P;
}

int Obrisi(student* head, student* element)
{
	student* P = NULL;
	student* q = NULL;
	P = (student*)malloc(sizeof(student));
	q = (student*)malloc(sizeof(student));
	q = element;

	P = PronadiPrethodni(head, element);
	P->next = q->next;

	free(q);

	return 0;
}

int DodajIzaElementa(student* head, student* element)
{
	student* novi;
	novi = (student*)malloc(sizeof(student));

	printf("Unesite ime: ");
	scanf("%s", novi->ime);
	printf("Unesite prezime: ");
	scanf("%s", novi->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &novi->godina);
	printf("\n");

	novi->next = element->next;
	element->next = novi;

	return 0;
}

int DodajIspredElementa(student* head, student* element)
{
	student* novi;
	novi = (student*)malloc(sizeof(student));
	student *P = NULL;
	P = (student*)malloc(sizeof(student));

	P = PronadiPrethodni(head, element);

	P->next = novi;
	novi->next = element;

	printf("Unesite ime: ");
	scanf("%s", novi->ime);
	printf("Unesite prezime: ");
	scanf("%s", novi->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &novi->godina);
	printf("\n");
	
	return 0;
}

int Sortiraj(student * head)
{
	student * p = head;
	student * q = NULL;
	student * pret_q = NULL;
	student * zadnji = NULL;

	while (p->next != zadnji)
	{
		pret_q = p;
		q = pret_q->next;

		while (q->next != zadnji)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
			{
				pret_q->next = q->next;
				q->next = q->next->next;
				pret_q->next->next = q;
				q = pret_q->next;
			}
			pret_q = q;
			q = q->next;
		}
		zadnji = q;
	}

	return 0;
}

int CitajIzDat(student* head)
{
	student* q;
	student* p = PronadiZadnji(head);
	
	FILE* fp = NULL;
	fp = fopen("datoteka1.txt", "r");

	int znak = 0;
	int broj = 0;
	int i = 0;
	char buffer[MAX] = { 0 };

	if (fp == NULL) {
		printf("Greska!\n");
		return -1;
	}

	while (fgets(buffer, MAX, fp)) {
		broj++;
	}

	rewind(fp);

	for(i=0; i<broj; i++){
		q = (student*)malloc(sizeof(student));

		q->next = NULL;
		p->next = q;
		p = p->next;

		fscanf(fp, "%s %s %d", q->ime, q->prezime, &q->godina);		
	}

	fclose(fp);

	return 0;
}

int PisiuDat(student* head)
{
	student* q = NULL;
	q = (student*)malloc(sizeof(student));
	q = head->next;

	FILE* fp = NULL;
	fp = fopen("datoteka.txt", "w+");

	if (fp == NULL) {
		printf("Greska!\n");
		return -1;
	}
	
	while (q != NULL) {
		fprintf(fp, "Ime: %s \tPrezime: %s \tGodina: %d\n", q->ime, q->prezime, q->godina);
		q = q->next;
	}

	fclose(fp);

	return 0;
}
