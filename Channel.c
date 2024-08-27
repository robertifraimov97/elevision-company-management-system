//
// Created by Robert Ifraimov on 25/08/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Channel.h"

void initChannel(Channel* pChannel)
{
    pChannel->ChannelNum = choosingChannelNum(pChannel);
    pChannel->type = getChannelType(pChannel);
    pChannel->CommercialArr = NULL;
    pChannel->numOfCommercial = 0;

    if (!L_init(&(pChannel->showsList))) {
        printf("Error\n");
        return;
    }
}

int initShow(Show* pShow, Channel* pChannel)
{
    while (1)
    {
        getShowName(pShow->showName);
        if (checkUniqeName(pShow->showName, pChannel))
            break;

        printf("This name is already in use, please try again!\n");
    }

    showLength(pShow);
    choosingABroadcastDay(pShow);
    while (1)
    {
        if (broadcastTime(pShow, pChannel) == 1)
            break;
    }
    showSubtitles(pShow);

    return 1;
}

int getChannelType(Channel* pChannel)
{
    int option = 0;
    printf("Please select one of the channel types presented to you.\n");
    for (int i = 0; i < eNofgenreTypes; i++)
    {
        printf("%d ~ %s\n",i+1, ChannelTypeStr[i]);
    }

    do
    {
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                pChannel->type = 1;
                break;

            case 2:
                pChannel->type = 2;
                break;

            case 3:
                pChannel->type = 3;
                break;

            case 4:
                pChannel->type = 4;
                break;

            case 5:
                pChannel->type = 5;
                break;

            case 6:
                pChannel->type = 6;
                break;

            default:
                printf("Not a Valid Number, Please Try Again.\n");
                while (getchar() != '\n');
                option = -1;
                break;
        }
    } while (option < 0);

    if (option >= 1 && option <= 6)
        printf("You chose %s.\nYour answer has been captured in the system.\n\n", ChannelTypeStr[pChannel->type - 1]);

    return (pChannel->type) - 1;
}

int addCommercial(Channel* pChannel)
{
    pChannel->CommercialArr = (Commercial*)realloc(pChannel->CommercialArr, (pChannel->numOfCommercial + 1) * sizeof(Commercial));
    if (!pChannel->CommercialArr)
        return 0;
    initCommercial(&pChannel->CommercialArr[pChannel->numOfCommercial], pChannel->CommercialArr, pChannel->numOfCommercial);
    pChannel->numOfCommercial++;
    return 1;
}

int choosingChannelNum(Channel* pChannel)
{
    int numOfChnanel = 0;
    printf("Please enter the channel number you want to open. (%d-%d)\n", MIN_CHANNEL_NUM, MAX_CHANNEL_NUM);

    do
    {
        if (scanf("%d", &(pChannel->ChannelNum)) != 1) {
            printf("Please enter a valid channel number:\n");
            while (getchar() != '\n');
        }
        else if (pChannel->ChannelNum < MIN_CHANNEL_NUM || pChannel->ChannelNum > MAX_CHANNEL_NUM) {
            printf("Please enter a valid channel number between %d and %d:\n", MIN_CHANNEL_NUM, MAX_CHANNEL_NUM);
            while (getchar() != '\n');
        }
    } while (pChannel->ChannelNum < MIN_CHANNEL_NUM || pChannel->ChannelNum > MAX_CHANNEL_NUM);
    return pChannel->ChannelNum;
}

void printChannel(const Channel* pChannel)
{
    printf("The channel number is: %-20d", pChannel->ChannelNum);
    printf("The channel genre is: %s\n\n", ChannelTypeStr[pChannel->type]);
    generalArrayFunction(pChannel->CommercialArr, pChannel->numOfCommercial, sizeof(Commercial), printCommercialsArr);
    int numShows = L_print(&(pChannel->showsList), printShow);
    printf("There are %d show", numShows);
    PRINT_PLURAL_IF_MORE_THAN_ONE(numShows);// MACRO

    printf("There are %d commercial", pChannel->numOfCommercial);
    PRINT_PLURAL_IF_MORE_THAN_ONE(pChannel->numOfCommercial);// MACRO
}

void printCommercialsArr(void* arr, int size)
{
    Commercial* pArr = (Commercial*)arr;
    for (int i = 0; i < size; i++)
        printCommercial(&pArr[i]);
}

void generalArrayFunction(void* arr, int numOfElements, size_t typeSize, void(*freeOrPrintFunc)(void*, int))
{
    freeOrPrintFunc(arr, numOfElements);
}

int addShow(Channel* pChannel)
{
    Show* pShow = (Show*)calloc(1, sizeof(Show));
    if (!pShow)
        return 0;

    if (!initShow(pShow, pChannel))
    {
        free(pShow);
        return 0;
    }

    return 1;
}

Show* findShowByName(const Channel* pChannel, char* name)
{
    if (!(pChannel->showsList.head.next) || !name)
        return NULL;

    return (Show*)L_find(pChannel->showsList.head.next, name, isSameShowName);
}

int checkUniqeName(char* name, const Channel* pChannel)
{
    Show* show = findShowByName(pChannel, name);

    if (show != NULL)
        return 0;

    return 1;
}


int broadcastTime(Show* pShow, Channel* channel) {
    Time broadcastTime;
    boolean conflict = FALSE;
    int scanfResult;
    char dummy;

    do {
        printf("Enter the broadcast start time (in HH:MM format): ");
        scanfResult = scanf("%d:%d%c", &broadcastTime.hours, &broadcastTime.minutes, &dummy);
        if (scanfResult != 3 || dummy != '\n') {
            printf("Invalid input. Please enter a valid time in HH:MM format.\n");
            while ((dummy = getchar()) != '\n' && dummy != EOF); // clear input buffer
        }
        else if (broadcastTime.hours < 0 || broadcastTime.hours > 23) {
            printf("Invalid hour. Please enter an hour between 0 and 23.\n");
            scanfResult = 0; // reset scanfResult to repeat the loop
        }
        else if (broadcastTime.minutes < 0 || broadcastTime.minutes > 59) {
            printf("Invalid minute. Please enter a minute between 0 and 59.\n");
            scanfResult = 0; // reset scanfResult to repeat the loop
        }
    } while (scanfResult != 3 || dummy != '\n');

    broadcastTime.seconds = 0;

    Time endTime;
    endTime.hours = broadcastTime.hours + (pShow->showLengthInMinutes + broadcastTime.minutes) / 60;
    endTime.minutes = (pShow->showLengthInMinutes + broadcastTime.minutes) % 60;
    endTime.seconds = 0;

    NODE* current = channel->showsList.head.next;

    while (current != NULL)
    {
        Show* existingShow = (Show*)current->key;
        if (strcmp(pShow->broadcastDay, existingShow->broadcastDay) == 0)
        {
            if ((existingShow->startTime.hours < endTime.hours || (existingShow->startTime.hours == endTime.hours &&
                                                                   existingShow->startTime.minutes <= endTime.minutes)) && (broadcastTime.hours < existingShow->endTime.hours || (broadcastTime.hours == existingShow->endTime.hours
                                                                                                                                                                                  && broadcastTime.minutes <= existingShow->endTime.minutes)))
            {
                conflict = TRUE;
                break;
            }
            else if ((existingShow->startTime.hours == broadcastTime.hours && existingShow->startTime.minutes == broadcastTime.minutes) || (existingShow->endTime.hours == endTime.hours
                                                                                                                                            && existingShow->endTime.minutes == endTime.minutes))
            {
                conflict = TRUE;
                break;
            }
            else
            {
                conflict = FALSE;
            }
        }
        current = current->next;
    }

    if (conflict) {
        printf("There is a scheduling conflict with an existing program. Please choose a different time.\n");
        return 0;
    }

    if (endTime.hours > 23 || (endTime.hours == 23 && endTime.minutes > 59)) {
        printf("Invalid end time. Please choose a valid end time (up to 23:59).\n");
        return 0;
    }
    pShow->startTime = broadcastTime;
    pShow->endTime = endTime;

    printf("Broadcast time set successfully from %02d:%02d to %02d:%02d\n",
           broadcastTime.hours, broadcastTime.minutes, endTime.hours, endTime.minutes);

    L_insert(&(channel->showsList.head), pShow);
    return 1;
}


Commercial* commercialNameExist(char* commercialName, Commercial* commercialArr, int numOfCommercials)
{
    for (int i = 0; i < numOfCommercials; i++)
    {
        if (strcmp(commercialArr[i].commercialName, commercialName) == 0)
            return &commercialArr[i];
    }
    return NULL;
}

int deleteCommercial(Commercial* commercialArr, int* numOfCommercials, char* commercialToDelete)
{
    for (int i = 0; i < *numOfCommercials; i++)
    {
        if (strcmp(commercialToDelete, commercialArr[i].commercialName) == 0)
        {
            freeCommercial(&commercialArr[i]);

            // Shift elements after the deleted element to fill the gap
            for (int j = i; j < *numOfCommercials - 1; j++)
            {
                commercialArr[j] = commercialArr[j + 1];
            }
            (*numOfCommercials)--;

            // Check if numOfCommercials is zero after the deletion
            if (*numOfCommercials == 0) {
                free(commercialArr);
                commercialArr = NULL;
            }
            else {
                // Reallocate memory only if there are more than zero commercials left
                Commercial* temp = realloc(commercialArr, (*numOfCommercials) * sizeof(Commercial));
                if (!temp)
                {
                    return 0;
                }
                commercialArr = temp;
            }

            return 1; // Return 1 indicating successful deletion
        }
    }

    return 0; // Return 0 if the commercial to delete was not found
}



void freeChannel(Channel* pChannel)
{
    L_free(&(pChannel->showsList), freeShow);

    for (int i = 0; i < pChannel->numOfCommercial; i++)
        freeCommercial(&pChannel->CommercialArr[i]);
    free(pChannel->CommercialArr);
}
