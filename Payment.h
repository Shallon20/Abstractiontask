#pragma once

#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include "PaymentSpec.h"
#include "ItemSpec.h"
#include "Item.h"

class Payment : public Item
{
public:
	typedef std::chrono::system_clock::time_point date_time;
	
	Payment() = default;

	std::string get_cardNumber() const { return _cardNumber; }
	std::string get_currency() const { return _currency; }
	int get_amountCents() const { return _amountCents; }
	date_time get_dateTime() const { return _dateTime; }
 
	
	void send_to(std::ostream & os) const override;
	void recv_from(std::istream & is);
	friend std::istream & operator>>(std::istream &is,
	Payment & item);

	inline bool operator <(const Payment& other) const
	{
		return _amountCents < other._amountCents;
	}

private:
	std::string _cardNumber;
	std::string _currency;
	int _amountCents;
	date_time _dateTime;
	spcPaymentSpec _spec;

};

std::ostream & operator<<(std::ostream & os, const
Payment & item);
