#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
#define MAXR 1024


typedef struct student
{
	char ime[MAX];
	char prezime[MAX];
	double bodovi;	
}student;

int prebroji();



student* aip(int ,student*);

int main() 
{
	
	student *s;
	int brstud=0, i;
	brstud=prebroji();
	
	
	printf("Broj studenata je %d \n",brstud);
	
	s=aip(brstud,s);
	for(i=0;i<brstud;i++)
	{
		printf("%s\t %s\t %lf\t %lf\n",s[i].ime,s[i].prezime,s[i].bodovi,s[i].bodovi/30*100);
	}
	
	
	
	return 0;
}

int prebroji()
{
	int br=0;

	
	FILE *f=NULL;
	
	f=fopen("datoteka1.txt","r");
	
	while(!feof(f))
	{
		if(fgetc(f)=='\n')
		br++;
	}
	
	fclose(f);
	return br;
}

student* aip(int br, student *s)
{
	int i;
	FILE *f;
	f=fopen("datoteka1.txt","r");
	
	
	s=(student*)malloc(br*sizeof(student));
	
	for(i=0;i<br;i++)
	{
		fscanf(f," %s %s %lf",s[i].ime,s[i].prezime,&s[i].bodovi);
		
	}
	
	fclose(f);
	
	return s;
}
