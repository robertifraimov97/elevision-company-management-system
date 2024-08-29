
#ifndef SHOW
#define SHOW
#define SHOW_NAME_LENGTH 50
#include "Time.h"

typedef enum { FALSE, TRUE } boolean;

typedef struct
{
    char showName[SHOW_NAME_LENGTH];
    int showLengthInMinutes;
    boolean subtitles;
    char broadcastDay[10];
    Time startTime;
    Time endTime;
}Show;

void getShowName(char* code);
void showSubtitles(Show* pShow);
void showLength(Show* pShow);
void choosingABroadcastDay(Show* pShow);
int	isSameShowName(const void* pShow, const void* name);
void printShow(const void* pShow);
void printShowToFile(const void* pShow, FILE* file);
void writeShowToBinaryFile(const void* pShow, FILE* file);
void freeShow(void* pShow);
#endif
