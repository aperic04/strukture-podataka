#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<ctype.h>

#define MAX 1024

typedef struct student{
	char ime[MAX];
	char prezime[MAX];
	int godRod;
	struct student* next;
}student;

int UnosNaPocetak(student*);
int ispis(student*);
int unosNaKraj(student*);
student* pronadjiZadnji(student *);
student* pronadjiPoPrezimenu(student *, char*);
student* pronadjiPrethodni(student*, student *);
int obrisi(student*,student *);
int dodajIspredElementa(student*,student*);
int pisiUDatoteku(student*);

int main() 
{
	
	int izbor=0;
	
	student *head;
	head=(student*)malloc(sizeof(student));
	head->next=NULL;
	
	
	char prezime[MAX];
	student* trazeno_prezime = NULL;
	trazeno_prezime = (student*)malloc(sizeof(student));
	
	char obrisii[MAX];
	student* obrisi_el=NULL;
	obrisi_el=(student*)malloc(sizeof(student));
	
	char ispred[MAX];
	student *dodaj_ispred=NULL;
	dodaj_ispred=(student*)malloc(sizeof(student));
	
	printf("1-Unos na pocetak\n");
	printf("2-Unos na kraj\n");
	printf("3-Ispis\n");
	printf("4-Pronadji po prezimenu\n");
	printf("5-Obrisi element \n");
	printf("6-Ddaj ispred elementa \n");
	printf("7-Pisi u datoteku \n");
	
	while(1)
	{
		printf("1-Unos na pocetak\n");
	printf("2-Unos na kraj\n");
	printf("3-Ispis\n");
	printf("4-Pronadji po prezimenu\n");
	printf("5-Obrisi element \n");
	printf("6-Ddaj ispred elementa \n");
	printf("7-Pisi u datoteku \n");
	
		printf("Unesite vas izbor: ");
		scanf("%d",&izbor);
		
		switch(izbor)
		{
			case 1:UnosNaPocetak(head);
			break;
			
			case 2:UnosNaKraj(head);
			break;
			
			case 3:ispis(head);
			break;
				
			case 4:
				printf("Unesite prezime koje zelitr ponaci: ");
				scanf("%s",prezime);
				trazeno_prezime=pronadjiPoPrezimenu(head,prezime);
				printf("Trazena osoba je: %s\t %s\t %d\n",trazeno_prezime->ime,trazeno_prezime->prezime,trazeno_prezime->godRod);
				break;
			case 5:
				printf("\n Koje prezime zelite izbrisati\n");
				scanf("%s",obrisii);
				obrisi_el=pronadjiPoPrezimenu(head,obrisii);
				obrisi(head,obrisi_el);
					break;
					
			case 6:
				printf("\nIpred kojeg elementa zelite dodati: \n");
				scanf("%s",ispred);
				dodaj_ispred=pronadjiPoPrezimenu(head,ispred);
				dodajIspredElementa(head,dodaj_ispred);
				
				break;
				
			case 7:
				pisiUDatoteku(head);
		}
	}

	
	
	return 0;
}

int UnosNaPocetak(student *head)
{
	student *s;
	s=(student*)malloc(sizeof(student));
	
	s->next=head->next;
	head->next=s;
	
	printf("Unesite ime:");
	scanf("%s",s->ime);
	printf("Unesite prezime:");
	scanf("%s",s->prezime);
	printf("Unesite godrod:");
	scanf("%d",&s->godRod);
	printf("\n");
	
	return 0;
}
	
int ispis(student* head)
{
	student *s=head->next;
	
	while(s!=NULL)
	{
	printf("Ime:%s\n ",s->ime);
	printf("Prezme:%s\n ",s->prezime);
	printf("Godina rodjenja:%d \n",s->godRod);
	printf("\n");
		s=s->next;
	}
}

int UnosNaKraj(student *head)
{
	student *s;
	s=(student *)malloc(sizeof(student));
	student *p;
	p=(student *)malloc(sizeof(student));
	
	p=pronadjiZadnji(head);
	
	s->next=NULL;
	p->next=s;
	
	printf("Unesite ime:");
	scanf("%s",s->ime);
	printf("Unesite prezime:");
	scanf("%s",s->prezime);
	printf("Unesite godrod:");
	scanf("%d",&s->godRod);
	printf("\n");
	
	return 0;
	
}	

student * pronadjiZadnji(student *head)
{
	student *p=head;
	while(p!=NULL && p->next !=NULL)
	{
		p=p->next;
	}
	
	return p;
}

student * pronadjiPoPrezimenu(student* head,char* prezime)
{
	student *p=head->next;
	
	while(p->next!=NULL && strcmp(p->prezime,prezime))
	{
		p=p->next;
	}
	return p;
}

student* pronadjiPrethodni(student* head, student* element)
{
	student *p;
	p=head;
	
	while(p!=NULL && p->next!=element)
	p=p->next;
	
	return p;
}

int obrisi(student *head, student *element)
{
	student *p;
	p=(student *)malloc(sizeof(student));
	student *q;
	q=(student *)malloc(sizeof(student));
	
	q=element;
	
	p=pronadjiPrethodni(head,element);
	
	p->next=q->next;
	
	free(q);
	return 0;
	
}

int dodajIspredElementa(student *head,student *element)
{
	student *novi;
	novi=(student*)malloc(sizeof(student));
	student *p=NULL;
	p=(student*)malloc(sizeof(student));
	
	p=pronadjiPrethodni(head,element);
	p->next=novi;
	novi->next=element;
	
	printf("Unesite ime: ");
	scanf("%s", novi->ime);
	printf("Unesite prezime: ");
	scanf("%s", novi->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &(novi->godRod));
	printf("\n");
	
	return 0;
}
int pisiUDatoteku(student *head)
{
	student *q=NULL;
	q=(student*)malloc(sizeof(student));
	q=head->next;
	
	FILE *fp=NULL;
	fp=fopen("std.txt","w");
	
	/*	printf("Unesite ime:");
	scanf("%s",q->ime);
	printf("Unesite prezime:");
	scanf("%s",q->prezime);
	printf("Unesite godrod:");
	scanf("%d",&q->godRod);
	printf("\n");*/
	
	while(q=NULL)
	{
		fprintf(fp,"%s,%s,%d",q->ime,q->prezime,q->godRod);
		q=q->next;
	}
	fclose(fp);
	return 0;
}

