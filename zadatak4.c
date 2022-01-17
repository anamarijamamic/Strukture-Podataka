#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom{
	int koef;
	int pot;
	position next;
} polinom;

position stvori_polinom(int k, int eksp);
int procitaj_redak(position Head, char* buffer);
int unesi_nakon(position p, position novi_polinom); 
int unesi_sortirano(position head);
int ispis_liste(position first); 
int procitaj_iz_datoteke(position head1, position head2, char* ime);  
int zbrajanje_polinoma(position head1, position head2, position headS); 
int mnozenje_polinoma(position head1, position head2, position headP); 
int brisanje_memorije(position head); 

int main(int argc, char** argv){

	polinom Head1 = { .next = NULL, .koef = 0, .pot = 0 };
	polinom Head2 = { .next = NULL, .koef = 0, .pot = 0 };
	polinom HeadS = { .next = NULL, .koef = 0, .pot = 0 };
	polinom HeadP = { .next = NULL, .koef = 0, .pot = 0 };

	position p1 = &Head1;
	position p2 = &Head2;
	position pS = &HeadS;
	position pP = &HeadP;

	char fp[MAX_SIZE] = { 0 };

	printf("Unesi ime datoteke");
	scanf(" %s", fp);

	int odabir = 1;

	while (odabir != 0)
	{
		 
		printf("Zelite li:\n");
		printf("\t 0. Izici iz programa\n");
		printf("\t 1. Zbrojiti polinome\n");
		printf("\t 2. Pomnoziti polinome\n");
		printf("unesi odabir:\n ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			break;

		case 1:
			
			if (procitaj_iz_datoteke(p1, p2, fp) != EXIT_SUCCESS) break;
			printf("\tPolinomi:\n");
			printf("1. polinom:\n");
			ispis_liste(p1);
			printf("2. polinom:\n");
			ispis_liste(p2);
			printf("Suma polinoma:\n");
			zbrajanje_polinoma(p1, p2, pS);
			ispis_liste(pS);
			brisanje_memorije(p1);
			brisanje_memorije(p2);
			brisanje_memorije(pS);
			break;

		case 2:
			
			if (procitaj_iz_datoteke(p1, p2, fp) != EXIT_SUCCESS) break;
			printf("\tPolinomi:\n");
			printf("1. polinom:\n");
			ispis_liste(p1);
			printf("2. polinom:\n");
			ispis_liste(p2);
			printf("Produkt polinoma:\n");
			mnozenje_polinoma(p1, p2, pP);
			ispis_liste(pP);
			brisanje_memorije(p1);
			brisanje_memorije(p2);
			brisanje_memorije(pP);
			break;

		default:
			printf("Pogresan unos!\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}


position stvori_polinom(int k, int eksp)
{
	position novi_polinom = NULL;

	novi_polinom = (position)malloc(sizeof(polinom));

	if (!novi_polinom)
	{

		perror("Ne moze se alocirati memorija!\n");
		return -1;
	}

	novi_polinom->koef = k;
	novi_polinom->pot = eksp;
	novi_polinom->next = NULL;

	return novi_polinom;
}

int unesi_nakon(position p, position novi_polinom)
{
	novi_polinom->next = p->next;
	p->next = novi_polinom;

	return EXIT_SUCCESS;
}

int unesi_sortirano(position head)
{
	position i = NULL, j = NULL, prethodni = NULL, temp = NULL, kraj = NULL;
	i = head;
	while (i->next != kraj)
	{
		prethodni = i;
		j = i->next;
		while (j->next != kraj)
		{
			if (j->pot > j->next->pot)
			{
				temp = j->next;
				prethodni->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			prethodni = j;
			j = j->next;
		}
		kraj = j;
	}

	return EXIT_SUCCESS;
}

int ispis_liste(position prvi)
{
	position temp = prvi->next;

	while (temp)
	{
		printf("\t%dx*^(%d)\n", temp->koef, temp->pot);
		temp = temp->next;
	}

	puts("");
	return EXIT_SUCCESS;
}

int procitaj_redak(position head, char* buffer)
{
	int k = 0;
	int eksp = 0;
	char* pointer = NULL; 
	int procitaj_redak = 0; 
	int n = 0; 

	pointer = buffer;

	while (strlen(pointer) > 0) 
	{

		procitaj_redak = sscanf(pointer, " %d %d %n", &k, &eksp, &n);

		if (procitaj_redak == 2 && k != 0) 
			unesi_sortirano(head, stvori_polinom(k, eksp));

		pointer += n; 	
	}

	return EXIT_SUCCESS;
}

int procitaj_iz_datoteke(position head1, position head2, char* fp)
{
	int coef = 0;
	int exp = 0;
	char buffer[MAX_SIZE] = { 0 };

	fp = fopen(fp, "r");

	if (!fp)
	{
		perror("Pogreska pri otvaranju datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_SIZE, fp);
	procitaj_redak(head1, buffer);


	fgets(buffer, MAX_SIZE, fp);
	procitaj_redak(head2, buffer);

	printf("\nPodatci uspjesno upisani iz datoteke %s!\n", fp);

	fclose(fp);

	return EXIT_SUCCESS;
}


int zbrajanje_polinoma(position head1, position head2, position headS)
{
	position p1 = head1->next;
	position p2 = head2->next;
	position pS = headS;
	position temp = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->pot > p2->pot)
		{
			unesi_sortirano(pS, stvori_polinom(p2->koef, p2->pot));
			p2 = p2->next;
		}

		else if (p1->pot == p2->pot)
		{
			unesi_sortirano(pS, stvori_polinom(p1->koef + p2->koef, p1->pot));
			p1 = p1->next;
			p2 = p2->next;
		}

		else 
		{
			unesi_sortirano(pS, stvori_polinom(p1->koef, p1->pot));
			p1 = p1->next;
		}
	}

	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;
	while (temp != NULL)
	{
		unesi_sortirano(pS, stvori_polinom(temp->koef, temp->pot));
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int mnozenje_polinoma(position head1, position head2, position headP)
{
	position p1 = head1->next;
	position p2 = head2->next;
	position pP = headP;
	position start = head2;

	while (p1 != NULL)
	{
		p2 = start; 
		while (p2 != NULL)
		{
			unesi_sortirano(pP, stvori_polinom(p1->koef * p2->koef, p1->pot + p2->pot));
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return EXIT_SUCCESS;
}

int brisanje_memorije(position Head)
{
	position p = Head;
	position temp = NULL;

	if (NULL != p->next) {
		while (NULL != p->next)
		{
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		return EXIT_SUCCESS;
	}
	else return EXIT_FAILURE;
}
