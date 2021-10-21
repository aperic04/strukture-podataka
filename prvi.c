#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX_S 128
//#define MAX_L 1024

typedef struct student
{
	char ime[50];
	char prezime[50];
	double bodovi;	
}student;

int brred();
student* aip(int ,student*);

int main() 
{
	
	student *s;
	int brstud, i;
	FILE *f;
	f=fopen("std.txt","r");
	brstud=brred();
	
	
	printf("Broj studenata je %d \n",brstud);
	s=aip(brstud,s);
	for(i=0;i<brstud;i++)
	{
		printf("%s\t %s\t %lf\n",s[i].ime,s[i].prezime,s[i].bodovi);
	}
	
	
	return 0;
}

int brred()
{
	int br=0;
	
	FILE *f=NULL;
	
	f=fopen("std.txt","r");
	
//	if(!f)
//	printf("greska");
	
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
	f=fopen("std.txt","r");
	
	s=(student*)malloc(br*sizeof(student));
	
	for(i=0;i<br;i++)
	{
		fscanf(f," %s %s %lf",s[i].ime,s[i].prezime,&s[i].bodovi);
		
	}
	
	fclose(f);
	
	return s;
}
