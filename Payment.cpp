#include "Payment.h"

Payment::Payment(
	const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const CardType cardType,
	const date_time& dateTime
) {
	_cardNumber = cardNumber;
	_currency = currency;
	_amountCents = amountCents;
	_cardType = cardType;
	_dateTime = dateTime;
}