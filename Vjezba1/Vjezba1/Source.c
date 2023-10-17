#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}_student;


int main()
{
	int noRows = 0;
	FILE* filePtr = NULL;
	char buffer[MAX_LINE] = { 0 };
	_student* s;

	filePtr = fopen("students.txt", "r");
	if (!filePtr)
	{
		printf("Error while opening the file!\n");
		return -1;
	}
	while (!feof(filePtr))
	{
		fgets(buffer, MAX_LINE, filePtr);
		noRows++;
	}
	rewind(filePtr);
	
	s = malloc(sizeof(_student) * noRows);

	for (int i = 0; i < noRows; i++)
	{
		fscanf(filePtr, "%s %s %lf", s[i].name, s[i].surname, &s[i].points);
	}
	
	for (int i = 0; i < noRows; i++)
	{
		printf("%s %s %lf %lf\n", s[i].name, s[i].surname, s[i].points/100, s[i].points/(100*100));
	}
	fclose(filePtr);
	return 0;
}