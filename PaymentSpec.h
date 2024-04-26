#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <iostream>

class PaymentSpec
{
public:
    
	enum class CardType {ANY, CREDIT, DEBIT, GIFT, EBT};
    enum class CardScheme {ANY, VISA, MASTERCARD, AMEX, DISCOVER};
    enum class PaymentType {ANY, AUTH, CHARGEBACK};
	
    static constexpr std::string_view CardType_str[] { "Any", "Credit", "Debit", "Gift", "EBT" };
    static constexpr std::string_view CardScheme_str[] { "Any", "Visa", "Mastercard", "AmEx", "Discover" };
    static constexpr std::string_view PaymentType_str[] { "Any", "Auth", "Chargeback" };
    
    void send_to(std::ostream & os) const;
    void recv_from(std::istream & is);

    friend std::istream & operator>>(std::istream & is,
    PaymentSpec & spec);

    bool matches(const PaymentSpec & otherSpec) const;
    PaymentSpec() = default;

    PaymentSpec(CardType cardType, CardScheme cardScheme, PaymentType paymentType)
        : _cardType{ cardType }
        , _cardScheme{ cardScheme }
        , _paymentType{ paymentType }
        { }
    CardType get_cardType() const { return _cardType; }
	//std::string_view get_cardType_str() const { return CardType_str[(std::size_t)_cardType]; }
    CardScheme get_cardScheme() const { return _cardScheme; }
	//std::string_view get_cardScheme_str() const { return CardScheme_str[(std::size_t)_cardScheme]; }
    PaymentType get_paymentType() const { return _paymentType; }
	//std::string_view get_paymentType_str() const { return PaymentType_str[(std::size_t)_paymentType]; }
private:
    CardType _cardType;
    CardScheme _cardScheme;
    PaymentType _paymentType;
};
typedef std::shared_ptr<const PaymentSpec>spcPaymentSpec;

std::ostream & operator<<(std::ostream & os, PaymentSpec::CardType cardType);
std::istream & operator>>(std::istream & is, PaymentSpec::CardType & cardType);

std::ostream & operator<<(std::ostream & os, PaymentSpec::CardScheme cardScheme);
std::istream & operator>>(std::istream & is, PaymentSpec::CardScheme & cardScheme);

std::ostream & operator<<(std::ostream & os, PaymentSpec::PaymentType paymentType);
std::istream & operator>>(std::istream & is, PaymentSpec::PaymentType & paymentType);

std::ostream & operator<<(std::ostream & os, const
PaymentSpec & spec);

constexpr auto csv_delimiter { ';'};
