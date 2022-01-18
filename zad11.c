#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128
#define HASH_SIZE 11


struct _drzava;
typedef struct _drzava* PozicijaDrzave;

struct _grad;
typedef struct _grad* PozicijaGrad;

typedef struct _grad
{
	char* name;
	int populacija;
	PozicijaGrad left;
	PozicijaGrad right;
}grad;

typedef struct _drzava
{
	char* name;
	PozicijaGrad root;
	PozicijaDrzave next;
}drzava;



PozicijaDrzave StvoriDrzavu(char*);
int UmetniDrzavu(PozicijaDrzave, PozicijaDrzave);
int UmetniNakon(PozicijaDrzave, PozicijaDrzave);
PozicijaDrzave PronadjiDrzavu(PozicijaDrzave, char*);
PozicijaGrad StvoriGrad(char*, int);
int UsporediGrad(PozicijaGrad, PozicijaGrad);
int CitajIzDatoteke(PozicijaDrzave[], char*);
int IspisiListu(PozicijaDrzave);
PozicijaGrad StvoriStabloIzListe(char*);
int UmetniCvor(PozicijaGrad, PozicijaGrad);
int IspisiSilazno(PozicijaGrad);
int IspisiVeceg(PozicijaGrad, int);
void IspisiLiniju();
int PretraziGradove(PozicijaDrzave[]);



int main()
{
	PozicijaDrzave hashTablica[HASH_SIZE];
	int i;
	for (i = 0; i < HASH_SIZE; i++)
	{
		hashTablica[i] = (PozicijaDrzave)malloc(sizeof(drzava));
		hashTablica[i]->name = NULL;
		hashTablica[i]->root = NULL;
		hashTablica[i]->next = NULL;
	}


	CitajIzDatoteke(hashTablica, "drzave.txt");

	for (i = 0; i < HASH_SIZE; i++)
	{
		IspisiListu(hashTablica[i]);
	}

	PretraziGradove(hashTablica);

	return 0;
}



int UmetniNakon(PozicijaDrzave pos, PozicijaDrzave novaDrzava)
{
	novaDrzava->next = pos->next;
	pos->next = novaDrzava;

	return 0;
}

int UmetniDrzavu(PozicijaDrzave head, PozicijaDrzave novaDrzava)
{
	PozicijaDrzave temp = head;

	while (temp->next)
	{
		if (strcmp(novaDrzava->name, temp->next->name) < 0)
		{
			UmetniNakon(temp, novaDrzava);
			return EXIT_SUCCESS;
		}

		temp = temp->next;
	}

	UmetniNakon(temp, novaDrzava);
	return EXIT_SUCCESS;
}

PozicijaDrzave StvoriDrzavu(char* name)
{
	PozicijaDrzave novaDrzava = NULL;

	novaDrzava = (PozicijaDrzave)malloc(sizeof(drzava));

	if (!novaDrzava)
	{
		printf("Nema dovoljno memorije!!!\n");
		return NULL;
	}

	novaDrzava->name = (char*)malloc(strlen(name) + 1);

	strcpy(novaDrzava->name, name);
	novaDrzava->root = NULL;
	novaDrzava->next = NULL;

	return novaDrzava;
}


PozicijaGrad StvoriGrad(char* name, int populacija)
{
	PozicijaGrad noviGrad = NULL;
	noviGrad = (PozicijaGrad)malloc(sizeof(grad));
	if (!noviGrad)
	{
		printf("Nema dovoljno memorije!!\n");
		return NULL;
	}

	noviGrad->name = (char*)malloc(strlen(name) + 1);
	strcpy(noviGrad->name, name);
	noviGrad->populacija = populacija;
	noviGrad->left = NULL;
	noviGrad->right = NULL;

	return noviGrad;
}

int UsporediGrad(PozicijaGrad first, PozicijaGrad second)
{
	int rezultat = 0;

	rezultat = first->populacija - second->populacija;

	if (!rezultat)
	{
		rezultat = strcmp(first->name, second->name);
	}

	return rezultat;
}

int CitajIzDatoteke(PozicijaDrzave hash[HASH_SIZE], char* filename)
{
	FILE* drzave = NULL;
	PozicijaDrzave tempDrzava = NULL;

	char* buffer = NULL;
	char* temp = NULL;
	char* drzavaIme = NULL;
	char* datGradova = NULL;

	int fileSize = 0;
	int read = 0;
	int state = 0;
	int key = 0;
	int limit = 5;

	drzavaIme = (char*)malloc(MAX_SIZE);
	datGradova = (char*)malloc(MAX_SIZE);

	if (!drzavaIme || !datGradova)
	{
		printf("Nema memorije!!\n");
		return -1;
	}

	drzave = fopen(filename, "r");

	if (!drzave)
	{
		printf("Datoteka ne postoji!!\n");
		return 1;
	}

	fseek(drzave, 0, SEEK_END);
	fileSize = ftell(drzave);
	rewind(drzave);

	buffer = (char*)malloc(fileSize + 1);

	if (!buffer)
	{
		printf("Nema memorije!!\n");
		return -1;
	}

	fread(buffer, fileSize, 1, drzave);
	fclose(drzave);

	temp = buffer;

	while (strlen(temp) > 0)
	{
		state = sscanf(temp, "%s %s %n", drzavaIme, datGradova, &read);
		temp += read;
		int i;
		if (state == 2)
		{
			tempDrzava = StvoriDrzavu(drzavaIme);

			if (tempDrzava)
			{
				tempDrzava->root = StvoriStabloIzListe(datGradova);
				if (strlen(tempDrzava->name) < limit)
					limit = strlen(tempDrzava->name);

				for (i = 0; i < limit; i++)
				{
					key += (tempDrzava->name)[i];
				}

				key = key % HASH_SIZE;
				UmetniDrzavu(hash[key], tempDrzava);

				key = 0;
				limit = 5;
			}
		}

	}

	return 0;
}

int IspisiListu(PozicijaDrzave head)
{
	PozicijaDrzave temp = head->next;

	if (!temp)
	{
		return 1;
	}

	while (temp)
	{
		printf("%s:\n", temp->name);
		IspisiLiniju();
		IspisiSilazno(temp->root);
		IspisiLiniju();
		printf("\n");
		temp = temp->next;
	}

	return 0;
}

int UmetniCvor(PozicijaGrad curr, PozicijaGrad noviCvor)
{
	int state = 0;
	int relation = 0;
	if (!curr)
	{
		printf("Stablo ne postoji!!\n");
		return 1;
	}

	relation = UsporediGrad(noviCvor, curr);

	if (!relation)
	{
		free(noviCvor);
		return EXIT_SUCCESS;
	}

	if (relation < 0)
	{
		if (!(curr->left))
		{
			curr->left = noviCvor;
			return EXIT_SUCCESS;
		}
		state = UmetniCvor(curr->left, noviCvor);
		return EXIT_SUCCESS;
	}

	else
	{
		if (!(curr->right))
		{
			curr->right = noviCvor;
			return EXIT_SUCCESS;
		}
		state = UmetniCvor(curr->right, noviCvor);
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}

PozicijaGrad StvoriStabloIzListe(char* imedatoteke)
{
	FILE* graadovi = NULL;
	PozicijaGrad tempGraad = NULL;
	PozicijaGrad root = NULL;

	char* buffer = NULL;
	char* temp = NULL;
	char* imeGraada = NULL;

	int fileSize = 0;
	int read = 0;
	int pop = 0;
	int state = 0;

	imeGraada = (char*)malloc(MAX_SIZE);


	graadovi = fopen(imedatoteke, "r");

	if (!graadovi)
	{
		return NULL;
	}

	fseek(graadovi, 0, SEEK_END);
	fileSize = ftell(graadovi);
	rewind(graadovi);

	buffer = (char*)malloc(fileSize + 1);

	if (!buffer)
	{
		printf("Nema memorije!!!\n");
		return NULL;
	}

	fread(buffer, fileSize, 1, graadovi);
	fclose(graadovi);

	temp = buffer;

	while (strlen(temp) > 0)
	{
		state = sscanf(temp, "%s %d %n", imeGraada, &pop, &read);
		temp += read;

		if (state == 2)
		{
			tempGraad = StvoriGrad(imeGraada, pop);

			if (tempGraad)
			{
				if (!root)
					root = tempGraad;
				else
				{
					UmetniCvor(root, tempGraad);
				}
			}
		}
	}

	return root;
}

void IspisiLiniju()
{
	printf("\n");
	return;
}

int IspisiSilazno(PozicijaGrad pos)
{
	if (pos == NULL)
		return EXIT_SUCCESS;
	IspisiSilazno(pos->right);
	printf("%s - Populacija %d\n", pos->name, pos->populacija);
	IspisiSilazno(pos->left);

	return EXIT_SUCCESS;
}

int IspisiVeceg(PozicijaGrad pos, int limit)
{
	if (pos == NULL)
		return EXIT_SUCCESS;

	IspisiVeceg(pos->left, limit);
	if (pos->populacija > limit)printf("%s - Populacija %d\n", pos->name, pos->populacija);
	IspisiVeceg(pos->right, limit);

	return EXIT_SUCCESS;
}

PozicijaDrzave PronadjiDrzavu(PozicijaDrzave head, char* name)
{
	PozicijaDrzave temp = head;
	while (temp)
	{
		if (temp->name && !strcmp(temp->name, name))
		{
			return temp;
		}

		temp = temp->next;
	}

	return NULL;
}

int PretraziGradove(PozicijaDrzave hash[HASH_SIZE])
{
	char* drzavaIme = NULL;
	PozicijaDrzave toFind = NULL;
	int popLimit = 0;

	int key = 0;
	int limit = 5;

	printf("Izaberite drzavu:");
	drzavaIme = (char*)malloc(MAX_SIZE);

	fgets(drzavaIme, MAX_SIZE, stdin);
	drzavaIme[strcspn(drzavaIme, "\n")] = 0;

	if (strlen(drzavaIme) < limit)
		limit = strlen(drzavaIme);
	
	int i;
	
	for (i = 0; i < limit; i++)
	{
		key += drzavaIme[i];
	}

	key = key % HASH_SIZE;

	toFind = PronadjiDrzavu(hash[key], drzavaIme);

	if (!toFind)
	{
		printf("Nemoguce pronaci drzavu!!!\n");
		return 1;
	}

	printf("Unesite populaciju: ");
	scanf("%d", &popLimit);

	printf("\nGradovi u %s sa populacijom vecom od %d:\n", toFind->name, popLimit);
	IspisiLiniju();
	IspisiVeceg(toFind->root, popLimit);

	return 0;
}
