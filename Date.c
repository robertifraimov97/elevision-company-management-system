
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "General.h"
#include "Date.h"

void getCurrentDate(Date* pDate)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    pDate->day = timeinfo->tm_mday;
    pDate->month = timeinfo->tm_mon + 1;
    pDate->year = timeinfo->tm_year + 1900;
}

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '#'

void getCorrectDate(Date* pDate)
{
    char date[255];
    int ok = 1;

    do {
        printf("Enter Date dd%c%cmm%c%cyyyy\t",
               SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV);
        myGets(date, 255);
        ok = checkDate(date, pDate);
        if (!ok)
            printf("Error try again\n");
    } while (!ok);
}

int	 checkDate(char* date, Date* pDate)
{
    int day, month, year;
    if (strlen(date) != 12)
        return 0;
    if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
        || (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
        return 0;
    sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
    if (day < 1 || month < 1 || month > 12)
        return 0;

    if (day > DAY_MONTHS[month - 1])
        return 0;

    pDate->day = day;
    pDate->month = month;
    pDate->year = year;

    return 1;
}

void printDate(const Date* pDate)
{
    printf("%d/%d/%d", pDate->day, pDate->month, pDate->year);
}
