#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct gradovi* stablo;
struct gradovi {
    char ime[50];
    stablo D;
    stablo L;
    int br_stanovnika;

};

typedef struct drzave* pozicija;
struct drzave
{
    char ime[50];
    stablo Grad;
    pozicija Next;
};
int DodavanjeDrzave(char* ime_drzave, char* datoteka, pozicija P);
int DodavanjeGrada(char* datoteka, stablo S);
stablo UnosenjeGrada(char* ime, int broj_stan, stablo S);
int ispisiDrzave(pozicija P);
int ispisiGradove(stablo S);
pozicija traziDrzavu(pozicija P, char* ime);
int traziGrad(stablo S, int brojst);
int main(void)
{
    struct drzave Head = { .ime = "", .Grad = NULL, .Next = NULL };
    char ime_drzave[50];
    char ime_datoteke[50];
    pozicija P = NULL;
    int broj_stan = 0;
    FILE* f = NULL;

    f = fopen("drzave.txt", "r");
    if (f == NULL)
    {
        printf("Neuspjesno otvaranje.\n");
        return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %s", ime_drzave, ime_datoteke);
        DodavanjeDrzave(ime_drzave, ime_datoteke, &Head);
    }
    fclose(f);
    ispisiDrzave(Head.Next);

    printf("\nUnesite ime drzave koju zelite pregledati: ");
    scanf("%s", ime_drzave);
    P = traziDrzavu(Head.Next, ime_drzave);
    if (P == NULL)
    {
        printf("Ne postoji ta drzava.\n");
        return 0;
    }
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &broj_stan);
    printf("\nGradovi te drzave (%s) sa vise od %d stanovnika:\n", P->ime, broj_stan);
    traziGrad(P->Grad, broj_stan);

    return 0;


}


int DodavanjeDrzave(char* ime_drzave, char* datoteka, pozicija P)
{
    pozicija q = NULL;
    pozicija prev = NULL;
    stablo z = NULL;

    q = (pozicija)malloc(sizeof(struct drzave));
    if (q == NULL)
    {
        printf("Neispravno alociranje.\n");
        return -1;
    }
    strcpy(q->ime, ime_drzave);
    q->Grad = z;

    z = (stablo)malloc(sizeof(struct gradovi));
    if (z == NULL)
    {
        printf("Neispravno alociranje.\n");
        return -1;
    }
    strcpy(z->ime, "");
    z->br_stanovnika = 0;
    z->D = NULL;
    z->L = NULL;

    q->Grad = z;

    DodavanjeGrada(datoteka, q->Grad);
    prev = P;
    while (P != NULL)
    {
        if (P->Next == NULL)
        {
            P->Next = q;
            q->Next = NULL;
            break;
        }
        if (strcmp(q->ime, prev->Next->ime) < 0)
        {
            q->Next = prev->Next;
            prev->Next = q;
            break;
        }
        P = P->Next;
    }
    return 0;

}
int DodavanjeGrada(char* datoteka, stablo S)
{
    FILE* f = NULL;
    char name[50];
    int broj_stan = 0;

    f = fopen(datoteka, "r");
    if (f == NULL)
    {
        printf("Greska pri otvaranju datoteke.\n"); return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %d", name, &broj_stan);
        S = UnosenjeGrada(name, broj_stan, S);
    }
    fclose(f);
    return 0;
}
stablo UnosenjeGrada(char* ime, int broj_stan, stablo S)
{
    stablo q = NULL;
    if (S == NULL)
    {
        q = (stablo)malloc(sizeof(struct gradovi));
        if (q == NULL)
        {
            printf("Neuspjesno alocrianje.\n");
            return NULL;
        }
        strcpy(q->ime, ime);
        q->br_stanovnika = broj_stan;
        q->D = NULL;
        q->L = NULL;
        return q;
    }
    if (S->br_stanovnika < broj_stan)
        S->D = UnosenjeGrada(ime, broj_stan, S->D);
    else if (S->br_stanovnika > broj_stan)
        S->L = UnosenjeGrada(ime, broj_stan, S->L);
    else if (broj_stan == S->br_stanovnika)
    {
        if (strcmp(ime, S->ime) >= 0)
            S->D = UnosenjeGrada(ime, broj_stan, S->D);
        else
            S->L = UnosenjeGrada(ime, broj_stan, S->L);

    }
    return S;
}
int ispisiGradove(stablo S)
{
    if (S == NULL)
        return 0;
    ispisiGradove(S->L);
    printf("\t%s\n", S->ime);
    ispisiGradove(S->D);
    return 0;
}
pozicija traziDrzavu(pozicija P, char* ime)
{
    while (P != NULL)
    {
        if (strcmp(P->ime, ime) == 0)
            return P;
        P = P->Next;
    }
    return P;
}
int traziGrad(stablo S, int brojst)
{
    if (S == NULL)
        return 0;
    traziGrad(S->L, brojst);
    if (S->br_stanovnika >= brojst)
        printf("\t%s %d\n", S->ime, S->br_stanovnika);
    traziGrad(S->D, brojst);
    return 0;
}
int ispisiDrzave(pozicija P)
{
    printf("Drzave:\n");
    while (P != NULL)
    {
        printf("%s\n", P->ime);
        ispisiGradove(P->Grad->D);
        P = P->Next;
    }
    return 0;
}
