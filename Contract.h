//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_CONTRACT_H
//#define FINAL_PROJECT_IN_C_CONTRACT_H

//#endif //FINAL_PROJECT_IN_C_CONTRACT_H

#ifndef CONTRACT
#define CONTRACT
#include "Date.h"
#define BASIC_CHANNELS 2
#define PREMIUM_CHANNELS 3
#define VIP_CHANNELS 5

typedef enum {
    eEmployee, eBasic, ePremium, eVip, eNofContTypes
} eContType;

static const char* ContractTypeStr[eNofContTypes]
        = {"Employee", "Basic", "Premium", "Vip"};

typedef struct
{
    int contractNumber;
    Date contStartDate;
    Date contEndDate;
    eContType type;
}Contract;

void initContract(Contract* pCont);

void contractLength(Contract* pCont);

int typeIdentifier(Contract* pCont);

void increaseContractNumber(Contract* pCont);

void printContract(const Contract* pCont);

#endif