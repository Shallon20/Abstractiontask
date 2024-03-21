#include "Log.h"
#include <cmath>
#include <vector>
#include <algorithm>

void Log::add_item(
    const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const Payment::date_time& dateTime,
    const PaymentSpec& spec
) {
    if (_count < Log::MAX_SIZE)
    {
        Payment new_item(cardNumber, currency, amountCents, dateTime, spec);
        _items[_count] = new_item;
        _count++;
    }
}

Payment Log::find_item(const Payment& query) const
{
    const auto& query_spec = query.get_spec();
    for (size_t i = 0; i < _count; i++)
    {
        const auto& item_spec = _items[i].get_spec();
        if (query.get_cardNumber() != ""
            && query.get_cardNumber() != _items[i].get_cardNumber())
            continue;
        if (query.get_currency() != ""
            && query.get_currency() != _items[i].get_currency())
            continue;
        if (query.get_amountCents() != 0
            && query.get_amountCents() != _items[i].get_amountCents())
            continue;
        if (query.get_dateTime() != Payment::date_time{}
            && query.get_dateTime() != _items[i].get_dateTime())
            continue;
        if (query_spec.get_cardType() != PaymentSpec::CardType::ANY
            && query_spec.get_cardType() != item_spec.get_cardType())
            continue;
        if (query_spec.get_cardScheme() != PaymentSpec::CardScheme::ANY
            && query_spec.get_cardScheme() != item_spec.get_cardScheme())
            continue;
        if (query_spec.get_paymentType() != PaymentSpec::PaymentType::ANY
            && query_spec.get_paymentType() != item_spec.get_paymentType())
            continue;

        return _items[i];
    }

    return Payment{}; // returns the 'default' object value

}

Payment Log::find_item(const PaymentSpec& query) const
{
    for (size_t i = 0; i < _count; i++)
    {
        const auto& item_spec = _items[i].get_spec();
        
        if (query.get_cardType() != PaymentSpec::CardType::ANY
            && query.get_cardType() != item_spec.get_cardType())
            continue;
        if (query.get_cardScheme() != PaymentSpec::CardScheme::ANY
            && query.get_cardScheme() != item_spec.get_cardScheme())
            continue;
        if (query.get_paymentType() != PaymentSpec::PaymentType::ANY
            && query.get_paymentType() != item_spec.get_paymentType())
            continue;

        return _items[i];
    }

    return Payment{}; // returns the 'default' object value

}

 Payment Log::find_largest_payment() const
 {
    std::vector<Payment> payments(std::begin(_items), std::begin(_items)+_count);
    std::sort(payments.begin(), payments.end());
    return payments.back();
 }

 double Log::find_average_amount() const
 {
    double sum = 0;
    for (size_t i = 0 ; i < _count ; i++){
        sum += _items[i].get_amountCents();
    }
    return sum/(double)_count/100;
 }

 