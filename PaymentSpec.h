#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <iostream>
#include <cstddef>
#include "ItemSpec.h"

class PaymentSpec : public ItemSpec
{
public:
    
	enum class CardType {ANY, CREDIT, DEBIT, GIFT, EBT};
    enum class CardScheme {ANY, VISA, MASTERCARD, AMEX, DISCOVER};
    enum class PaymentType {ANY, AUTH, CHARGEBACK};
	
    static constexpr std::string_view CardType_str[] { "Any", "Credit", "Debit", "Gift", "EBT" };
    static constexpr std::string_view CardScheme_str[] { "Any", "Visa", "Mastercard", "AmEx", "Discover" };
    static constexpr std::string_view PaymentType_str[] { "Any", "Auth", "Chargeback" };
    
    PaymentSpec() = default;
    PaymentSpec(CardType cardType, CardScheme cardScheme, PaymentType paymentType)
     :
        _cardType { cardType }
        ,_cardScheme { cardScheme }
        ,_paymentType { paymentType }
        {}
    CardType get_cardType() const { return _cardType; }
    CardScheme get_cardScheme() const { return _cardScheme; }
    PaymentType get_paymentType() const { return _paymentType; }

    void send_to(std::ostream & os) const override;
    void recv_from(std::istream & is)override;

    //friend std::istream & operator>>(std::istream & is,
    //PaymentSpec & spec);

    bool matches(const ItemSpec & otherSpec) const override;
   
    private:
    CardType _cardType;
    CardScheme _cardScheme;
    PaymentType _paymentType;
};
//typedef std::shared_ptr<const PaymentSpec>spcPaymentSpec;

std::ostream & operator<<(std::ostream & os, PaymentSpec::CardType cardType);
std::istream & operator>>(std::istream & is, PaymentSpec::CardType & cardType);

std::ostream & operator<<(std::ostream & os, PaymentSpec::CardScheme cardScheme);
std::istream & operator>>(std::istream & is, PaymentSpec::CardScheme & cardScheme);

std::ostream & operator<<(std::ostream & os, PaymentSpec::PaymentType paymentType);
std::istream & operator>>(std::istream & is, PaymentSpec::PaymentType & paymentType);

/*std::ostream & operator<<(std::ostream & os, const
PaymentSpec & spec);

constexpr auto csv_delimiter { ';'};*/