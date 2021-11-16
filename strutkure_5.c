#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 30


struct _StackElement;
typedef struct _StackElement* position;
typedef struct _StackElement {
	double number;
	position next;
}_StackElement;

position create(double number);
int insertAfter(position Position, position newEl);
int push(position Head, double number);
int deleteAfter(position Position);
int pop(double* destination, position Head);
int Operation(position Head, char operation);
int calculatePostfixFile(double* destination, char* fileName);




int main(int argc, char** argv)
{
	char fileName[MAX_SIZE] = { 0 };
	double* destination;

	printf("Unesite ime datoteke:");
	scanf(" %s", fileName);

	calculatePostfixFile(destination, fileName);

	return EXIT_SUCCESS;
}


position create(double number)
{
	position newEl = NULL;

	newEl = (position)malloc(sizeof(_StackElement));
	if (!newEl)
	{
		peror("Cant allocate memory!\n");
		return NULL;
	}

	newEl->number = number;
	newEl->next = NULL;


	return newEl;

}

int insertAfter(position Position, position newEl)
{
	newEl->next = Position->next;
	Position->next = newEl;


	return EXIT_SUCCESS;
}

int push(position Head, double number)
{
	position newEl = NULL;

	newEl = create(number);
	if (!newEl)
		return -1;

	insertAfter(Head, newEl);
}

int deleteAfter(position Position)
{
	position temp = Position->next;

	if (!temp)
		return EXIT_SUCCESS;

	Position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int pop(double* destination, position Head)
{
	position first = Head->next;

	if (!first)
	{
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}

	*destination = first->number;

	deleteAfter(Head);
	return EXIT_SUCCESS;
}

int Operation(position Head, char operation)
{
	double operand2 = 0;
	double operand1 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;


	status2 = pop(&operand2, Head);
	if (status2 != EXIT_SUCCESS)
		return -1;


	status1 = pop(&operand1, Head);
	if (status1 != EXIT_SUCCESS)
		return -2;


	switch (operation)
	{
	case '+':
	{
		result = operand1 + operand2;
		break;
	}

	case '-':
	{
		result = operand1 - operand2;
		break;
	}

	case '*':
	{
		result = operand1 * operand2;
		break;
	}

	case '/':
	{
		if (operand2 == 0)
		{
			printf("Cannot devide by zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	}

	default:
	{
		printf("This operation is not supported yet!\n");
		return -4;
	}
	}

	push(Head, result);

	return EXIT_SUCCESS;
}

int calculatePostfixFile(double* destination, char* fileName)
{

	FILE* file = NULL;
	int fileLenght = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	char operation = 0;
	double number = 0;
	int status = 0;
	_StackElement head = { .number = 0, .next = NULL };
	file = fopen(fileName, "rb");

	if (!file)
	{
		perror("Cant open file!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);

	buffer = (char*)calloc(fileLenght + 1, sizeof(char));

	if (!buffer)
	{
		perror("Cant allocate memory!\n");
		return -1;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLenght, file);
	printf("|%s|\n", buffer);
	fclose(file);

	currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);

		if (status == 1)
		{
			push(&head, number);
			currentBuffer += numBytes;
		}

		else
		{
			status = sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = Operation(&head, operation);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				while (head.next = NULL)
				{
					deleteAfter(&head);
				}
				return -1;
			}

			currentBuffer += numBytes;
		}
	}
	free(buffer);

	return EXIT_SUCCESS;
}