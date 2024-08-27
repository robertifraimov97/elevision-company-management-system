//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_PERSON_H
//#define FINAL_PROJECT_IN_C_PERSON_H

//#endif //FINAL_PROJECT_IN_C_PERSON_H
#ifndef PERSON_H
#define PERSON_H
#define NAME_LENGTH 50


typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
} Person;

void initPerson(Person* pPer);
void printPerson(const Person* pPer);
void personName(Person* pPer);
void increaseId(Person* pPer);


#endif
