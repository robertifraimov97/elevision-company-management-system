
#ifndef DATE
#define DATE

typedef struct
{
    int			day;
    int			month;
    int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void    getCurrentDate(Date* pDate);
void	printDate(const Date* pDate);

#endif