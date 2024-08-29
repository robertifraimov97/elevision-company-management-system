
#ifndef _CHANNEL_
#define _CHANNEL_
#define MAX_CHANNEL_NUM 200
#define MIN_CHANNEL_NUM 1
#include "Commercial.h"
#include "List.h"
#include "Show.h"
#define PRINT_PLURAL_IF_MORE_THAN_ONE(num) \
    if (num > 1) { \
        printf("s"); \
    } \
    printf("\n");


typedef enum {
    eAction, eComedy, eSport, eReality, eNews, eEntertainment, eNofgenreTypes
} eGenreType;

static const char* ChannelTypeStr[eNofgenreTypes]
        = { "Action", "Comedy", "Sport", "Reality", "News","Entertainment" };


typedef struct
{
    int ChannelNum;
    eGenreType type;
    Commercial* CommercialArr;
    int numOfCommercial;
    LIST showsList;
}Channel;

void initChannel(Channel* pChannel);
int initShow(Show* pShow, Channel* pChannel);
int getChannelType(Channel* pChannel);
int addCommercial(Channel* pChannel);
int choosingChannelNum(Channel* pChannel);
void printChannel(const Channel* pChannel);
void printCommercialsArr(void* arr, int size);
void generalArrayFunction(void* arr, int numOfElements, size_t typeSize, void(*freeOrPrintFunc)(void*, int));
int	addShow(Channel* pChannel);
Show* findShowByName(const Channel* pChannel, char* name);
int checkUniqeName(char* name, const Channel* pChannel);
int broadcastTime(Show* pShow, Channel* pChannel);
Commercial* commercialNameExist(char* commercialName, Commercial* commercialArr, int numOfCommercials);
int deleteCommercial(Commercial* commercialArr, int* numOfCommercials, char* commercialToDelete);
void freeChannel(Channel* pChannel);


#endif