#include "Payment.h"
#include <string.h>

/*Payment::Payment(
	const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const date_time& dateTime,
) 
{   _cardNumber = cardNumber;
	_currency = currency;
	_amountCents= amountCents; 
	_dateTime = dateTime; 
}*/
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
	Item::send_to(os);
	// sends ⌊Abstraction⌋ properties to the stream object os

	os << _cardNumber << csv_delimiter
	   << _currency << csv_delimiter
	   << _amountCents;
}

void Payment::recv_from(std::istream & is)
{
	Item::recv_from(is);

	if (is)
        (is >> _cardNumber).ignore(); // calling ignore() to skip csv_delimiter

    if (is)
       std::getline(is >>std::ws, _currency, csv_delimiter);

    if (is)
       (is >> _amountCents).ignore();

}