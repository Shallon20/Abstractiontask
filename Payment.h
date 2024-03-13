#pragma once

#include <string>
#include <chrono>

class Payment
{
public:
	typedef std::chrono::system_clock::time_point date_time;
	enum class CardType {ANY, CREDIT, DEBIT, GIFT, EBT};
	static constexpr std::string_view CardType_str[] { "Any", "Credit", "Debit", "Gift", "EBT" };
	Payment(
		const std::string& cardNumber = "",
		const std::string& currency = "", 
		const int& amountCents = 0,
		const CardType cardType = CardType::ANY,
		const date_time& dateTime = {}
	);
	
	std::string get_cardNumber() const { return _cardNumber; }
	std::string get_currency() const { return _currency; }
	int get_amountCents() const { return _amountCents; }
	CardType get_cardType() const { return _cardType; }
	std::string_view get_cardType_str() { return CardType_str[(std::size_t)_cardType]; }
	date_time get_dateTime() const { return _dateTime; }

	inline bool operator <(const Payment& other)
	{
		return _amountCents < other._amountCents;
	}

private:
	std::string _cardNumber;
	std::string _currency;
	int _amountCents;
	CardType _cardType;
	date_time _dateTime;

};
