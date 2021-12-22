#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE 1024
#define COUNT 10

struct _tree;
typedef struct _tree* Position;

typedef struct _tree {
	int el;
	Position left;
	Position right;
}tree;

Position CreateElement(int element);
Position Insert(Position curr, Position new);
int Replace(Position current);
int RandomNum(int min, int max);
int Inorder(Position curr);
int ToFile(Position current, FILE* fp);

int main()
{
	char* file = "stablo.txt";
	Position head = NULL;
	Position first = NULL;
	Position root = NULL;
	Position temp = NULL;

	int list1[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int list2[10] = { 0 };
	int min = 0;
	int max = 0;
	int i = 0;

	srand(time(NULL));
	head = (Position)malloc(sizeof(tree));
	for (i = 0; i < 10; i++)
	{
		temp = CreateElement(list1[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
			Insert(first, temp);
		}
	}

	printf("(Inorder) print before the sum operation: \n");
	Inorder(first);
	Replace(first);
	puts("\n\n");

	head->el = 0;
	head->left = NULL;
	head->right = NULL;

	printf("(Inorder) print after the sum operation: \n");
	Inorder(first);
	first = head->right;
	while (first != NULL)
	{
		printf("%d ", first->el);
		first = first->right;
	}

	puts("\n\n");
	ToFile(head, file);
	printf("Enter the limits of random numbers:\n");
	printf("Low: ");
	scanf(" %d", &min);
	printf("High: ");
	scanf(" %d", &max);
	puts("\n");

	for (i = 0; i < 10; i++)
	{
		list2[i] = RandomNum(min, max);
	}

	for (i = 0; i < 10; i++)
	{
		temp = CreateElement(list2[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
			Insert(first, temp);
		}
	}

	Inorder(first);
	Replace(first);
	puts("\n");
	return 0;
}

Position CreateElement(int element)
{
	Position new = NULL;
	new = (Position)malloc(sizeof(tree));
	new->el = element;
	new->left = NULL;
	new->right = NULL;
	return new;
}

Position Insert(Position curr, Position new)
{
	if (curr == NULL)
	{
		return new;
	}
	if ((curr->el) <= (new->el))
	{
		curr->right = Insert(curr->right, new);
	}
	else if ((curr->el) > (new->el))
	{
		curr->left = Insert(curr->left, new);
	}
	return curr;
}

int Inorder(Position curr)
{
	if (curr)
	{
		Inorder(curr->left);
		printf("%d ", curr->el);
		Inorder(curr->right);
	}

	return EXIT_SUCCESS;
}

int Replace(Position current)
{
	int L1 = 0;
	int D1 = 0;
	int L2 = 0;
	int D2 = 0;

	if (current != NULL)
	{
		if (current->left != NULL)
		{
			L1 = current->left->el;
		}
		if (current->right != NULL)
		{
			D1 = current->right->el;
		}

		Replace(current->left);
		Replace(current->right);

		if (current->left != NULL)
		{
			L2 = current->left->el;
		}

		if (current->right != NULL)
		{
			D2 = current->right->el;
		}

		return current->el = L2 + D2 + L1 + D1;
	}
	return EXIT_SUCCESS;
}

int ToFile(Position head, char* name)
{
	FILE* dat = NULL;
	Position temp;

	temp = head->right;
	dat = fopen(name, "w");

	while (temp != NULL)
	{
		fprintf(dat, "%d ", temp->el);
		temp = temp->right;
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int RandomNum(int min, int max)
{
	int n = 0;
	n = max - min + 1;
	int m = RAND_MAX - (RAND_MAX % n);
	int rand_num = rand();
	while (rand_num > m)
		rand_num = rand();
	return rand_num % n + min;
}