//
// Created by Robert Ifraimov on 25/08/2024.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Time.h"

#define SPECIAL_TAV ':'

void validTime(Time* pTime)
{
    char time[255];
    int ok = 1;

    do {
        printf("Enter Time hh%cmm%css\t", SPECIAL_TAV, SPECIAL_TAV);
        myGets(time, 255);
        ok = checkTime(time, pTime);
        if (!ok)
            printf("Error try again\n");
    } while (!ok);
}

int	 checkTime(char* time, Time* pTime)
{
    int hour, minutes, seconds;
    if (strlen(time) != 8)
        return 0;
    if ((time[2] != SPECIAL_TAV) || (time[5] != SPECIAL_TAV))
        return 0;
    sscanf(time, "%d%*c%d%*c%d", &hour, &minutes, &seconds);
    if (hour < 0 || hour > 24 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59)
        return 0;

    pTime->hours = hour;
    pTime->minutes = minutes;
    pTime->seconds = seconds;

    return 1;
}

void printTime(const Time* pTime)
{
    if (pTime->hours < 10)
    {
        printf("0");
    }
    printf("%d:", pTime->hours);

    if (pTime->minutes < 10)
    {
        printf("0");
    }
    printf("%d:", pTime->minutes);

    if (pTime->seconds < 10)
    {
        printf("0");
    }
    printf("%d\n", pTime->seconds);
}

void printTimeToFile(const Time* pTime, FILE* file)
{
    if (pTime->hours < 10)
    {
        fprintf(file, "0");
    }
    fprintf(file, "%d:", pTime->hours);

    if (pTime->minutes < 10)
    {
        fprintf(file, "0");
    }
    fprintf(file, "%d:", pTime->minutes);

    if (pTime->seconds < 10)
    {
        fprintf(file, "0");
    }
    fprintf(file, "%d\n", pTime->seconds);
}