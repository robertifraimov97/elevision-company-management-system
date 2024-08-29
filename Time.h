
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
