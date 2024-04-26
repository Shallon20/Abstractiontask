#include "Payment.h"
#include <string.h>

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
	os << _cardNumber << csv_delimiter
	   << _currency << csv_delimiter
	   << _amountCents;
	if (_spec)
	{
		os << csv_delimiter;
		_spec->send_to(os);
	}
}

void Payment::recv_from(std::istream & is)
{
	if (is)
        (is >> _cardNumber).ignore(); // calling ignore() to skip csv_delimiter

    if (is)
       std::getline(is >>std::ws, _currency, csv_delimiter);

    if (is)
       (is >> _amountCents).ignore();

    auto temp_spec{ std::make_shared<PaymentSpec>() };
    is >> *temp_spec; // alternatively: temp_spec->recv_from(is);
    _spec = temp_spec; // replace the specification
}