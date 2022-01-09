#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct gradovi* pozicija;
struct gradovi {
    char ime_grada[50];
    pozicija Next;
    int brojstanovnika;


};


typedef struct drzave* stablo;
struct drzave {
    char ime_drzave[50];
    stablo D;
    stablo L;
    pozicija Grad;

};

int ispisiDrzave(stablo S);
int ispisiGradove(pozicija P);
stablo trazidrzavu(stablo S, char* imedrz);
int dodajgradove(pozicija P, char* datoteka);
int trazi(stablo S, char* imedrzav, int brojstan);
stablo dodajdrzavu(stablo S, char* imedr, char* imedat);

int main(void)
{
    stablo root = NULL;
    FILE* fp = NULL;
    char ime_drzave[50];
    char imedatoteke[50];
    int stanovnici = 0;

    fp = fopen("drzave.txt", "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje.\n");
        return -1;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%s %s", ime_drzave, imedatoteke);
        root = dodajdrzavu(root, ime_drzave, imedatoteke);
    }
    fclose(fp);
    ispisiDrzave(root);
    char name[50];
    printf("\nUnesite ime drzave koju zelite istraziti: ");
    scanf("%s", &name);

    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &stanovnici);

    trazi(root, name, stanovnici);

    return 0;
}
stablo dodajdrzavu(stablo S, char* imedr, char* imedat)
{
    stablo q = NULL;
    pozicija z = NULL;
    if (S == NULL)
    {
        q = (stablo)malloc(sizeof(struct drzave));
        if (q == NULL)
        {
            printf("Neuspjesna alokacija.\n");
            return NULL;
        }
        strcpy(q->ime_drzave, imedr);

        z = (pozicija)malloc(sizeof(struct gradovi));
        if (z == NULL)
        {
            printf("Neuspjesna alokacija.\n");
            return NULL;
        }
        strcpy(z->ime_grada, "");
        z->brojstanovnika = 0;
        z->Next = NULL;

        q->Grad = z;

        dodajgradove(q->Grad, imedat);
        q->L = NULL;
        q->D = NULL;

        return q;
    }
    else if (strcmp(S->ime_drzave, imedr) < 0)
        S->D = dodajdrzavu(S->D, imedr, imedat);
    else if (strcmp(S->ime_drzave, imedr) > 0)
        S->L = dodajdrzavu(S->L, imedr, imedat);
    return S;

}


int ispisiGradove(pozicija P)
{
    while (P != NULL)
    {
        printf("\t\t%s %d\n", P->ime_grada, P->brojstanovnika);
        P = P->Next;
    }
    return 0;
}

int ispisiDrzave(stablo S)
{
    if (S == NULL)
        return 0;
    ispisiDrzave(S->L);
    printf("\t%s\n", S->ime_drzave);
    ispisiDrzave(S->Grad->Next);
    ispisiDrzave(S->D);
    return 0;
}
int dodajgradove(pozicija P, char* datoteka)
{
    char ime[50];
    int stan = 0;
    pozicija q = NULL;
    FILE *fp = NULL;
    fp = fopen(datoteka, "r");
    pozicija Pocetak = P;
    pozicija prev = P;
    if (fp == NULL)
    {
        printf("Neispravno otvaranje datoteke.\n");
        return -1;
    }
    while (!feof(fp))
    {
        P = Pocetak;
        prev = Pocetak;
        fscanf(fp, "%s %d", ime, &stan);
        q = (pozicija)malloc(sizeof(struct gradovi));
        if (q == NULL)
        {
            printf("Neispravna alokacija.\n");
            return NULL;
        }
        strcpy(q->ime_grada, ime);
        q->brojstanovnika = stan;
        while (P != NULL)
        {
            if (P->Next == NULL)
            {
                q->Next = P->Next;
                P->Next = q;
                break;
            }

            if (q->brojstanovnika < P->brojstanovnika)
            {
                q->Next = prev->Next;
                prev->Next = q;
                break;
            }

            if (strcmp(q->ime_grada, P->ime_grada) < 0)
            {
                q->Next = prev->Next;
                prev->Next = q;
                break;
            }
            prev = P;
            P = P->Next;

        }
    }
    fclose(fp);
    return 0;

}
stablo trazidrzavu(stablo S, char* imedrz)
{
    if (S == NULL)
        return NULL;
    if (strcmp(S->ime_drzave, imedrz) == 0)
        return S;
    if (strcmp(S->ime_drzave, imedrz) > 0)
        return trazidrzavu(S->L, imedrz);
    if (strcmp(S->ime_drzave, imedrz) < 0)
        return trazidrzavu(S->D, imedrz);
}
int trazi(stablo S, char* imedrzav, int brojstan)
{
    pozicija q = NULL;
    stablo R = NULL;

    R = trazidrzavu(S, imedrzav);
    if (R == NULL)
    {
        printf("Nema te drzave.\n");
        return 0;
    }
    q = R->Grad;
    if (q == NULL)
    {
        printf("Drzava nema gradova.\n");
        return 0;
    }
    q = q->Next;
    while (q != NULL)
    {
        if (q->brojstanovnika >= brojstan)
            printf("\t%s %d\n", q->ime_grada, q->brojstanovnika);
        q = q->Next;
    }
    return 0;
}