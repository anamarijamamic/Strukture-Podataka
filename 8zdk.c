#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128


typedef struct tree* Position;
typedef struct tree
{
	int number;
	Position left;
	Position right;
}tree;

Position CreateNewElement(int number);
Position Insert(Position root, Position NewElement);
int Inorder(Position root);
int Preorder(Position root);
int Postorder(Position root);

int main()
{
	Position root = NULL;
	Position newElement = NULL;
	int temp = 0;
	int num = 0;

	printf("Izbornik:\n");
	printf("1 - unos novog elementa\n2 - inorder ispis\n3 - preorder ispis\n4 - postorder ispis\n5 - zavrsetak programa\n");


	do {

		scanf("%d", &temp);
		switch (temp)
		{
		case 1:
			printf("\nKoji broj zelite unijeti? ");
			scanf("%d", &num);
			newElement = CreateNewElement(num);
			if (!newElement)
				return -1;
			root = Insert(root, newElement);
			break;
		case 2:
			Inorder(root);
			printf("\n");
			break;
		case 3:
			Preorder(root);
			printf("\n");
			break;
		case 4:
			Postorder(root);
			printf("\n");
			break;
		default:
			break;

		}
	} 	while (temp != 7);

	return 0;
}
Position CreateNewElement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(tree));
	if (!newElement)
	{
		printf("Nije moguce alocirati memoriju!");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
Position Insert(Position current, Position newElement)
{
	if (current == NULL)
		return newElement;
	if (current->number < newElement->number)
		current->right = Insert(current->right, newElement);
	else if (current->number > newElement->number)
		current->left = Insert(current->left, newElement);
	else
		free(newElement);

	return current;
}

int Inorder(Position current)
{
	if (current == NULL)
		return 0;
	Inorder(current->left);
	printf("%d ", current->number);
	Inorder(current->right);

	return 0;
}
int Preorder(Position current)
{
	if (current == NULL)
		return 0;
	printf("%d ", current->number);
	Preorder(current->left);
	Preorder(current->right);

	return 0;
}
int Postorder(Position current)
{
	if (current == NULL)
		return 0;
	Postorder(current->left);
	Postorder(current->right);
	printf("%d ", current->number);

	return 0;
}