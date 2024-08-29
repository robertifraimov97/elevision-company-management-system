
#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#define PRINT_SEPARATOR_LINE() \
    printf("------------------------------------------------------------------------------------------------------------\n");

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);

#endif

