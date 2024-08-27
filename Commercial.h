//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_COMMERCIAL_H
//#define FINAL_PROJECT_IN_C_COMMERCIAL_H

//#endif //FINAL_PROJECT_IN_C_COMMERCIAL_H

#ifndef COMMERCIAL
#define COMMERCIAL
#define MAX_COMMERCIAL_LENGTH 60
#define MIN_COMMERCIAL_LENGTH 5


typedef enum {
    eFoodAndDrinks, eTechnology, eFashion, eCars, eTourism, eNofCommercialTypes
} eCommercialType;

static const char* CommercialTypeStr[eNofCommercialTypes]
        = { "Food and drinks", "Technology", "Fashion", "Cars", "Tourism"};


typedef struct
{
    char* commercialName;
    int commercialLengthInSeconds;
    eCommercialType type;

}Commercial;

void initCommercial(Commercial* pCom, Commercial* commercialArr, int commercialNum);
void commercialLength(Commercial* pCom);
int getCommercialType(Commercial* pCom);
int	isCommercialNameUnique(Commercial* commercialArr, int commercialNum, char* name);
void printCommercial(const Commercial* pCom);
void freeCommercial(Commercial* pCom);




#endif