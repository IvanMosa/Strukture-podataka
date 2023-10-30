#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH (50)
#define NO_PERSON_FOUND (NULL)
#define EMPTY_LIST (-1)
#define NO_PERSON_FOUND_INT (-2)
#define SINGLE_PERSON_IN_LIST (-3)

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
Position findPerson(Position Head);
int printPerson(Position Head);
int deletePerson(Position Head);
int addNewPersonBehind(Position Head);
int addNewPersonInfront(Position next);

int main(void) {
    Person Head = { .next = NULL, .name = {0}, .surname={0}, .birthYear = 0};
    char comm={0};
    Position person = NULL;
    Position previous = NULL;
    Position next = NULL;
    
    
    while(1)
    {
        printf("Type the command\n");
        printf("A for new element at the front, B for print, C for new element at the back, D for search with surname, E to delete person by surname, F to add element behind a person\n");
        scanf(" %c", &comm);
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
            case 'D':
            case 'd':
                person = findPerson(Head.next);
                person ? printPerson(person) : printf("Can't find person with that surname\n");
                continue;
            case 'E':
            case 'e':
                switch(deletePerson(&Head))
                {
                    case EXIT_SUCCESS:
                        printf("Deleted.\n");
                        break;
                    case EXIT_FAILURE:
                        printf("List is empty!\n");
                        break;
                    case NO_PERSON_FOUND_INT:
                        printf("Can't find that person!\n");
                        break;
                    default:
                        break;
                }
            case 'F':
            case 'f':
                previous = findPerson(Head.next);
                previous ? addNewPersonBehind(previous) : printf("Can't find that person\n");
                continue;
            case 'G':
            case 'g':
                next = findPerson(Head.next);
                next ? addNewPersonInfront(next) : printf("Can'T find that person\n");
                continue;
            default:
                printf("Wrong command!\n");
                continue;
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
    if(!currentItem)
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

Position findPerson(Position Head)
{
    Position currentItem = Head;
    char surname[MAX_LENGTH] = {0};
    if(!Head)
    {
        printf("Empty list1\n");
        return NULL;
    }
    printf("Enter surname:");
    scanf(" %s", surname);
    do{
        if(strcmp(currentItem->surname, surname) == 0)
        {
            return currentItem;
        }
        else{
            currentItem = currentItem->next;
        }
    }while(currentItem);
    
    return NULL;
}

int printPerson(Position Head)
{
    printf("%s %s %d\n", Head->name, Head->surname, Head->birthYear);
    
    return EXIT_SUCCESS;
}

int deletePerson(Position Head)
{
    Position currentItem = Head;
    char surname[MAX_LENGTH] = {0};
    if(!currentItem)
    {
        printf("Empty list\n");
        return EXIT_FAILURE;
    }
    printf("Enter surname:");
    scanf(" %s", surname);
    if(Head->next)
    {
        Position previous = NULL;
        while(currentItem->next && strcmp(currentItem->surname, surname) != 0)
        {
            previous = currentItem;
            currentItem=currentItem->next;
        }
        if(previous && previous->next && strcmp(currentItem->surname, surname) == 0)
        {
            printPerson(currentItem);
            previous->next=currentItem->next;
            free(currentItem);
        }
        else{
            return NO_PERSON_FOUND_INT;
        }
    }
    else{
        return EMPTY_LIST;
    }
    return EXIT_SUCCESS;
}

int addNewPersonBehind(Position Head)
{
    Position newPerson = NULL;
    
    newPerson = createPerson();
    if(newPerson)
    {
        newPerson->next=Head->next;
        Head->next=newPerson;
    }
    return EXIT_SUCCESS;
}

int addNewPersonInfront(Position previous)
{
    Position newPerson = NULL;
    newPerson = createPerson();
    if(newPerson)
    {
        newPerson->next=previous->next;
        previous->next=newPerson;
    }
    return EXIT_SUCCESS;
}
Position findPrevious(Position Head)
{
    Position current = Head;
}
