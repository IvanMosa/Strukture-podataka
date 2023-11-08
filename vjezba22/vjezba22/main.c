#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT (50)
#define NO_PERSON_FOUND (NULL)
#define NO_PERSON_FOUND_INT (-1)
#define EMPTY_LIST (-2)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person{
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    int birthYear;
    Position next;
}Person;

int addPersonToTheFront(Position Head);
Position createPerson(void);
int printList(Position FirstPerson);
int addPersonToTheBack(Position Head);
Position findLast(Position Head);
Position findPerson(Position Head);
int printPerson(Position person);
int deletePerson(Position Head);
int printListInDoc(Position Head);
Position findPrevious(Position Head);
int addPersonAfter(Position previous);
int printListFromDoc(Position Head);

int main(void) {
    
    Person Head = {.name={0}, .surname={0}, .birthYear=0, .next=NULL};
    Position person = NULL;
    Position previous = NULL;
    while(1)
    {
        char com;
        printf("Type command\n");
        printf("A - new person from the front, B - print list, C - new person from the back, D - print person by surname, E - delete person, F - add person behind, G - add person before, H - print list in a document\n");
        scanf(" %c", &com);
        switch(com)
        {
            case 'A':
            case 'a':
                addPersonToTheFront(&Head);
                continue;
            case 'B':
            case 'b':
                printList(Head.next);
                continue;
            case 'C':
            case 'c':
                addPersonToTheBack(&Head);
                continue;
            case 'D':
            case 'd':
                person = findPerson(&Head);
                person ? printPerson(person):printf("Can't find a person with that surname\n");
                continue;
            case 'E':
            case 'e':
                switch(deletePerson(&Head))
                {
                    case NO_PERSON_FOUND_INT:
                        printf("Can' find that person\n");
                        break;
                    case EMPTY_LIST:
                        printf("Empty list\n");
                        break;
                    case EXIT_SUCCESS:
                        printf("Person deleted\n");
                        break;
                    default:
                        break;
                }
                continue;
            case 'F':
            case 'f':
                person = findPerson(&Head);
                person ? addPersonAfter(person):printf("Can't find that person\n");
                continue;
            case 'G':
            case 'g':
                previous = findPrevious(&Head);
                previous ? addPersonAfter(previous) : printf("Can't find that person\n");
                continue;
            case 'H':
            case 'h':
                printListInDoc(Head.next);
                continue;
            /*
            case 'I':
            case 'i':
                printListFromDoc(&Head);*/
            case 'X':
            case 'x':
                printf("Exiting...\n");
                break;
            default:
                printf("Wrong letter\n");
                continue;
        }
        break;
    }
    return 0;
}

Position createPerson(void)
{
    Position newPerson;
    char surname[MAX_LENGHT]={0};
    char name[MAX_LENGHT]={0};
    int birthYear=0;
    
    newPerson=(Position)malloc(sizeof(Person));
    if(!newPerson)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }
    
    printf("Enter name:");
    scanf("%s", name);
    printf("Enter surname:");
    scanf("%s", surname);
    printf("Enter year:");
    scanf("%d", &birthYear);
    
    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear=birthYear;
    
    return newPerson;
}

int addPersonToTheFront(Position Head)
{
    Position newPerson=NULL;
    newPerson=createPerson();
    
    if(newPerson)
    {
        newPerson->next=Head->next;
        Head->next=newPerson;
    }
    return EXIT_SUCCESS;
}

int printList(Position FirstPerson)
{
    if(!FirstPerson)
    {
        printf("Empty list!\n");
        return NO_PERSON_FOUND_INT;
    }
    while(FirstPerson!=NULL)
    {
        printf("%s %s %d\n", FirstPerson->name, FirstPerson->surname, FirstPerson->birthYear);
        FirstPerson=FirstPerson->next;
    }
    return EXIT_SUCCESS;
}

int addPersonToTheBack(Position Head)
{
    Position newPerson = NULL;
    Position last = NULL;
    newPerson=createPerson();
    
    if(newPerson)
    {
        last=findLast(Head);
        newPerson->next=last->next;
        last->next=newPerson;
    }
    return EXIT_SUCCESS;
}

Position findLast(Position Head)
{
    Position last = Head;
    
    while(last->next!=NULL)
    {
        last=last->next;
    }
    return last;
}

Position findPerson(Position Head)
{
    Position person = Head;
    char surname[MAX_LENGHT]={0};
    if(!person)
    {
        printf("Empty list\n");
        return NO_PERSON_FOUND;
    }
    printf("Enter surname:");
    scanf("%s", surname);
    do
    {
        if(strcmp(person->surname, surname)==0)
        {
            return person;
        }
        else
        {
            person=person->next;
        }
    }while(person);
    
    return NO_PERSON_FOUND;
}

int printPerson(Position person)
{
    printf("%s %s %d\n", person->name, person->surname, person->birthYear);
    return EXIT_SUCCESS;
}

int deletePerson(Position Head)
{
    Position current = Head;
    char surname[MAX_LENGHT]={0};
    printf("Enter surname:");
    scanf("%s", surname);
    if(current->next)
    {
        Position prev=NULL;
        while(current && strcmp(current->surname, surname) != 0)
        {
            prev=current;
            current=current->next;
        }
            if(prev && prev->next && strcmp(current->surname, surname) == 0)
            {
                prev->next=current->next;
                free(current);
            }
            else
            {
                return NO_PERSON_FOUND_INT;
            }
    }
    else
    {
        return EMPTY_LIST;
    }
    return EXIT_SUCCESS;
}


int printListInDoc(Position Head)
{
    FILE* filePtr=NULL;
    
    filePtr=fopen("/Users/Mosa21/programiranje/Strukture-podataka/vjezba22/vjezba22/list.txt", "w");
    
    if(!filePtr)
    {
        printf("Failed to create file\n");
        return EXIT_FAILURE;
    }
    if(Head)
    {
        while(Head)
        {
            fprintf(filePtr,"%s %s %d\n", Head->name, Head->surname, Head->birthYear);
            Head=Head->next;
        }
    }
    else
    {
        fclose(filePtr);
        return NO_PERSON_FOUND_INT;
    }
    
    fclose(filePtr);
    return EXIT_SUCCESS;
}

Position findPrevious(Position Head)
{
    Position prev=NULL;
    char surname[MAX_LENGHT]={0};
    printf("Enter surname:");
    scanf("%s", surname);
    if(Head)
    {
        while(Head && strcmp(Head->surname, surname) != 0)
        {
            prev=Head;
            Head=Head->next;
        }
        if(Head && strcmp(Head->surname, surname) == 0)
        {
            return prev;
        }
        else
        {
            return NO_PERSON_FOUND;
        }
    }
    else
    {
        return NO_PERSON_FOUND;
    }
}

int addPersonAfter(Position previous)
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
