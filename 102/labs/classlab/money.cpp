/*Elizabeth Stauder (estaude)
CPSC 1021-004
03/12/15
This program creates a C++ class. */
#include "money.h"
money_t::money_t(){
	dollars = 0;
	cents = 0;
}
money_t::money_t(double amount){ 
	dollars = (int) amount; 
	cents = (int) ((amount - dollars) * 100);
}
money_t::money_t(int d, int c){
	dollars = d;
	cents = c;
}
money_t::~money_t(){
	cout<<"destructor invoked\n";
}
int money_t::get_dollars(){
	return dollars;
}
int money_t::get_cents(){
	return cents;
}
void money_t::set_dollars(int amount){
	dollars = amount;
}
void money_t::set_cents(int amount){
	cents = amount;
}
void money_t::set(int dollar_amt, int cent_amt){
	dollars = dollar_amt;
	cents = cent_amt;
}
int money_t::value_in_cents(){
	double x = (dollars * 100) + cents;
	return x;
}
double money_t::compute_value(){
	double x = dollars + (cents / 100.0);
	return x;
}
