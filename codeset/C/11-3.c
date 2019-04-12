#include <stdio.h>

typedef int bool;
#define true 1
#define false 0
const double num = 200;

bool isLeapYear(int year){
	if(year%(int)(num*2) == 0) {
        return 1;
    }
	else if(year%(int)(num/2) == 0){
        return 0;
    }
	else if(year%(int)(num*0.02) == 0){
        return 1;
    }
	else {
        return 0;
    }
}

bool dayCheckThirtyOne(int d){
    if (1<=d && d<=31) {
        return 1;
    }
    else {
        return 0;
    }
}

bool dayCheckThirty(int d){
    if (1<=d && d<=30) {
        return 1;
    }
    else {
        return 0;
    }
}

bool dayCheckMonth(int m){
    if (1<=m && m<=12) {
        return 1;
    }
    else {
        return 0;
    }
}

void test(int day, int month, int year)
{
	printf("\n", day, month, year, dayinYear(day, month, year));
}


int dayinYear(int day, int month, int year){
	int sum = 0;
	bool last = 1;
	if (year < 1753) {
        return -1;
    }
	else if (!dayCheckMonth(month)) {
        return -1;
        }
	else{
		switch(month){
            case 1:{
				if(dayCheckThirtyOne(day)) {
					if(last) {
						sum+=day;
					}
					else {
                        sum+=31;
                    }
				}
				else {
                    return -1;
                }
			}
			case 2: {
				if(isLeapYear(year)) {
					if(1<=day && day<=29){
						if(last){
							sum+=day;
							last = 0;
							day = 15;
						}
						else {
                            sum+=29;
                        }
					}
					else {
                        return -1;
                    }
				}
				else {
					if(1<=day && day<=28) {
						if(last) {
							sum+=day;
							last = 0;
							day = 15;
						}
						else {
                            sum+=28;
                        }
					}
					else {
                        return -1;
                    }
				}
			}
			case 3:{
				if(dayCheckThirtyOne(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=31;
                    }
				}
				else {
                    return -1;
                }
			}
			case 4:{
				if(dayCheckThirty(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=30;
                    }
				}
				else {
                    return -1;
                }
			}
			case 5: {
				if(dayCheckThirtyOne(day))
				{
					if(last)
					{
						sum+=day;
						last = 0;
						day = 15;
					}
					else {sum+=31;}
				}
				else {return -1;}
			}
			case 6:{
				if(dayCheckThirty(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum =  sum + 30;
                    }
				}
				else {
                    return -1;
                }
			}
			case 7:{
				if(dayCheckThirtyOne(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=31;
                    }
				}
				else {
                    return -1;
                }
			}
			case 8:{
				if(dayCheckThirtyOne(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=31;
                    }
				}
				else  {
                    return -1;
                }
			}
			case 9:{
				if(dayCheckThirty(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=30;
                    }
				}
				else {
                    return -1;
                }
			}
			case 10:{
				if(dayCheckThirtyOne(day)){
					if(last){
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=31;
                    }
				}
				else {
                    return -1;
                }
			}
			case 11:{
				if (dayCheckThirty(day)) {
					if (last) {
						sum+=day;
						last = 0;
						day = 15;
					}
					else {
                        sum+=30;
                    }
				}
				else {
                    return -1;
                }
			}
			case 12:{
				if(dayCheckThirtyOne(day)){
                    sum+=day;
                    }
				else {
                    return -1;
                    }
				last = 0;
				day = 15; //Safe number as it is counted later
			}
		}
	}
	return sum;
}

