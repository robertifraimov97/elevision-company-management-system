//
// Created by Robert Ifraimov on 25/08/2024.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Show.h"
#include "General.h"


void getShowName(char* code)
{
    char temp[SHOW_NAME_LENGTH];
    int ok;
    do {
        ok = 1;
        printf("Enter a name for the show:\n");
        myGets(temp, SHOW_NAME_LENGTH);
        if (strlen(temp) > SHOW_NAME_LENGTH)
        {
            printf("Name should contain less than %d letters.\n", SHOW_NAME_LENGTH);
            ok = 0;
        }
    } while (!ok);

    strcpy(code, temp);
}

void showSubtitles(Show* pShow)
{
    char trueOrFalse[10];
    printf("Do you want your show to have subtitles T/F? ");
    do {
        scanf("%s", trueOrFalse);

        if (strcmp(trueOrFalse, "t") == 0 || strcmp(trueOrFalse, "T") == 0) {
            pShow->subtitles = 1;
            break;
        }
        else if (strcmp(trueOrFalse, "f") == 0 || strcmp(trueOrFalse, "F") == 0) {
            pShow->subtitles = 0;
            break;
        }
        else {
            printf("Please enter valid output.\n");
            while (getchar() != '\n');
        }
    } while (1);
}

void showLength(Show* pShow)
{
    printf("Enter the desired show length:\nPlease note that the length of the show can range between 15 - 90 minutes.\n");
    do
    {
        if (scanf("%d", &(pShow->showLengthInMinutes)) != 1) {
            printf("Please enter a valid show length:\n");
            while (getchar() != '\n');
        }
        else if (pShow->showLengthInMinutes < 15 || pShow->showLengthInMinutes > 90) {
            printf("Please enter a valid show length between 15 and 90 minutes:\n");
            while (getchar() != '\n');
        }
    } while (pShow->showLengthInMinutes < 15 || pShow->showLengthInMinutes > 90);
}


void choosingABroadcastDay(Show* pShow)
{
    char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int choice;

    printf("Pick a day of the week:\n");
    for (int i = 0; i < 7; ++i) {
        printf("%d. %s\n", i + 1, days[i]);
    }

    do {
        printf("Enter the number corresponding to your choice: ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= 7) {
            printf("You picked: %s\n", days[choice-1]);
            strcpy(pShow->broadcastDay, days[choice-1]);
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
            while (getchar() != '\n');
        }
    } while (1);
}

int isSameShowName(const void* pShow, const void* name)
{
    const Show* p1 = (const Show*)pShow;
    const char* p2 = (const char*)name;

    if (!p1)
        return 0;
    if (strcmp(p1->showName, p2) == 0)
        return 0;

    return 1;
}

void printShow(const void* pShow)
{
    Show* show = (Show*)pShow;
    printf("Show name: %-20s, The broadcast day is: %-15s, starts at: ", show->showName, show->broadcastDay);
    printTime(&show->startTime);
}

void printShowToFile(const void* pShow, FILE* file)
{
    Show* show = (Show*)pShow;

    fprintf(file, "%s\n", show->showName);// print the name
    fprintf(file, "%s\n", show->broadcastDay);//print broadcast day
    printTimeToFile(&show->startTime, file);//print starts at
    printTimeToFile(&show->endTime, file);//print ends at
    fprintf(file, "%d\n", show->showLengthInMinutes);
    fprintf(file, "%d\n", show->subtitles);
}

void writeShowToBinaryFile(const void* pShow, FILE* file)
{
    Show* show = (Show*)pShow;

    // Write show name
    int nameLength = strlen(show->showName) + 1;
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(show->showName, sizeof(char), nameLength, file);

    // Write broadcast day
    int broadcastDayLength = strlen(show->broadcastDay) + 1;
    fwrite(&broadcastDayLength, sizeof(int), 1, file);
    fwrite(show->broadcastDay, sizeof(char), broadcastDayLength, file);

    // Write start time
    fwrite(&show->startTime, sizeof(Time), 1, file);

    // Write end time
    fwrite(&show->endTime, sizeof(Time), 1, file);

    // Write show length in minutes and subtitles
    fwrite(&show->showLengthInMinutes, sizeof(int), 1, file);
    fwrite(&show->subtitles, sizeof(int), 1, file);
}

void freeShow(void* pShow)
{
}

