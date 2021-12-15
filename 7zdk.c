#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct stablo* Position;
typedef struct stablo {
	char* ime;
	Position child;
	Position sibling;
}Stablo;

typedef struct stog* position;
typedef struct stog {
	Position directory;

	position next;
	position prev;
}Stog;

int MakeDir(Position);
int Menu(Position, position);
int Dir(Position);
Position cd(Position, position);
Position Back(Position, position);
Position FindByName(char*, Position);
int PushStog(position, Position);
Position PopStog(position);
int Linija(position, Position, Position);
position FindLast(position);

int main()
{
	Position root;
	root = (Position)malloc(sizeof(Stablo));
	root->child = NULL;
	root->sibling = NULL;
	Stog* head;
	head = (position)malloc(sizeof(Stog));
	head->next = NULL;
	head->prev = NULL;
	int status = 0;
	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do {
		status = Menu(root, head);
	} while (!status);

	return 0;
}

int Linija(position head, Position root, Position currentFile)
{
	position s;

	s = FindLast(head);

	printf("\n");
	if (head->next == NULL) {
		printf("%s>", root->ime);
		return EXIT_SUCCESS;
	}

	while (s->prev != NULL) {
		printf("%s>", s->directory->ime);
		s = s->prev;
	}

	printf("%s>", currentFile->ime);

	return EXIT_SUCCESS;
	;
}

position FindLast(position head)
{
	position s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int Menu(Position root, position head) {
	Position CurrentFile = root;
	char command[MAX] = { 0 };


	printf("md <filename> - Dodaj direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvori direktorij\n");
	printf("dir - Ispisi listu direktorija u sadasnjem direktoriju\n");
	printf("exit - Izlaz\n");


	while (1) {
		Linija(head, root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			MakeDir(CurrentFile);
		}

		else if (!strcmp(command, "cd")) {
			CurrentFile = cd(CurrentFile, head);
		}

		else if (!strcmp(command, "cd..")) {
			CurrentFile = Back(CurrentFile, head);
		}

		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}

		else if (!strcmp(command, "exit")) {
			return 1;
		}

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}

int MakeDir(Position currentFile) {
	Position directory;
	directory = (Position)malloc(sizeof(Stablo));
	directory->ime = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Memorija nije uspjesno alocirana");

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = directory;
	}

	else
		currentFile->child = directory;

	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
}

int Dir(Position currentFile) {
	if (currentFile->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("DIRECTORIES: \n");
	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}

Position FindByName(char* name, Position currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}

int PushStog(position head, Position directory) {
	position q = (position)malloc(sizeof(Stog));

	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head->next->prev = q;
	}
	head->next = q;
	q->directory = directory;

	return 0;
}

Position PopStog(position head) {
	position q = (position)malloc(sizeof(Stog));
	Position p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;
	if (head->next != NULL)
		head->next->prev = head;
	free(q);

	return p;
}

Position Back(Position currentFile, position head)
{
	Position SearchedFile;

	SearchedFile = PopStog(head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}

Position cd(Position currentFile, position head)
{
	Position SearchedFile;
	char* imeDir;
	imeDir = (char*)malloc(MAX * sizeof(char));

	scanf("%s", imeDir);

	if (currentFile->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return currentFile;
	}

	SearchedFile = FindByName(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	PushStog(head, currentFile);

	return SearchedFile;
}