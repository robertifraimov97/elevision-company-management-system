//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_GENERAL_H
//#define FINAL_PROJECT_IN_C_GENERAL_H

//#endif //FINAL_PROJECT_IN_C_GENERAL_H

#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#define PRINT_SEPARATOR_LINE() \
    printf("------------------------------------------------------------------------------------------------------------\n");

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);

#endif

