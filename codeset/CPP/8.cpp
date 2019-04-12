// A4.cpp : Defines the entry point for the console application.
// Program about showing yearly cost of shopping carts

//#include "stdafx.h"
#include "iostream"
#include "string.h"
using namespace std;


//Base Class
class shopper{

protected:
	char *shopper_name;
	int years_a_member;
	double avg_monthly_purchases, membership_cost, nominal_membership_cost = 50;

public:
	shopper(int yrs_a_mbr, char *sh_nm, double av_mnth_prchs = 250.00); //Constructor

	~shopper() { //~Destructor
		cout << "In the destructor" << endl;
		delete[] shopper_name;
	}

	virtual void set_membership_cost(void)
	{
		if (years_a_member < 5){
			membership_cost = nominal_membership_cost - ((avg_monthly_purchases * 0.01)*0.5) - nominal_membership_cost * (0.04 * years_a_member);
		}
		else{
			membership_cost = 30;
		}
	}

	double get_membership_cost(void){
		return membership_cost += 2;

	}
	char * get_shoper_name(void) {
		return shopper_name;
	}


};
//Outside / Member functions definitions including constructor
shopper::shopper(int yrs_a_mbr, char *sh_nm, double av_mnth_prchs): years_a_member (yrs_a_mbr){
	shopper_name = new char[strlen(sh_nm + 1)]; //Dynamically Allocated
	strcpy(shopper_name, sh_nm);
	avg_monthly_purchases = av_mnth_prchs;
}

//Ostream
ostream &operator <<(ostream &output, shopper &shpr) {
	output << shpr.get_shoper_name() << " has yearly membership cost of $" << shpr.get_membership_cost() << endl;
	return output;
}

//Derived Class
class family_shopper : public shopper
{
	public:
		family_shopper(char * f_sh_nm,double fam_disc = 10, int yrs_a_mbr = 2, double av_mnth_prchs = 100): shopper (yrs_a_mbr, shopper_name = f_sh_nm, av_mnth_prchs){
			family_discount = fam_disc;
		}

		virtual void set_membership_cost() {
			membership_cost = (nominal_membership_cost - ((avg_monthly_purchases * 0.01)*0.5) - nominal_membership_cost * (0.04 * years_a_member))* (1 - family_discount / 100);
		}

		friend ostream &operator << (ostream &output, family_shopper &f_shpr) {

			output << endl << f_shpr.shopper_name << " is a family shopper whose annual membership with discount of " << f_shpr.family_discount << "% is $" << f_shpr.membership_cost << endl;

			cout.setf(ios::fixed);
			cout.precision(2);
			return output;
		}

	private:
		double family_discount;



};

int main()
{
	static shopper shpr1(3, "ABC", 600);
	static shopper shpr2(6, "DEF");

	static family_shopper f_shpr1("GHI", 12);


	shopper *ptr;

	ptr = &shpr1;
	ptr->set_membership_cost();
	cout << shpr1;

	ptr = &shpr2;
	ptr->set_membership_cost();
	cout << shpr2;

	ptr = &f_shpr1;
	ptr->set_membership_cost();
	cout << f_shpr1;

	return 0;
}