#include <stdio.h>

typedef enum {false, true} bool;

// Check if year is leap
bool leap(int year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

// Check if the day is valid
bool validDay(int day, int min, int max){
    return min <= day && day <= max;
}

// Here we check the day of the year
int dayOfYear(int day, int month, int year)
{
	int sum = 0;
	bool last = true;
	if (year < 1753) {return -1;}
	else if (month < 1 || month > 12) {return -1;}
	else
	{
		switch(month)
		{
			case 12:
			{
				if(validDay(day, 1, 31)){sum += day;}
				else {return -1;}
				last = false;
				day = 15;
			}
			case 11:
			{
				if(validDay(day, 1, 30))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 30;}
				}
				else {return -1;}
			}
			case 10:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 31;}
				}
				else {return -1;}
			}
			case 9:
			{
				if(validDay(day, 1, 30))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 30;}
				}
				else {return -1;}
			}
			case 8:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 31;}
				}
				else  {return -1;}
			}
			case 7:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 31;}
				}
				else {return -1;}
			}
			case 6:
			{
				if(validDay(day, 1, 30))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum =  sum + 30;}
				}
				else {return -1;}
			}
			case 5:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 31;}
				}
				else {return -1;}
			}
			case 4:
			{
				if(validDay(day, 1, 30))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 30;}
				}
				else {return -1;}
			}
			case 3:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
						last = false;
						day = 15;
					}
					else {sum += 31;}
				}
				else {return -1;}
			}
			case 2:
			{
				if(leap(year))
				{
					if(validDay(day, 1, 29))
					{
						if(last)
						{
							sum += day;
							last = false;
							day = 15;
						}
						else {sum += 29;}
					}
					else {return -1;}
				}
				else
				{
					if(validDay(day, 1, 28))
					{
						if(last)
						{
							sum += day;
							last = false;
							day = 15;
						}
						else {sum += 28;}
					}
					else {return -1;}
				}
			}
			case 1:
			{
				if(validDay(day, 1, 31))
				{
					if(last)
					{
						sum += day;
					}
					else {sum += 31;}
				}
				else {return -1;}
			}
		}
	}
	return sum;
}