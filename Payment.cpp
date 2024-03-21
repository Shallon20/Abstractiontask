#include "Payment.h"

Payment::Payment(
	const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const date_time& dateTime,
	const PaymentSpec& spec
) 
	: _cardNumber{ cardNumber }
		, _currency{ currency }
		, _amountCents{ amountCents }
		, _dateTime{ dateTime } 
		, _spec{ spec } { };

