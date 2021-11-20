#pragma once

#include "General.h"
#include <ctime>

struct Date
{
	int year;
	int month;
	int day;

	int weekDay;

	int hours;
	int minutes;

	long timestamp;

	long ConvertToTimestamp(Date dateToConvert)
	{
		long result = dateToConvert.day;

		switch (dateToConvert.month - 1)
		{
		case 12:
			result += 31;
		case 11:
			result += 30;
		case 10:
			result += 31;
		case  9:
			result += 30;
		case  8:
			result += 31;
		case  7:
			result += 31;
		case  6:
			result += 30;
		case  5:
			result += 31;
		case  4:
			result += 30;
		case  3:
			result += 31;
		case  2:
			if (dateToConvert.year % 4 == 0 || dateToConvert.year % 400 == 0)
				result += 29;
			else
				result += 28;
		case 1:
			result += 31;
		}

		result += ((dateToConvert.year - 1900) - 1) * 365 + (((dateToConvert.year - 1900) - 1) / 4);
		result--;
		result *= 24;
		result += dateToConvert.hours;
		result--;
		result *= 60;
		result += dateToConvert.minutes;

		return result;
	}

	void GetCurrentTime()
	{
		tm ltm;
		time_t now = time(0);
		localtime_s(&ltm, &now);

		year = 1900 + ltm.tm_year;
		month = 1 + ltm.tm_mon;
		day = ltm.tm_mday;
		weekDay = ltm.tm_wday;
		hours = ltm.tm_hour;
		minutes = ltm.tm_min;
	}
};