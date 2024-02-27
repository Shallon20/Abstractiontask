#include "Payment.h"

Payment::Payment(
	const string& cardNumber, 
	const string& currency, 
	const int& amountCents, 
	const date_time& dateTime
) {
	_cardNumber = cardNumber;
	_currency = currency;
	_amountCents = amountCents;
	_dateTime = dateTime;
}