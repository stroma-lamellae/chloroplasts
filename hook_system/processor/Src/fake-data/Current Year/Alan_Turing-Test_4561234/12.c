#include <stdio.h>

typedef enum {false, true} bool;

bool leap(int year)
{
	if(year%400 == 0){return true;}
	else if(year%100 == 0){return false;}
	else if(year%4 == 0){return true;}
	else {return false;}
}

int dateSplit(int dayOfYear, int year, int *day, int *month)
{
	if(year < 1753) {return 0;}
	if(dayOfYear < 1) {return 0;}
	if(dayOfYear == 366)
	{
		if(leap(year))
		{
			//Do Nothing
		}
		else
		{
			return 0;
		}
	}
	if(dayOfYear > 366) {return 0;}
	
	//January
	if(dayOfYear - 31 <= 0)
	{
		*month = 1;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//February
	if(leap(year))
	{
		if(dayOfYear - 29 <= 0)
		{
			*month = 2;
			*day = dayOfYear;
			return 1;
		}
		else
		{
			dayOfYear = dayOfYear - 29;
		}
	}
	else
	{
		if(dayOfYear - 28 <= 0)
		{
			*month = 2;
			*day = dayOfYear;
			return 1;
		}
		else
		{
			dayOfYear = dayOfYear - 28;
		}
	}
	
	//March
	if(dayOfYear - 31 <= 0)
	{
		*month = 3;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//April
	if(dayOfYear - 30 <= 0)
	{
		*month = 4;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 30;
	}
	
	//May
	if(dayOfYear - 31 <= 0)
	{
		*month = 5;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//June
	if(dayOfYear - 30 <= 0)
	{
		*month = 6;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 30;
	}
	
	//July
	if(dayOfYear - 31 <= 0)
	{
		*month = 7;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//August
	if(dayOfYear - 31 <= 0)
	{
		*month = 8;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//September
	if(dayOfYear - 30 <= 0)
	{
		*month = 9;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 30;
	}
	
	//October
	if(dayOfYear - 31 <= 0)
	{
		*month = 10;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	//November
	if(dayOfYear - 30 <= 0)
	{
		*month = 11;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 30;
	}
	
	//December
	if(dayOfYear - 31 <= 0)
	{
		*month = 12;
		*day = dayOfYear;
		return 1;
	}
	else
	{
		dayOfYear = dayOfYear - 31;
	}
	
	return 0; //Safe catch
}