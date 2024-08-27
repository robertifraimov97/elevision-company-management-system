//
// Created by Robert Ifraimov on 25/08/2024.
//

//#define FINAL_PROJECT_IN_C_EMPLOYEE_H

//#endif //FINAL_PROJECT_IN_C_EMPLOYEE_H

#ifndef EMPLOYEE
#define EMPLOYEE
#include "Person.h"
#include "Contract.h"
#include "General.h"
#define EMPLOYEE_MIN_AGE 20


typedef struct
{
    Person person;
    Contract contract;
}Employee;

int initEmployee(Employee* pEmployee);
void printEmployee(const Employee* pEmployee);


#endif //
