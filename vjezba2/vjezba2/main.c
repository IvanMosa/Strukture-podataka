#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birthYear;
    Position next;
} Person;

int addNewStudentToTheFront(Position Head);
Position createPerson(void);
int printList(Position FirstItem);
int addNewStudentToTheBack(Position Head);
Position findLast(Position Head);

int main(void) {
    Person Head = { .next = NULL, .name = {0}, .surname={0}, .birthYear = 0};
    char comm={0};
    Position Person = NULL;
    
    while(1)
    {
        printf("Type the command\n");
        printf("A for new element at the front, B for print, C for new element at the back\n");
        scanf("%c", &comm);
        switch(comm)
        {
            case 'A':
            case 'a':
                addNewStudentToTheFront(&Head);
                continue;
            case 'B':
            case 'b':
                printList(Head.next);
                continue;
            case 'C':
            case 'c':
                addNewStudentToTheBack(&Head);
                continue;
            /*case 'D':
            case 'd':
                person = findPerson(Head.next);
                person ? printPerson(person) : printf("Can't find person with that surname");
                continue;*/
        }
    }
    return 0;
}

Position createPerson(void)
{
    Position newStudent;
    char name[MAX_LENGTH] = { 0 };
    char surname[MAX_LENGTH] = { 0 };
    int birthYear = 0;
    
    newStudent=(Position)malloc(sizeof(Person));
    
    if(!newStudent)
        {
            printf("Can't allocate memory\n");
            return NULL;
        }
    printf("Enter name:");
    scanf("%s", name);
    printf("Enter surname:");
    scanf("%s", surname);
    printf("Enter birth year:");
    scanf("%d", &birthYear);
    
    strcpy(newStudent->name, name);
    strcpy(newStudent->surname, surname);
    newStudent->birthYear=birthYear;
    
    return newStudent;
}

int addNewStudentToTheFront(Position Head)
{
    Position newStudent = NULL;
    
    newStudent=createPerson();
    if(newStudent)
    {
        newStudent->next=Head->next;
        Head->next=newStudent;
    }
    return EXIT_SUCCESS;
}

int printList(Position FirstItem)
{
    Position currentItem = FirstItem;
    while(!currentItem)
    {
        printf("Empty list\n");
    }
    while(currentItem)
    {
        printf("%s %s %d\n", currentItem->name, currentItem->surname, currentItem->birthYear);
        
        currentItem = currentItem->next;
    }
    return EXIT_SUCCESS;
}

int addNewStudentToTheBack(Position Head)
{
    Position newStudent = NULL;
    Position last = NULL;
    
    newStudent=createPerson();
    if(newStudent)
    {
        last = findLast(Head);
        newStudent->next=last->next;
        last->next=newStudent;
    }
    return EXIT_SUCCESS;
}

Position findLast(Position Head)
{
    Position temp = Head;
    while(temp->next)
    {
        temp=temp->next;
    }
    return temp;
}
