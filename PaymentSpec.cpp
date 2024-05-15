#include "PaymentSpec.h"
#include <string>
#ifdef _MSC_VER // Visual C++ ?
    #define strcasecmp _stricmp // then use the function _stricmp() 
#else
    #include <strings.h> // for strcasecmp() function in POSIX C++
#endif

bool PaymentSpec::matches(const ItemSpec & itemSpec)const {
    if (this == &itemSpec) // if comparing to self
        return true;

    bool result{ true };
    auto temp{ dynamic_cast<const PaymentSpec*>(&itemSpec) };
    if (nullptr == temp)
        return false; // if itemSpec doesn't refer to ⌊Abstraction⌋Spec (or derived) class instance

    // cast to reference type for actual comparison of properties
    const PaymentSpec & otherSpec{ *temp };
    // Check each BicycleSpec property, e.g.:
    
    
    if (otherSpec.get_cardType() != PaymentSpec::CardType::ANY &&
        otherSpec.get_cardType() != this->_cardType)
    {
        result = false;
    }
    if (otherSpec.get_cardScheme() != PaymentSpec::CardScheme::VISA &&
        otherSpec.get_cardScheme() != this->_cardScheme)
    {
        result = false;
    }
    if (otherSpec.get_paymentType() != PaymentSpec::PaymentType::CHARGEBACK &&
        otherSpec.get_paymentType() != otherSpec._paymentType)
    {
        result = false;
    }
    
return result;
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::CardType cardType){
os << PaymentSpec::CardType_str[static_cast<size_t>(cardType)];
return os;
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::CardType & cardType){
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
                    cardType = static_cast<PaymentSpec::CardType>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                cardType = PaymentSpec::CardType::ANY;
        }
    }

    return is;
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::CardScheme cardScheme){
    os<< PaymentSpec::CardScheme_str[static_cast<size_t>(cardScheme)];
return os;
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::CardScheme & cardScheme){
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
                    cardScheme = static_cast<PaymentSpec::CardScheme>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                cardScheme = PaymentSpec::CardScheme::ANY;
        }
    }

    return is;
}

std::ostream & operator<<(std::ostream & os, 
PaymentSpec::PaymentType paymentType){
    os<< PaymentSpec::CardType_str[static_cast<size_t>(paymentType)];
return os;
}
std::istream & operator>>(std::istream & is, 
PaymentSpec::PaymentType & paymentType){
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
                    paymentType = static_cast<PaymentSpec::PaymentType>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                paymentType = PaymentSpec::PaymentType::ANY;
        }
    }

    return is;
}

/*std::ostream & operator<<(std::ostream & os, const
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
*/
void PaymentSpec::send_to(std::ostream & os) const
{
    os << csv_delimiter<< _cardType
       << csv_delimiter<< _cardScheme
       <<csv_delimiter << _paymentType;
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
