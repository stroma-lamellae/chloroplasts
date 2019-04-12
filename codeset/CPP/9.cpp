#include <iostream>
#include <cstring>

using namespace std;

class shopper {

protected:
	char* shopper_name;
	int years_a_member;
	double avg_monthly_purchases;
	double membership_cost;
	double nominal_membership_cost = 50;

public:
	shopper(int yrs_a_mbr, char* sh_nm, double av_mnth_prchs = 250.00);
	~shopper(void)
	{
		delete[] shopper_name;
		cout << "In the destructor" << endl;
	}

	virtual void set_membership_cost(void)
	{
	if (years_a_member < 5) {
			membership_cost = nominal_membership_cost - (0.005)*avg_monthly_purchases
				- nominal_membership_cost*(0.04)*years_a_member;
		}
		else {
			membership_cost = 30;
		}
	}

	double get_membership_cost(void)
	{
		return membership_cost += 2.00;
	}

	char* get_shopper_name(void)
	{
		return shopper_name;
	}

};

shopper::shopper(int yrs_a_mbr, char* sh_nm, double av_mnth_prchs) : years_a_member(yrs_a_mbr)
{
	shopper_name = new char[strlen(sh_nm) + 1];
	//strcpy_s(shopper_name, (strlen(sh_nm) + 1)*sizeof(char), sh_nm);
	strcpy(shopper_name, sh_nm);
	avg_monthly_purchases = av_mnth_prchs;
}


ostream& operator << (ostream& os, shopper& shpr)
{
	os << shpr.get_shopper_name() << " has yearly membership cost of $" << shpr.get_membership_cost() << endl;
	return os;
}

class family_shopper : public shopper {

private:
	double family_discount;

public:
	family_shopper(char* f_sh_nm, double fam_disc = 10.00, int yrs_a_mbr = 2, double av_mnth_prchs = 100.00) : shopper(yrs_a_mbr, f_sh_nm, av_mnth_prchs)
	{
		family_discount = fam_disc;
	}


	virtual void set_membership_cost(void)
	{
		shopper::set_membership_cost();
		membership_cost *= (1 - (family_discount) / 100);
	}

	friend ostream& operator<<(ostream& os, family_shopper& f_shpr)
	{
		os << f_shpr.shopper_name << " is a family shopper whose annual membership with discount of " << f_shpr.family_discount << "% is $" << f_shpr.membership_cost << endl;
		//cout.setf(ios::fixed);
		//cout.precision(2);
		return os;
	}

};


int main(void)
{
	cout << "CPS311 A4 Gp69 Khudadad, J; Safaryan, E; Rahbar, A" << "\n" << endl;

	shopper shpr1(3, "ABC", 600);
	shopper shpr2(6, "DEF");
	family_shopper f_shpr1("GHI", 12.00);

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

};