//
// Created by Robert Ifraimov on 25/08/2024.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Person.h"

static int next_id = 1;

void increaseId(Person* pPer)
{
    pPer->id = next_id++;
}

void initPerson(Person* pPer)
{
    increaseId(pPer);
    personName(pPer);

    printf("Please enter your age.\n");
    do
    {
        if (scanf("%d", &(pPer->age)) != 1) {
            printf("Please enter a valid age:\n");
            while (getchar() != '\n');
        }
        else if (pPer->age <= 0 || pPer->age > 120) {
            printf("Please enter a valid age between 1 and 120:\n");

            while (getchar() != '\n');
        }
    } while (pPer->age <= 0 || pPer->age > 120);
}

void printPerson(const Person* pPer)
{
    printf("Name: %-10s, Id number: %-10d, age: %-10d\n",pPer->name, pPer->id, pPer->age);
}

void personName(Person* pPer)
{
    int isValid = 0;
    printf("Please enter a name.\n");
    do
    {
        isValid = 1;
        scanf("%s", pPer->name);
        for (int i = 0; i < strlen(pPer->name); i++) {
            if (!isalpha(pPer->name[i]))
            {
                printf("Please enter a valid name:\n");
                isValid = 0;
                break;
            }
        }

    } while (isValid == 0);
}
