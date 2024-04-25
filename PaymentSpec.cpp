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
std::ostream & operator<<(std::ostream & os, 
PaymentSpec::CardType CardType){
    return os<< 
    PaymentSpec::CardType_str[static_cast<size_t>(CardType)];
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::CardType CardType){
    //demo
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::CardScheme Cardscheme){
    return os<< 
    PaymentSpec::CardScheme_str[static_cast<size_t>(Cardscheme)];
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::CardScheme Cardscheme){
    //demo
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::PaymentType PaymentType){
    return os<< 
    PaymentSpec::CardType_str[static_cast<size_t>(PaymentType)];
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::PaymentType PaymentType){
    //demo
}

std::ostream & operator<<(std::ostream & os, const
PaymentSpec & spec)
{
    spec.send_to(os);
    return os;
}

std::istream & operator>>(std::istream & is, PaymentSpec
& item)
{
    item.recv_from(is);
    return is;
}

void PaymentSpec::send_to(std::ostream & os) const
{
    os << PaymentSpec::CardType::CREDIT << csv_delimiter
       << PaymentSpec::CardScheme::VISA << csv_delimiter
       << PaymentSpec::PaymentType::AUTH << csv_delimiter;
}

void PaymentSpec::recv_from(std::istream & is)
{
    // demo
}