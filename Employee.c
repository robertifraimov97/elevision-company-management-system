
#include <stdio.h>
#include "Employee.h"

int initEmployee(Employee* pEmployee)
{
    initPerson(&pEmployee->person);
    if (pEmployee->person.age < EMPLOYEE_MIN_AGE)
    {
        printf("Hello, unfortunately you are still young, you can join us in %d years.\n", EMPLOYEE_MIN_AGE - pEmployee->person.age);
        return 0;
    }

    pEmployee->contract.type = 0;
    initContract(&pEmployee->contract);
    return 1;
}

void printEmployee(const Employee* pEmployee)
{
    PRINT_SEPARATOR_LINE();
    printPerson(&pEmployee->person);
    printContract(&pEmployee->contract);
    PRINT_SEPARATOR_LINE();
}
