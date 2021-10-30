#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 1024

typedef struct student{
	char ime[MAX];
	char prezime[MAX];
	int godinaRodjenja;
	struct student * next;
}student;

int unosNaPocetak(student * HEAD, student *ubaci);
int ispis(student * head);
int unosNaKraj(student * HEAD, student * ubaci);
student * pronadjiPoPrezimenu(student *HEAD, char *prezime);
int brisiElement(student *HEAD, student * element);
student * pronadjiZadnjiElement(student *HEAD);
student * pronadjiPrethodniElement(student *HEAD, student *elemnt);
student *unosPodataka(void);


int main()
{
	int br;	s=(student*)malloc(sizeof(student));

	char prezime[50];
	student *HEAD;
	student *s;
	HEAD=(student*)malloc(sizeof(student));
	if(!HEAD)
	return -1;
	
	HEAD->next=NULL;
	
	printf("Upisite 1 za unos elementa na pocetak liste \n");
	printf("Upisite 2 za ispis liste \n");
	printf("Upisite 3 za unos elementa na kraj liste \n");
	printf("Upisite 4 za pretragu elementa po prezimenu \n");
	printf("Upisite 5 za brisanje elementa iz liste \n");

	scanf("%d",&br);
	
	switch(br)
	{
		case (1):
			unosNaPocetak(HEAD,unosPodataka());
				break;
			
			
			case (2):
			ispis(HEAD);
				break;
			
			
			case (3):
				unosNaKraj(HEAD,unosPodataka());
				break;
			
			
			case (4):
				
				printf("Unesi prezime po kojem zelis pretraziti\n");
				scanf("%s",prezime);
				s=pronadjiPoPrezimenu(HEAD,prezime);
				printf("%s %s %s",s->ime,s->prezime,s->godinaRodjenja);
				break;
			
			case (5):
			
				printf("Unesite prezime studenta kojeg zelite izbrisati:\n");
				scanf("%s",prezime);
				brisiElement(HEAD,pronadjiPoPrezimenu(HEAD,prezime));
				break;
			
	}
	
	return 0;
}



int unosNaPocetak(student *HEAD, student *ubaci)
{
ubaci->next=HEAD->next;
HEAD->next=ubaci;

return 0;
}



int ispis(student *HEAD)
{
	student *s= HEAD->next;
	
	while(s!=NULL)
	{
		printf(" %s \t %s\t %d\n",s->ime,s->prezime,s->godinaRodjenja);
		s=s->next;
	}
	
	return 0;	
}


int unosNaKraj(student *HEAD, student *ubaci)
{
	student *s=pronadjiZadnjiElement(HEAD);
	
	ubaci->next=NULL;
	s->next=ubaci;
}

student * pronadjiZadnjiElement(student *HEAD)
{
	return pronadjiPrethodniElement(HEAD, NULL);
}

student *pronadiPrethodniElement(student *HEAD, student *element)
{
	
	//element=(student*)malloc(sizeof(student));
	student *s=HEAD;
	while(s!=NULL && s->next!=element)
	s=s->next;
	
	return s;
}

student * pronadjiPoPrezimenu(student *HEAD, char *prezime)
{
	student *s=HEAD->next;
	
	while(s!=NULL && strcmp(s->prezime,prezime))
	{
		s=s->next;
		
	}
	return s;
}

int brisiEement(student *HEAD, student *element)
{
	student *s=HEAD;
	
	while(s!=NULL && s->next !=element)
	{
		s=s->next;
	}
	
	if(s==NULL)
	return -1;
	
	else 
	{
		s->next=s->next->next;
		free(element);
	}
	return 0;
}

student * unosPodataka(void)
{
	student *s=(student*)malloc(sizeof(student));
	
	printf("Unesite ime, prezime i godinu rodjenja studenta: ");
	scanf("%s %s %d",s->ime,s->prezime,&(s->godinaRodjenja));
}
