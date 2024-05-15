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
	
	Payment(int id, std::string cardNumber, std::string currency,int amountCents, date_time dateTime, std::shared_ptr<const PaymentSpec> spec)
		: Item(id, spec),
		  _cardNumber{ cardNumber },
		  _currency { currency },
		  _amountCents { amountCents },
		  _dateTime { dateTime } 
		   {}
	std::string get_cardNumber() const { return _cardNumber; }
	std::string get_currency() const { return _currency; }
	int get_amountCents() const { return _amountCents; }
	date_time get_dateTime() const { return _dateTime; }
 
	
	void send_to(std::ostream & os) const override;
	void recv_from(std::istream & is) override;
	
	/*std::istream & operator>>(std::istream &is,
	Payment & item);

	inline bool operator <(const Payment& other) const
	{
		return _amountCents < other._amountCents;
	} */

private:
	std::string _cardNumber;
	std::string _currency;
	int _amountCents;
	date_time _dateTime;
	

};

