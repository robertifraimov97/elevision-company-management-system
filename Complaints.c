//
// Created by Robert Ifraimov on 25/08/2024.
//


#include <stdio.h>
#include "Complaints.h"

void initComplaint(Complaints* pComp, Viewer* viewer)
{
    getCurrentDate(&pComp->date);
    pComp->viewer = *viewer;
    pComp->type = getComplaintType(pComp);
}

Viewer* checkViewer(int viewerId, Viewer* viewerArr, int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        if (viewerArr[i].person.id == viewerId)
            return &(viewerArr[i]);
    }
    printf("Your ID was not found in the company's customer database.\n");
    return NULL;
}

int getComplaintType(Complaints* pComp)
{
    int option = 0;
    printf("Please select one of the complaints presented to you.\n");
    for (int i = 0; i < eNofComplaintsType; i++)
    {
        printf("%d ~ %s\n",i+1, ComplaintsTypeStr[i]);
    }

    do
    {
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                pComp->type = 1;
                break;

            case 2:
                pComp->type = 2;
                break;

            case 3:
                pComp->type = 3;
                break;

            default:
                printf("Not a Valid Number, Please Try Again.\n");
                while (getchar() != '\n');
                option = -1;
                break;
        }
    } while (option < 0);

    if (option >= 1 && option <= 3)
        printf("We thank you for your inquiry and will take care of it as soon as possible.\n");

    return (pComp->type) - 1;
}

void freeComplaints(Complaints* pComp)
{
    freeViewer(&pComp->viewer);
}
