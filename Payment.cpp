#include "Payment.h"
#include <string.h>
/*
Payment::Payment(
	const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const date_time& dateTime,
	spcPaymentSpec spec
) 
{   _cardNumber = cardNumber;
	_currency = currency;
	_amountCents= amountCents; 
	_dateTime = dateTime; 
	_spec = spec ;
}
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
*/
void Payment::send_to(std::ostream &os) const
{
	os << csv_delimiter << _cardNumber
	   << csv_delimiter << _currency
	   << csv_delimiter << _amountCents
	   << csv_delimiter << _dateTime;
	/*if (_spec)
	{
		os << csv_delimiter;
		_spec->send_to(os);
	}*/
}

void Payment::recv_from(std::istream & is)
{
	if (is)
        (is >> _cardNumber).ignore(); // calling ignore() to skip csv_delimiter

    if (is)
       std::getline(is >>std::ws, _currency, csv_delimiter);

    if (is)
       (is >> _amountCents).ignore();

    //auto temp_spec{ std::make_shared<PaymentSpec>() };
    //is >> *temp_spec; // alternatively: temp_spec->recv_from(is);
   // _spec = temp_spec; // replace the specification
}
 double Payment::find_largest_payment() const
 {
    std::vector<Payment> payments(std::begin(_items), std::begin(_items)+_count);
    std::sort(payments.begin(), payments.end());
    return payments.back();
 }

double Payment::find_average_amount() const
 {
    double sum = 0.0;
    for (size_t i = 0 ; i < _count ; i++){
        sum += _items[i].get_amountCents();
    }
    return sum/(double)_count/100;
 }
