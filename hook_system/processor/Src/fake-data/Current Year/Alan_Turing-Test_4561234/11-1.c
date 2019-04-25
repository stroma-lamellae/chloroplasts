#include <stdio.h>

typedef enum {false, true} bool;

bool leap(int year)
{
	if(year%400 == 0){return true;}
	else if(year%100 == 0){return false;}
	else if(year%4 == 0){return true;}
	else {return false;}
}

int dayOfYear(int day, int month, int year)
{
	int sum = 0;
	bool last = true;
	if (year < 1753) {return -1;}
	else if (!(1<=month && month<=12)) {return -1;}
	else
	{
		switch(month)
		{
			case 12:
			{
				if(1<=day && day<=31){sum = sum + day;}
				else {return -1;}
				last = false;
				day = 15; //Safe number as it is counted later
			}
			case 11:
			{
				if(1<= day && day <=30)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 30;}
				}
				else {return -1;}
			}
			case 10:
			{
				if(1<=day && day<=31)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 31;}
				}
				else {return -1;}
			}
			case 9:
			{
				if(1<=day && day<=30)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 30;}
				}
				else {return -1;}
			}
			case 8:
			{
				if(1<=day && day<=31)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 31;}
				}
				else  {return -1;}
			}
			case 7:
			{
				if(1<= day && day<=31)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 31;}
				}
				else {return -1;}
			}
			case 6:
			{
				if(1<=day && day<=30)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum =  sum + 30;}
				}
				else {return -1;}
			}
			case 5:
			{
				if(1<=day && day <=31)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 31;}
				}
				else {return -1;}
			}
			case 4:
			{
				if(1<= day && day <=30)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 30;}
				}
				else {return -1;}
			}
			case 3:
			{
				if(1<=day && day <=31)
				{
					if(last)
					{
						sum = sum + day;
						last = false;
						day = 15;
					}
					else {sum = sum + 31;}
				}
				else {return -1;}
			}
			case 2:
			{
				if(leap(year))
				{
					if(1<=day && day<=29)
					{
						if(last)
						{
							sum = sum + day;
							last = false;
							day = 15;
						}
						else {sum = sum + 29;}
					}
					else {return -1;}
				}
				else
				{
					if(1<=day && day<=28)
					{
						if(last)
						{
							sum = sum + day;
							last = false;
							day = 15;
						}
						else {sum = sum + 28;}
					}
					else {return -1;}
				}
			}
			case 1:
			{
				if(1<=day &&day <=31)
				{
					if(last)
					{
						sum = sum + day;
					}
					else {sum = sum + 31;}
				}
				else {return -1;}
			}
		}
	}
	return sum;
}
/*
void testDayOfYear(int day, int month, int year)
{
	printf("%d/%d/%d => %d\n", day, month, year, dayOfYear(day, month, year));
}
/*
int main (void)
{
	testDayOfYear(1, 1, 2008);
	testDayOfYear(29, 2, 2008);
	testDayOfYear(29, 2, 2009);
	testDayOfYear(26, 9, 2008);
	testDayOfYear(31, 12, 2008);
	testDayOfYear(31, 12, 2009);
	testDayOfYear(100, 1, 2009);
	testDayOfYear(1, 100, 2008);
	testDayOfYear(1, 1, 100);
}
*/