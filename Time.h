//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_TIME_H
//#define FINAL_PROJECT_IN_C_TIME_H

//#endif //FINAL_PROJECT_IN_C_TIME_H
#ifndef TIME
#define TIME


typedef struct
{
	int hours;
	int minutes;
	int seconds;

}Time;

void validTime(Time* pTime);
int	 checkTime(char* time, Time* pTime);
void printTime(const Time* pTime);
void printTimeToFile(const Time* pTime, FILE* file);

#endif

