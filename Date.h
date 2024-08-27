//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_DATE_H
//#define FINAL_PROJECT_IN_C_DATE_H

//#endif //FINAL_PROJECT_IN_C_DATE_H


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