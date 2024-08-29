
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Commercial.h"
#include "General.h"


void initCommercial(Commercial* pCom, Commercial* commercialArr, int commercialNum)
{
    int unique = 0;
    do
    {
        pCom->commercialName = getStrExactName("Enter Commercial name:\n");
        unique = isCommercialNameUnique(commercialArr, commercialNum, pCom->commercialName);
        if (!unique)
            printf("This name is already in use, please try again!\n");

    } while (!unique);

    commercialLength(pCom);
    pCom->type = getCommercialType(pCom);
}

void commercialLength(Commercial* pCom)
{
    printf("Enter the desired commercial length:\nPlease note that the length of the commercial can range between %d - %d seconds.\n", MIN_COMMERCIAL_LENGTH, MAX_COMMERCIAL_LENGTH);
    do
    {
        if (scanf("%d", &(pCom->commercialLengthInSeconds)) != 1) {
            printf("Please enter a valid commercial length:\n");
            while (getchar() != '\n');
        }
        else if (pCom->commercialLengthInSeconds < MIN_COMMERCIAL_LENGTH || pCom->commercialLengthInSeconds > MAX_COMMERCIAL_LENGTH) {
            printf("Please enter a valid commercial length between %d and %d seconds:\n" ,MIN_COMMERCIAL_LENGTH, MAX_COMMERCIAL_LENGTH);
            while (getchar() != '\n');
        }
    } while (pCom->commercialLengthInSeconds < MIN_COMMERCIAL_LENGTH || pCom->commercialLengthInSeconds > MAX_COMMERCIAL_LENGTH);
}

int getCommercialType(Commercial* pCom)
{
    int option = 0;
    printf("Please select one of the commercial types presented to you.\n");
    for (int i = 0; i < eNofCommercialTypes; i++)
    {
        printf("%d ~ %s\n", i+1, CommercialTypeStr[i]);
    }

    do
    {
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                pCom->type = 1;
                break;

            case 2:
                pCom->type = 2;
                break;

            case 3:
                pCom->type = 3;
                break;

            case 4:
                pCom->type = 4;
                break;

            case 5:
                pCom->type = 5;
                break;

            default:
                printf("Not a Valid Number, Please Try Again.\n");
                while (getchar() != '\n');
                option = -1;
                break;
        }
    } while (option < 0);

    if (option >= 1 && option <= 5)
        printf("you chose %s.\nYour answer has been captured in the system.\n\n", CommercialTypeStr[pCom->type - 1]);

    return (pCom->type) - 1;
}

int isCommercialNameUnique(Commercial* commercialArr, int commercialNum, char* name)
{
    for (int i = 0; i < commercialNum; i++)
    {
        if (strcmp(commercialArr[i].commercialName, name) == 0)
            return 0;
    }
    return 1;
}

void printCommercial(const Commercial* pCom)
{
    printf("Commercial: name: %-20s, length: %-15d, type: %-15s\n", pCom->commercialName, pCom->commercialLengthInSeconds, CommercialTypeStr[pCom->type]);
}

void freeCommercial(Commercial* pCom)
{
    free(pCom->commercialName);
}

