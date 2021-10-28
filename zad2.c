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
student * pronadjiPoPrezimenu(student *HEAD, cahr *prezime);
int brisiElement(student *HEAD, student * element);
student * pronadjiZadnjiElement(stuent *HEAD);
student * pronadjiPrethodniElement(student *HEAD, student *elemnt);
student *unosPodataka(void);


int main()
{
	student *HEAD;
	HEAD=(student*)malloc(sizeof(student));
	if(!HEAD)
	return -1;
	
	HEAD->next=NULL;
	
	
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
	student *s=HEAD;
	while(s!=NULL && s->next!=elemnt)
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

int brisiEement(strudent *HEAD, student *element)
{
	srudent *s=HEAD;
	
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
