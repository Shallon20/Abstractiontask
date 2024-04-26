#include "PaymentSpec.h"
#include <string>
#ifdef _MSC_VER // Visual C++ ?
    #define strcasecmp _stricmp // then use the function _stricmp() 
#else
    #include <strings.h> // for strcasecmp() function in POSIX C++
#endif

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
    if (is)
    {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(PaymentSpec::CardType_str)/sizeof(PaymentSpec::CardType_str[0]); i++)
            {
                if (tmp.length() == PaymentSpec::CardType_str[i].length()
					&& 0 == strcasecmp(tmp.c_str(), std::string(PaymentSpec::CardType_str[i]).c_str())) // case insensitive comparison
                {
                    CardType = static_cast<PaymentSpec::CardType>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                CardType = PaymentSpec::CardType::ANY;
        }
    }

    return is;
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::CardScheme Cardscheme){
    return os<< 
    PaymentSpec::CardScheme_str[static_cast<size_t>(Cardscheme)];
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::CardScheme Cardscheme){
    if (is)
    {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(PaymentSpec::CardScheme_str)/sizeof(PaymentSpec::CardScheme_str[0]); i++)
            {
                if (tmp.length() == PaymentSpec::CardScheme_str[i].length()
					&& 0 == strcasecmp(tmp.c_str(), std::string(PaymentSpec::CardScheme_str[i]).c_str())) // case insensitive comparison
                {
                    Cardscheme = static_cast<PaymentSpec::CardScheme>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                Cardscheme = PaymentSpec::CardScheme::ANY;
        }
    }

    return is;
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::PaymentType PaymentType){
    return os<< 
    PaymentSpec::CardType_str[static_cast<size_t>(PaymentType)];
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::PaymentType PaymentType){
    if (is)
    {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(PaymentSpec::PaymentType_str)/sizeof(PaymentSpec::PaymentType_str[0]); i++)
            {
                if (tmp.length() == PaymentSpec::PaymentType_str[i].length()
					&& 0 == strcasecmp(tmp.c_str(), std::string(PaymentSpec::PaymentType_str[i]).c_str())) // case insensitive comparison
                {
                    PaymentType = static_cast<PaymentSpec::PaymentType>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                PaymentType = PaymentSpec::PaymentType::ANY;
        }
    }

    return is;
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
    if (is)
        is >> _cardType; // operator>>() processed csv_delimiter

    if (is)
        (is >> _cardScheme).ignore(); // call ignore() to skip csv_delimiter
    
    if (is)
        (is >> _paymentType).ignore();
    
}