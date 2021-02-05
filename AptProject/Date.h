#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef Date_h
#define Date_h

#define DATE "Date"

typedef struct date
{
	short Day;
	short Month;
	int Year;
}Date;

//This funciton recieves a current date and a number.
//The function sets the date to the date that was "num"  days before today.
void setAnewDate(Date* currentdate, int num);

//This funcion recieves two dates.
//The function returns 1 if the check date is earlier than the entry date and 0 if not.
int checkDateLater(Date* checkDate, Date* entryDate);

//This function returns a struct of today date.
Date* CurTime();

#endif /* Date_h */