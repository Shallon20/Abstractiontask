#pragma once

#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include "PaymentSpec.h"

class Payment
{
public:
	typedef std::chrono::system_clock::time_point date_time;
	Payment(
		const std::string& cardNumber,
		const std::string& currency, 
		const int& amountCents,
		const date_time& dateTime,
		const std::shared_ptr<const PaymentSpec>& spec
	);
	Payment()
        : _cardNumber{ "" }
		, _currency{ "" }
		, _amountCents{ 0 }
		, _dateTime{ {} } 
		, _spec{ } { };
	std::string get_cardNumber() const { return _cardNumber; }
	std::string get_currency() const { return _currency; }
	int get_amountCents() const { return _amountCents; }
	date_time get_dateTime() const { return _dateTime; }
	const spcPaymentSpec & get_spec() const { return _spec; }
	
	void send_to(std::ostream & os) const;
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
	std::shared_ptr<const PaymentSpec> _spec;

};

std::ostream & operator<<(std::ostream & os, const
Payment & item);
