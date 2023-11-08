#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define EMPTY_LISTS (-2)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element{
    int coefficient;
    int exponent;
    Position next;
}Element;

int readFile(Position HeadPoly1, Position HeadPoly2, char* fileName);
Position createElement(int coefficient, int exponent);
int parseStringIntoList(Position HeadPoly, char* buffer);
int insertSorted(Position HeadPoly, Position newElement);
int mergeAfter(Position HeadPoly, Position newElement);
int insertAfter(Position HeadPoly, Position newElement);
int deleteAfter(Position HeadPoly);
int printPoly(char* polyName, Position first);

int main(void) {
    
    Element HeadPoly1 = { .coefficient=0, .exponent= 0, .next = NULL};
    Element HeadPoly2 = { .coefficient=0, .exponent= 0, .next = NULL};
    char* fileName = "/Users/Mosa21/programiranje/Strukture-podataka/vjezba4/vjezba4/polynomes.txt";
    
    if(readFile(&HeadPoly1, &HeadPoly2, fileName) == EXIT_SUCCESS)
    {
        printPoly("First Polynome ", HeadPoly1.next);
        printPoly("Second Polynome", HeadPoly2.next);
    }
    
    return 0;
}

int readFile(Position HeadPoly1, Position HeadPoly2, char* fileName)
{
    FILE* filePtr = NULL;
    int status = EXIT_SUCCESS;
    char buffer[MAX_LINE] = {0};
    
    filePtr=fopen(fileName, "r");
    
    if(!filePtr)
    {
        printf("Can't open file\n");
        return FILE_NOT_OPEN;
    }
    fgets(buffer, MAX_LINE, filePtr);
    status = parseStringIntoList(HeadPoly1, buffer);
    if(status != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    
    fgets(buffer, MAX_LINE, filePtr);
    status = parseStringIntoList(HeadPoly2, buffer);
    if(status != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent)
{
    Position newElement = NULL;
    
    newElement=(Position)malloc(sizeof(Element));
    
    if(!newElement)
    {
        printf("Failed to allocate memory\n");
        return FAILED_MEMORY_ALLOCATION;
    }
    
    newElement->coefficient=coefficient;
    newElement->exponent=exponent;
    newElement->next=NULL;
    
    return newElement;
}
int parseStringIntoList(Position HeadPoly, char* buffer)
{
    char* currentBuffer = buffer;
    int coefficient = 0;
    int exponent = 0;
    int numBytes = 0;
    int status = 0;
    Position newElement = NULL;
    while(strlen(currentBuffer)>0)
    {
        status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);
        if(status != 2)
        {
            printf("This file is not good\n");
            return EXIT_FAILURE;
        }
        newElement=createElement(coefficient, exponent);
        
        if(!newElement)
        {
            printf("Failed to create element\n");
            return EXIT_FAILURE;
        }
        
        insertSorted(HeadPoly, newElement);
        
        currentBuffer += numBytes;
    }
    return EXIT_SUCCESS;
}
int insertSorted(Position HeadPoly, Position newElement)
{
    while(HeadPoly->next && newElement->exponent<HeadPoly->next->exponent)
    {
        HeadPoly=HeadPoly->next;
    }
    mergeAfter(HeadPoly, newElement);
    
    return EXIT_SUCCESS;
}

int mergeAfter(Position HeadPoly, Position newElement)
{
    if(!HeadPoly->next || HeadPoly->next->exponent != newElement->exponent)
    {
        insertAfter(HeadPoly, newElement);
    }
    else
    {
        int resultCoefficient = newElement->coefficient + HeadPoly->next->coefficient;
        
        if(resultCoefficient == 0)
        {
            deleteAfter(HeadPoly);
        }
        else
        {
            HeadPoly->next->coefficient=resultCoefficient;
        }
        free(newElement);
    }
    return EXIT_SUCCESS;
}
int insertAfter(Position HeadPoly, Position newElement)
{
    newElement->next=HeadPoly->next;
    HeadPoly->next=newElement;
    
    return EXIT_SUCCESS;
}

int deleteAfter(Position HeadPoly)
{
    Position toDelete = NULL;
    
    toDelete = HeadPoly;
    HeadPoly->next=toDelete->next;
    free(toDelete);
    
    return EXIT_SUCCESS;
}

int printPoly(char* polyName, Position first)
{
    printf(" %s = ", polyName);
    if(first)
    {
       if(first->exponent < 0)
       {
           if(first->coefficient == 1)
           {
               printf("x^(%d)", first->exponent);
           }
       }
       else
       {
           if(first->coefficient == 1)
           {
               printf("x^%d", first->exponent);
           }
           else
           {
               printf("%dx^%d", first->coefficient, first->exponent);
           }
       }
        first=first->next;
    }
    for(; first !=NULL; first = first->next)
    {
        if(first->coefficient < 0)
        {
            if(first->exponent < 0)
            {
                printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
            }
            else
            {
                printf(" - %dx^%d", abs(first->coefficient), first->exponent);
            }
        }
        else
        {
            if(first->exponent < 0)
            {
                if(first->coefficient == 1)
                {
                    printf(" + x^(%d)", first->exponent);
                }
                else
                {
                    printf(" + %dx^(%d)", first->coefficient, first->exponent);
                }
            }
            else
            {
                if(first->coefficient == 1)
                {
                    printf(" + x^%d", first->exponent);
                }
                else
                {
                    printf(" + %dx^%d", first->coefficient, first->exponent);
                }
            }
        }
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
