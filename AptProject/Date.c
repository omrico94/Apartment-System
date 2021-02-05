#include "Date.h"

int checkDateLater(Date* checkDate, Date* entryDate)
{
	if (checkDate->Year < entryDate->Year)
	{
		return 1;
	}
	else if (checkDate->Year == entryDate->Year)
	{
		if (checkDate->Month < entryDate->Month)
		{
			return 1;
		}
		else if (checkDate->Month == entryDate->Month)
		{
			if (checkDate->Day <= entryDate->Day)
				return 1;
		}
	}
	return 0;
}

void setAnewDate(Date* currentdate, int num)
{
	if (num < currentdate->Day)
	{
		currentdate->Day -= num;
	}
	else
	{
		num -= currentdate->Day;

		if (currentdate->Month - 1 == 0)
		{
			currentdate->Month = 12;
			currentdate->Year -= 1;
			currentdate->Day = 31;

		}
		else if ((currentdate->Month - 1) == 2)
		{
			currentdate->Month -= 1;
			currentdate->Day = 28;
		}
		else if ((currentdate->Month - 1) == 4 || (currentdate->Month - 1) == 6 || (currentdate->Month - 1) == 9 || (currentdate->Month - 1) == 11)
		{
			currentdate->Month -= 1;
			currentdate->Day = 30;
		}
		else
		{
			currentdate->Month -= 1;
			currentdate->Day = 31;
		}
		setAnewDate(currentdate, num);
	}
}

Date* CurTime()
{
	Date* curDate = (Date*)malloc(sizeof(Date));
	time_t curTime;
	time(&curTime);

	struct tm *MyTime = localtime(&curTime);

	curDate->Day = MyTime->tm_mday;
	curDate->Month = MyTime->tm_mon + 1;
	curDate->Year = MyTime->tm_year + 1900;

	return curDate;
}