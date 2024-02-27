#pragma once

#include <string>
#include <chrono>

using namespace std;

class Payment
{
public:
	typedef chrono::system_clock::time_point date_time;

	Payment(
		const string& cardNumber = "",
		const string& currency = "", 
		const int& amountCents = 0,
		const date_time& dateTime = {}
	);
	
	string get_cardNumber() const { return _cardNumber; }
	string get_currency() const { return _currency; }
	int get_amountCents() const { return _amountCents; }
	date_time get_dateTime() const { return _dateTime; }

private:
	string _cardNumber;
	string _currency;
	int _amountCents;
	date_time _dateTime;

};
