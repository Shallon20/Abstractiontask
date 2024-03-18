#include "Log.h"
#include <cmath>
#include <vector>
#include <algorithm>

void Log::add_item(
    const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
    const Payment::CardType cardType,
	const Payment::date_time& dateTime
) {
    if (_count < Log::MAX_SIZE)
    {
        Payment new_item(cardNumber, currency, amountCents, cardType, dateTime);
        _items[_count] = new_item;
        _count++;
    }
}

Payment Log::find_item(const Payment& query) const
{
    for (size_t i = 0; i < _count; i++)
    {
        if (query.get_cardNumber() != ""
            && query.get_cardNumber() != _items[i].get_cardNumber())
            continue;
        if (query.get_currency() != ""
            && query.get_currency() != _items[i].get_currency())
            continue;
        if (query.get_amountCents() != 0
            && query.get_amountCents() != _items[i].get_amountCents())
            continue;
        if (query.get_cardType() != Payment::CardType::ANY
            && query.get_cardType() != _items[i].get_cardType())
            continue;
        if (query.get_dateTime() != Payment::date_time{}
            && query.get_dateTime() != _items[i].get_dateTime())
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

 