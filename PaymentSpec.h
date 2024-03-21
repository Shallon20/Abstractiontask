#pragma once

#include <string>
#include <chrono>

class PaymentSpec
{
public:
    
	enum class CardType {ANY, CREDIT, DEBIT, GIFT, EBT};
    enum class CardScheme {ANY, VISA, MASTERCARD, AMEX, DISCOVER};
    enum class PaymentType {ANY, AUTH, CHARGEBACK};
	static constexpr std::string_view CardType_str[] { "Any", "Credit", "Debit", "Gift", "EBT" };
    static constexpr std::string_view CardScheme_str[] { "Any", "Visa", "Mastercard", "AmEx", "Discover" };
    static constexpr std::string_view PaymentType_str[] { "Any", "Auth", "Chargeback" };
    PaymentSpec()
        : _cardType{ CardType::ANY }, _cardScheme{ CardScheme::ANY }, _paymentType{ 0U }
        { }

    PaymentSpec(CardType cardType, CardScheme cardScheme, PaymentType paymentType)
        : _cardType{ cardType }
        , _cardScheme{ cardScheme }
        , _paymentType{ paymentType }
        { }
    CardType get_cardType() const { return _cardType; }
	std::string_view get_cardType_str() const { return CardType_str[(std::size_t)_cardType]; }
    CardScheme get_cardScheme() const { return _cardScheme; }
	std::string_view get_cardScheme_str() const { return CardScheme_str[(std::size_t)_cardScheme]; }
    PaymentType get_paymentType() const { return _paymentType; }
	std::string_view get_paymentType_str() const { return PaymentType_str[(std::size_t)_paymentType]; }
private:
    CardType _cardType;
    CardScheme _cardScheme;
    PaymentType _paymentType;
};