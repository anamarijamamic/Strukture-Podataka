#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 100

struct _osoba;
typedef struct _osoba* pozicija;

typedef struct _osoba {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godina_rodenja;
	pozicija next;
} osoba;


int napravi_listu(pozicija head, char* ime, char* prezime, int godina_rodenja);
int ispisi_listu(pozicija head);
int dodaj_listu(pozicija head, char* ime, char* prezime, int godina_rodenja);
pozicija stvori_osobu(char* ime, char* prezime, int godina_rodenja);
int umetni_nakon(pozicija zadnji, pozicija nova_osoba);
pozicija pronadi_zadnjeg(pozicija head);
pozicija pronadi_po_prezimenu(pozicija head, char* prezime);
pozicija pronadi_prethodnog(pozicija head, pozicija nova_osoba);
int obrisi(pozicija head, pozicija brisi);
int sortiraj_po_prezimenu(pozicija head);
int pisi_u_datoteku(pozicija head);
int citaj_iz_datoteke(pozicija head);


int main() {

	int odabir = 0;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	char trazeno_prezime[MAX_SIZE] = { 0 };
	int godina_rodenja = 0;

	pozicija temp_p = NULL;
	temp_p = (pozicija)malloc(sizeof(osoba));



	printf("Odaberite :\n");
	printf("1. Unesi osobu na pocetak liste\n");
	printf("2. Unesi osobu na kraj liste\n");
	printf("3. Pronadi osobu po prezimenu\n");
	printf("4. Ispisi listu\n");
	printf("5. Dodaj osobu iza neke osobe\n");
	printf("6. Dodaj osobu ispred neke osobe\n");
	printf("7. Sortiraj listu\n");
	printf("8. Spremi listu u datoteku\n");
	printf("9. Ucitaj listu iz datoteke\n");
	printf("10. Izbrisi osobu\n");
	printf("0. Zatvori program\n");

	scanf(" %d", &odabir);

	switch (odabir)
	{
		
		case 1:
			printf("\nIme i prezime: ");
			scanf(" %s %s", ime, prezime);
			printf("Godina rodenja: ");
			scanf(" %d", &godina_rodenja);
			napravi_listu(head, ime, prezime, godina_rodenja);
			break;

		case 2:
			printf("\nIme i prezime: ");
			scanf(" %s %s", ime, prezime);
			printf("Godina rodenja: ");
			scanf(" %d", &godina_rodenja);
			dodaj_listu(head, ime, prezime, godina_rodenja);
			break;

		case 3:
			printf("\nIme i prezime:");
			scanf(" %s", trazeno_prezime);
			temp_p = pronadi_po_prezimenu(head, trazeno_prezime);
			printf("\nTrazeni student je %s %s, %d.\n", temp_p->ime, temp_p->prezime, temp_p->godina_rodenja);
			break;

		case 4:
			printf("\nIme i prezime: ");
			scanf(" %s", trazeno_prezime);
			temp_p = pronadi_po_prezimenu(head, trazeno_prezime);
			obrisi(head, temp_p);
			break;

		case 5:
			printf("\nPrezime studenta iza kojeg zelite nadodati novog studenta: ");
			scanf(" %s", trazeno_prezime);
			printf("\nUnesite ime i prezime novog studenta: ");
			scanf(" %s %s", ime, prezime);
			printf("Godina rodenja:  ");
			scanf(" %d", &godina_rodenja);
			temp_p = pronadi_po_prezimenu(head, trazeno_prezime);
			umetni_nakon(temp_p, godina_rodenja(ime, prezime, godina_rodenja));
			break;

		case 6:
			printf("\nUnesite prezime studenta ispred kojeg zelite nadodati novog studenta: ");
			scanf(" %s",trazeno_prezime);
			temp_p = pronadi_po_prezimenu(head, trazeno_prezime);
			printf("\nUnesite ime i prezime novog studenta: ");
			scanf(" %s %s", ime, prezime);
			printf("Unesite godinu rodjenja novog studenta: ");
			scanf(" %d", &godina_rodenja);

			temp_p = pronadi_prethodnog(head, temp_p);
			umetni_nakon(temp_p, stvori_osobu(ime, prezime, godina_rodenja));
			break;

		case 7:
			sortiraj_po_prezimenu(head);
			break;

		case 8:
			pisi_u_datoteku(head);
			break;

		case 9:
			citaj_iz_datoteke(head);
			break;

		case 0:
			return 0;
		}



	return EXIT_SUCCESS;

}


int napravi_listu(pozicija head, char* ime, char* prezime, int godina_rodenja) {

	pozicija nova_osoba = NULL;

	nova_osoba = stvori_osobu(ime, prezime, godina_rodenja);
	if (!nova_osoba) {

		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	umetni_nakon(head, nova_osoba);
	
	return EXIT_SUCCESS;

}

pozicija stvori_osobu(char* ime, char* prezime, int godina_rodenja)
{
	pozicija nova_osoba = NULL;

	nova_osoba = (pozicija)malloc(sizeof(osoba));

	if (!nova_osoba) {

		perror("Nije moguce alocirati memoriju!\n");
		return 0;
	}

	strcpy(nova_osoba->ime, ime);
	strcpy(nova_osoba->prezime, prezime);
	nova_osoba->godina_rodenja = godina_rodenja;
	nova_osoba->next = NULL;

	return nova_osoba;
}


int ispisi_listu(pozicija head)
{
	pozicija temp = head->next;
	while (temp) {
		printf("Ime: %s, prezime: %s, godina rodenja: %d\n",
			temp->ime, temp->prezime, temp->godina_rodenja);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int dodaj_listu(pozicija head, char* ime, char* prezime, int godina_rodenja)
{
	pozicija nova_osoba = NULL;
	pozicija zadnji = NULL;

	nova_osoba = stvori_osobu(ime, prezime, godina_rodenja);
	if (!nova_osoba) {
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}
	zadnji = pronadi_zadnjeg(head);
	umetni_nakon(zadnji, nova_osoba);

	return EXIT_SUCCESS;
}

pozicija pronadi_zadnjeg(pozicija head)
{
	pozicija temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

int umetni_nakon(pozicija zadnji, pozicija nova_osoba)
{
	nova_osoba->next = zadnji->next;
	zadnji->next = nova_osoba;

	return EXIT_SUCCESS;
}

pozicija pronadi_po_prezimenu(pozicija head, char* prezime)
{
	pozicija temp = head->next;

	while (temp != NULL && strcmp(temp->prezime, prezime))
		temp = temp->next;

	return temp;
}

pozicija pronadi_prethodnog(pozicija head, pozicija nova_osoba)
{
	pozicija temp = head;

	while (temp != NULL && temp->next != nova_osoba)
		temp = temp->next;

	return temp;
}

int obrisi(pozicija head, pozicija brisi)
{
	pozicija temp = NULL;
	pozicija q = NULL;
	temp = (pozicija)malloc(sizeof(osoba));
	q = (pozicija)malloc(sizeof(osoba));
	q = brisi;

	temp = pronadi_prethodnog(head, brisi);
	temp->next = q->next;

	free(q);

	return EXIT_SUCCESS;
}


int SortListBySurname(pozicija head)
{
	pozicija temp = head;
	pozicija q = NULL;
	pozicija p = NULL;
	pozicija zadnji = NULL;

	while (temp->next != zadnji)
	{
		p = temp;
		q = p->next;

		while (q->next != zadnji)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			p = q;
			q = q->next;
		}
		zadnji = q;
	}
	return EXIT_SUCCESS;
}



int citaj_iz_datoteke(pozicija head, char* naziv_datoteke) {
	FILE* fp = NULL;
	fp = fopen(naziv_datoteke, "r");
	char ime[MAX_SIZE] = { 0 }, prezime[MAX_SIZE] = { 0 }, buffer = { 0 };
	int godina_rodenja = 0;

	pozicija nova_osoba = 0, temp = head;

	if (!dat) {
		printf("Greska pri alociranju.\n");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d\n", ime, prezime, &godina_rodenja);
		dodaj_listu(head, ime, prezime, &godina_rodenja);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}


int pisi_u_datoteku(pozicija head)
{
	pozicija p = NULL;
	p = (pozicija)malloc(sizeof(osoba));
	p = head->next;

	FILE* fp = NULL;
	fp = fopen("osobe.txt", "w");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (p != NULL) {
		fprintf(fp, "Ime: %s \tPrezime: %s \tGodina: %d\n", q->ime, q->prezime, q->godina_rodenja);
		q = q->next;
	}

	fclose(fp);

	return 0;
}
