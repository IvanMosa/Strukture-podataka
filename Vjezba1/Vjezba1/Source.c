#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;


int main()
{
	int noRows = 0;
	FILE* filePtr = NULL;
	char buffer[MAX_LINE] = { 0 };

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


	printf("%d", noRows);
	fclose(filePtr);
	return 0;
}