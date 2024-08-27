//
// Created by Robert Ifraimov on 25/08/2024.
//

#include <stdio.h>
#include "Contract.h"

static int nextContractNumber = 5894;

void increaseContractNumber(Contract* pCont)
{
    pCont->contractNumber = nextContractNumber++;
}

void initContract(Contract* pCont)
{
    increaseContractNumber(pCont);
    pCont->type = typeIdentifier(pCont);
    getCurrentDate(&(pCont->contStartDate));
    contractLength(pCont);
}

void contractLength(Contract* pCont)
{
    int option;
    Date endDate = pCont->contEndDate;
    Date startDate = pCont->contStartDate;

    endDate.day = startDate.day;
    endDate.month = startDate.month;
    if(pCont->type == 0)
        printf("Hello dear employee,\nthank you for choosing us, you have several options for choosing a contract length.\n");
    else
    {
        printf("Hello dear costumer,\nthank you for choosing us, you have several options for choosing a contract length.\n");
    }
    printf("Your contract start date is: ");
    printDate(&startDate);
    printf("\n1 - one - year contract.\n2 - two - year contract.\n3 - Five - year contract.\n");
    do
    {
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                endDate.year = startDate.year + 1;
                printf("You chose the first route, your contract will end on: ");
                printDate(&endDate);
                printf("\n");
                break;
            case 2:
                endDate.year = startDate.year + 2;
                printf("You chose the second route, your contract will end on: ");
                printDate(&endDate);
                printf("\n");
                break;
            case 3:
                endDate.year = startDate.year + 5;
                printf("You chose the third route, your contract will end on: ");
                printDate(&endDate);
                printf("\n");
                break;
            default:
                printf("Not a Valid Number , Please Try Again.\n");
                while (getchar() != '\n');
                option = -1;
                break;
        }
    } while (option < 0);

    pCont->contEndDate = endDate;
}

int typeIdentifier(Contract* pCont)
{
    if (pCont->type == 0)
        return pCont->type;
    else
    {
        int option = 0;
        printf("Dear client! Select the requested route for the contract:\n");
        printf("1 - Basic: This route includes %d viewing channels.\n", BASIC_CHANNELS);
        printf("2 - premium: This route includes %d viewing channels.\n", PREMIUM_CHANNELS);
        printf("3 - VIP: This route includes %d viewing channels.\n", VIP_CHANNELS);
        do
        {
            scanf("%d", &option);

            switch (option)
            {
                case 1:
                    pCont->type = 1;
                    printf("You chose %s.\n", ContractTypeStr[pCont->type]);
                    break;
                case 2:
                    pCont->type = 2;
                    printf("You chose %s\n", ContractTypeStr[pCont->type]);
                    break;
                case 3:
                    pCont->type = 3;
                    printf("You chose %s\n", ContractTypeStr[pCont->type]);
                    break;
                default:
                    printf("Not a Valid Route Number , Please Try Again.\n");
                    while (getchar() != '\n');
                    option = -1;
                    break;
            }

        } while (option < 0);
        return pCont->type;
    }
}

void printContract(const Contract* pCont)
{
    printf("The contract number is: %-10d", pCont->contractNumber);
    printf("Start date: ");
    printDate(&pCont->contStartDate);
    printf("%-10s", "");
    printf("End date: ");
    printDate(&pCont->contEndDate);
    printf("%-10s", "");
    printf("type: %s\n", ContractTypeStr[pCont->type]);

}
