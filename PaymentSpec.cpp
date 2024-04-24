#include "PaymentSpec.h"

bool PaymentSpec::matches(const PaymentSpec & otherSpec)const {
    if (this == &otherSpec) // if comparing to self
        return true;

    auto result{ true };

    // Check each BicycleSpec property, e.g.:
    
    
    if (PaymentSpec::get_cardType() != otherSpec._cardType &&
        _cardType != otherSpec._cardType)
    {
        result = false;
    }
    if (PaymentSpec::get_cardScheme() != otherSpec._cardScheme &&
        _cardScheme != otherSpec._cardScheme)
    {
        result = false;
    }
    if (PaymentSpec::get_paymentType() != otherSpec._paymentType &&
        _paymentType != otherSpec._paymentType)
    {
        result = false;
    }
    
return result;
}