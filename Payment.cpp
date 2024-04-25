#include "Payment.h"

Payment::Payment(
	const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const date_time& dateTime,
	const std::shared_ptr<const PaymentSpec>& spec
) 
	: _cardNumber{ cardNumber }
		, _currency{ currency }
		, _amountCents{ amountCents }
		, _dateTime{ dateTime } 
		, _spec{ spec } { };

std::ostream & operator<<(std::ostream & os, const
Payment & item)
{
	item.send_to(os);
	return os;
}
std::istream & operator>>(std::istream & is, Payment &
item)
{
	item.recv_from(is);
	return is;
}

void Payment::send_to(std::ostream &os) const
{
	os << Payment::_cardNumber << csv_delimiter
	   << Payment::_currency << csv_delimiter
	   << Payment::_amountCents << csv_delimiter
	   << Payment::_dateTime << csv_delimiter
	   << Payment::_spec << csv_delimiter;
	if (_spec)
	{
		os << csv_delimiter;
		_spec->send_to(os);
	}
}

void recv_from(std::istream & is)
{
	//demo
}